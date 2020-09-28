FROM alpine as librdkafka-build

ARG VERSION=1.5.0

RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.tuna.tsinghua.edu.cn/g' /etc/apk/repositories

RUN apk add --no-cache bash make pkgconfig g++ zlib-dev openssl-dev cyrus-sasl-dev zstd-dev zstd-static lz4-dev

RUN wget -O /tmp/librdkafka-${VERSION}.tar.gz https://codeload.github.com/edenhill/librdkafka/tar.gz/v${VERSION}
RUN tar -zxvf /tmp/librdkafka-${VERSION}.tar.gz -C /tmp
RUN cd /tmp/librdkafka-${VERSION} && ./configure && make && make install

FROM alpine

RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.tuna.tsinghua.edu.cn/g' /etc/apk/repositories \
    && apk add --no-cache db libgcc lz4-libs libsasl libstdc++ zstd-libs

COPY --from=librdkafka-build /usr/local/lib /usr/local/lib