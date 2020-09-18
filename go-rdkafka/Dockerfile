FROM golang

ARG VERSION=1.3.0

COPY librdkafka-${VERSION}.tar.gz /tmp

RUN cd /tmp && tar -zxvf librdkafka-${VERSION}.tar.gz && \
cd librdkafka-${VERSION} && ./configure --install-deps

RUN cd /tmp/librdkafka-${VERSION} && /make && make install && ldconfig

RUN rm -rf /tmp/librdkafka-${VERSION}.tar.gz /tmp/librdkafka-${VERSION}