FROM golang

ARG VERSION=1.5.0

RUN cd /tmp && wget -O librdkafka-${VERSION}.tar.gz https://codeload.github.com/edenhill/librdkafka/tar.gz/v${VERSION} && \
tar -zxvf librdkafka-${VERSION}.tar.gz && \
cd librdkafka-${VERSION} && ./configure --install-deps

RUN cd /tmp/librdkafka-${VERSION} && make && make install && ldconfig

RUN rm -rf /tmp/librdkafka-${VERSION}.tar.gz /tmp/librdkafka-${VERSION}