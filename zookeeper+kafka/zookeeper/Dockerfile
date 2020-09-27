FROM java

ARG ZOOKEEPER_VERSION=3.6.2

WORKDIR /opt/apache-zookeeper-${ZOOKEEPER_VERSION}

RUN wget -O apache-zookeeper-${ZOOKEEPER_VERSION}-bin.tar.gz https://mirrors.tuna.tsinghua.edu.cn/apache/zookeeper/zookeeper-${ZOOKEEPER_VERSION}/apache-zookeeper-${ZOOKEEPER_VERSION}-bin.tar.gz \
    && tar zxvf apache-zookeeper-${ZOOKEEPER_VERSION}-bin.tar.gz \
    && mv apache-zookeeper-${ZOOKEEPER_VERSION}-bin/* . \
    && rm -rf apache-zookeeper-${ZOOKEEPER_VERSION}-bin \
    && chmod -R 755 . \
    && cp conf/zoo_sample.cfg conf/zoo.cfg \
    && rm -f apache-zookeeper-${ZOOKEEPER_VERSION}-bin.tar.gz

EXPOSE 2181
ENTRYPOINT [ "bash", "./bin/zkServer.sh", "start-foreground", "./conf/zoo.cfg" ]
