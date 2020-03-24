FROM golang

COPY librdkafka-1.3.0.tar.gz /tmp

RUN cd /tmp && tar -zxvf librdkafka-1.3.0.tar.gz && \
cd librdkafka-1.3.0 && ./configure --install-deps

RUN cd /tmp/librdkafka-1.3.0 && /make && make install && ldconfig

RUN rm -rf /tmp/librdkafka-1.3.0.tar.gz /tmp/librdkafka-1.3.0