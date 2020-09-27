FROM java

ARG SCALA_VERSION=2.12
ARG KAFKA_VERSION=2.6.0
ARG SSL_CN="kafka"
ARG SSL_PASS="kafka@212260"

WORKDIR /opt/kafka_${SCALA_VERSION}-${KAFKA_VERSION}

COPY ./startup ./startup
COPY ./gen-ssl-certs.sh ./gen-ssl-certs.sh

RUN chmod +x ./startup \
    && chmod +x ./gen-ssl-certs.sh \
    && wget -O kafka_${SCALA_VERSION}-${KAFKA_VERSION}.tgz https://mirrors.tuna.tsinghua.edu.cn/apache/kafka/${KAFKA_VERSION}/kafka_${SCALA_VERSION}-${KAFKA_VERSION}.tgz \
    && tar zxvf kafka_${SCALA_VERSION}-${KAFKA_VERSION}.tgz \
    && mv kafka_${SCALA_VERSION}-${KAFKA_VERSION}/* . \
    && rm -rf kafka_${SCALA_VERSION}-${KAFKA_VERSION} \
    && chmod -R +x ./bin \
    && rm -f kafka_${SCALA_VERSION}-${KAFKA_VERSION}.tgz \
    && ./gen-ssl-certs.sh ${SSL_CN} ${SSL_PASS} \
    && mkdir /ssl \
    && mv ./server/* /ssl

COPY ./server.properties ./config/server.properties

EXPOSE 9092
EXPOSE 9091

ENTRYPOINT [ "bash", "./startup" ]
