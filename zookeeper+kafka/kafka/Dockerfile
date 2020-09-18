FROM java

WORKDIR /opt

COPY ./kafka_2.12-2.6.0.tgz .

COPY ./startup /bin/startup

RUN chmod +x /bin/startup \
    && tar zxvf kafka_2.12-2.6.0.tgz \
    && chmod -R +x ./kafka_2.12-2.6.0/bin \
    && rm -f kafka_2.12-2.6.0.tgz

COPY ./server.properties /opt/kafka_2.12-2.6.0/config/server.properties

EXPOSE 9092
EXPOSE 9091

CMD startup
