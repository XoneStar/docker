FROM java

WORKDIR /opt

COPY ./apache-zookeeper-3.6.2-bin.tar.gz .

RUN tar zxvf apache-zookeeper-3.6.2-bin.tar.gz \
    && mv apache-zookeeper-3.6.2-bin apache-zookeeper-3.6.2 \
    && chmod -R 755 apache-zookeeper-3.6.2/ \
    && cp apache-zookeeper-3.6.2/conf/zoo_sample.cfg apache-zookeeper-3.6.2/conf/zoo.cfg \
    && rm -f apache-zookeeper-3.6.2-bin.tar.gz

EXPOSE 2181
CMD [ "bash", "/opt/apache-zookeeper-3.6.2/bin/zkServer.sh", "start-foreground", "/opt/apache-zookeeper-3.6.2/conf/zoo.cfg" ]
