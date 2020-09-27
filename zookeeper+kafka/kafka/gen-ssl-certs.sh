#!/bin/bash
#
#
# This scripts generates:
#  - root CA certificate
#  - server certificate and keystore
#  - client keys
#
# https://cwiki.apache.org/confluence/display/KAFKA/Deploying+SSL+for+Kafka
#

#国家代码
C=CN
#省/市
ST=SC
#城市/区域
L=CD
#组织行业
O=Development
#组织单位
OU=CH
#用户名
CN="$1"

#证书密码
PASS="$2"

#证书有效时间(天)
VALIDITY=10000

set -e

export LC_ALL=C

if [[ -n "$CN" && -n "$PASS" ]]; then

    if [ ! -d "./server/" ];then
        mkdir ./server/
    else
        rm -rf ./server/
        mkdir ./server/
    fi
    if [ ! -d "./client/" ];then
        mkdir ./client/
    else
        rm -rf ./client/
        mkdir ./client/
    fi
    
    echo "############ Generating CA"
    openssl req -new -x509 -keyout ca_cert.key -out ca_cert -days $VALIDITY -passin "pass:$PASS" -passout "pass:$PASS" <<EOF
${C}
${ST}
${L}
${O}
${OU}
${CN}
$USER@${CN}
.
.
EOF

#Step 1
    echo "############ Generating key"
    keytool -storepass "$PASS" -keypass "$PASS" -keystore ./server/server.keystore.jks -alias localhost -validity $VALIDITY -genkey -keyalg RSA <<EOF
$CN
$OU
$O
$L
$ST
$C
yes
yes
EOF

	
#Step 2
    echo "############ Adding CA"
    keytool -storepass "$PASS" -keypass "$PASS" -keystore ./server/server.truststore.jks -alias CARoot -import -file ca_cert <<EOF
yes
EOF
    
#Step 3
    echo "############ Export certificate"
    keytool -storepass "$PASS" -keypass "$PASS" -keystore ./server/server.keystore.jks -alias localhost -certreq -file cert-file

    echo "############ Sign certificate"
    openssl x509 -req -CA ca_cert -CAkey ca_cert.key -in cert-file -out cert-signed -days $VALIDITY -CAcreateserial -passin "pass:$PASS"


    echo "############ Import CA"
    keytool -storepass "$PASS" -keypass "$PASS" -keystore ./server/server.keystore.jks -alias CARoot -import -file ca_cert <<EOF
yes
EOF
    
    echo "############ Import signed CA"
    keytool -storepass "$PASS" -keypass "$PASS" -keystore ./server/server.keystore.jks -alias localhost -import -file cert-signed    

    echo "############ Creating client truststore"
    [[ -f client.truststore.jks ]] || keytool -storepass "$PASS" -keypass "$PASS" -keystore ./client/client.truststore.jks -alias CARoot -import -file ca_cert <<EOF
yes
EOF

    echo "############ Generating key"
    keytool -storepass "$PASS" -keypass "$PASS" -keystore ./client/client.keystore.jks -alias localhost -validity $VALIDITY -genkey -keyalg RSA <<EOF
$CN
$OU
$O
$L
$ST
$C
yes
yes
EOF

    echo "########### Export certificate"
    keytool -storepass "$PASS" -keystore ./client/client.keystore.jks -alias localhost -certreq -file cert-file

    echo "########### Sign certificate"
    openssl x509 -req -CA ca_cert -CAkey ca_cert.key -in cert-file -out cert-signed -days $VALIDITY -CAcreateserial -passin pass:$PASS	

    echo "########### Import CA"
    keytool -storepass "$PASS" -keypass "$PASS" -keystore ./client/client.keystore.jks -alias CARoot -import -file ca_cert <<EOF
yes
EOF

    echo "########### Import signed CA"
    keytool -storepass "$PASS" -keypass "$PASS" -keystore ./client/client.keystore.jks -alias localhost -import -file cert-signed

    # Standard OpenSSL keys
    echo "############ Generating key"
    openssl genrsa -des3 -passout "pass:$PASS" -out ./client/client.key 2048 

    echo "############ Generating request"
    openssl req -passin "pass:$PASS" -passout "pass:$PASS" -key ./client/client.key -new -out ./client/client.req <<EOF
$C
$ST
$L
$O
$OU
$CN
.
$PASS
.
EOF

    echo "########### Signing key"
    openssl x509 -req -passin "pass:$PASS" -in ./client/client.req -CA ca_cert -CAkey ca_cert.key -CAserial ca_cert.srl -out ./client/client.pem -days $VALIDITY
    cp ca_cert ca_cert.key ./client
else
    echo "please input the username and password!"
fi 