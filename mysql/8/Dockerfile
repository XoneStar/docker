FROM mysql:8 as build-mysql

WORKDIR /tmp/

COPY . .

COPY ./sources.list /etc/apt/sources.list

RUN apt update && apt install -y gcc make pkg-config libcurl4-openssl-dev libmysqlclient-dev

RUN cd /tmp/mysql-udf-http-1.0 && \
    ./configure --prefix=/tmp/mysql-udf-http-1.0/build/ --with-mysql=/usr/bin/mysql_config && \
    make && make install


FROM mysql:8 

COPY ./sources.list /etc/apt/sources.list

RUN apt update && apt install -y libcurl4-openssl-dev && apt clean all

COPY --from=build-mysql /tmp/mysql-udf-http-1.0/build/lib/mysql/plugin/ /usr/lib/mysql/plugin/

COPY ./init.sql /docker-entrypoint-initdb.d/

