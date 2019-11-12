FROM mysql:5.7 as build-mysql

WORKDIR /tmp/

COPY . .

COPY ./sources.list /etc/apt/sources.list

RUN apt update && apt install -y gcc make pkg-config libcurl4-openssl-dev libmysqlclient-dev

RUN cd /tmp/lib_mysqludf_urlencode && \
    ./configure --prefix=/tmp/lib_mysqludf_urlencode/build/ && \ 
    make && make install

RUN cd /tmp/mysql-udf-http-1.0 && \
    ./configure --prefix=/tmp/mysql-udf-http-1.0/build/ --with-mysql=/usr/bin/mysql_config && \
    make && make install

RUN cd /tmp/mysql-udf-json && \
    gcc $(/usr/bin/mysql_config --cflags) -shared -fPIC -o build/lib_mysqludf_json.so lib_mysqludf_json.c


FROM mysql:5.7

COPY ./sources.list /etc/apt/sources.list

RUN apt update && apt install -y libcurl4-openssl-dev && apt clean all

COPY --from=build-mysql /tmp/lib_mysqludf_urlencode/build/lib/ /usr/lib/mysql/plugin/
COPY --from=build-mysql /tmp/mysql-udf-http-1.0/build/lib/mysql/plugin/ /usr/lib/mysql/plugin/
COPY --from=build-mysql /tmp/mysql-udf-json/build/ /usr/lib/mysql/plugin/

COPY ./init.sql /docker-entrypoint-initdb.d/