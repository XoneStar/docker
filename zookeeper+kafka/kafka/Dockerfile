FROM java as kafka-build

ARG SCALA_VERSION=2.12
ARG KAFKA_VERSION=2.6.0
ARG SSL_CN="kafka"
ARG SSL_PASS="kafka@212260"

WORKDIR /opt/kafka_${SCALA_VERSION}-${KAFKA_VERSION}

COPY ./start_kafka.sh ./start_kafka.sh
COPY ./gen-ssl-certs.sh /ssl/gen-ssl-certs.sh

RUN chmod +x ./start_kafka.sh \
    && wget -O /tmp/kafka_${SCALA_VERSION}-${KAFKA_VERSION}.tgz https://mirrors.tuna.tsinghua.edu.cn/apache/kafka/${KAFKA_VERSION}/kafka_${SCALA_VERSION}-${KAFKA_VERSION}.tgz \
    && tar zxvf /tmp/kafka_${SCALA_VERSION}-${KAFKA_VERSION}.tgz -C /tmp \
    && mv /tmp/kafka_${SCALA_VERSION}-${KAFKA_VERSION}/* . \
    && chmod -R +x ./bin \
    && chmod +x /ssl/gen-ssl-certs.sh \
    && cd /ssl \
    && ./gen-ssl-certs.sh ${SSL_CN} ${SSL_PASS}

COPY ./server.properties ./config/server.properties

FROM openjdk:8-jre-slim

ARG SCALA_VERSION=2.12
ARG KAFKA_VERSION=2.6.0

WORKDIR /opt/kafka_${SCALA_VERSION}-${KAFKA_VERSION}

COPY --from=kafka-build /opt /opt
COPY --from=kafka-build /ssl /ssl

EXPOSE 9092
EXPOSE 9091

ENTRYPOINT [ "bash", "./start_kafka.sh" ]