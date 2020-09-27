#!/bin/bash

if [ "$KAFKA_ZOOKEEPER_CONNECT" ]; then
   sed -i "s/zookeeper.connect=zookeeper:2181/zookeeper.connect=$KAFKA_ZOOKEEPER_CONNECT/g" "$PWD"/config/server.properties
fi

if [ "$KAFKA_ENV_KAFKA_ADVERTISED_HOST_NAME" ] && [ "$KAFKA_ENV_KAFKA_ADVERTISED_PORT" ]; then
    sed -i "s/PLAINTEXT:\/\/x.x.x.x:9091,SSL:\/\/x.x.x.x:9092/PLAINTEXT:\/\/$KAFKA_ENV_KAFKA_ADVERTISED_HOST_NAME:9091,SSL:\/\/$KAFKA_ENV_KAFKA_ADVERTISED_HOST_NAME:$KAFKA_ENV_KAFKA_ADVERTISED_PORT/g" "$PWD"/config/server.properties
fi

JMX_PORT=9999 "$PWD"/bin/kafka-server-start.sh "$PWD"/config/server.properties