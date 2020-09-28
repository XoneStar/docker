FROM golang:alpine

ARG VERSION=1.5.0

RUN cd /tmp && wget -O librdkafka-${VERSION}.tar.gz https://codeload.github.com/edenhill/librdkafka/tar.gz/v${VERSION}

RUN tar -zxvf /tmp/librdkafka-${VERSION}.tar.gz -C /tmp

RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.tuna.tsinghua.edu.cn/g' /etc/apk/repositories

RUN RUN apk add --no-cache bash make pkgconfig g++ zlib-dev openssl-dev cyrus-sasl-dev zstd-dev zstd-static lz4-dev

RUN cd /tmp/librdkafka-${VERSION} && ./configure && make && make install && ldconfig

RUN rm -rf /tmp