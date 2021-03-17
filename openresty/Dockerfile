FROM debian:10-slim as build-env

ARG VERSION="1.19.3.1"
ARG CONFIG_OPTIONS="\
    --with-compat \
    --with-file-aio \
    --with-http_addition_module \
    --with-http_auth_request_module \
    --with-http_dav_module \
    --with-http_flv_module \
    --with-http_geoip_module=dynamic \
    --with-http_gunzip_module \
    --with-http_gzip_static_module \
    --with-http_image_filter_module=dynamic \
    --with-http_mp4_module \
    --with-http_random_index_module \
    --with-http_realip_module \
    --with-http_secure_link_module \
    --with-http_slice_module \
    --with-http_ssl_module \
    --with-http_stub_status_module \
    --with-http_sub_module \
    --with-http_v2_module \
    --with-http_xslt_module=dynamic \
    --with-http_stub_status_module \
    --with-ipv6 \
    --with-mail \
    --with-mail_ssl_module \
    --with-md5-asm \
    --with-pcre-jit \
    --with-sha1-asm \
    --with-stream \
    --with-stream_ssl_module \
    --with-threads \
    "

RUN sed -i 's/security.debian.org/mirrors.tuna.tsinghua.edu.cn/g' /etc/apt/sources.list \ 
&& sed -i 's/deb.debian.org/mirrors.tuna.tsinghua.edu.cn/g' /etc/apt/sources.list

RUN apt update && apt install perl make build-essential curl tar -y

RUN apt install libpcre3-dev libssl-dev zlib1g-dev libxml2-dev libxslt-dev libgd-dev libgeoip-dev -y 

RUN curl -fSL https://openresty.org/download/openresty-${VERSION}.tar.gz -o /tmp/openresty-${VERSION}.tar.gz

RUN tar -xzvf /tmp/openresty-${VERSION}.tar.gz -C /tmp && cd /tmp/openresty-${VERSION} \ 
&& ./configure ${CONFIG_OPTIONS} && make && make install

FROM debian:10-slim

RUN sed -i 's/security.debian.org/mirrors.tuna.tsinghua.edu.cn/g' /etc/apt/sources.list \ 
&& sed -i 's/deb.debian.org/mirrors.tuna.tsinghua.edu.cn/g' /etc/apt/sources.list

RUN DEBIAN_FRONTEND=noninteractive apt update \ 
&& DEBIAN_FRONTEND=noninteractive apt install openssl zlib1g libpcre3 \
libxml2 libgd3 libgeoip1 libxslt1.1 libssl1.1 libstdc++6 -y --no-install-recommends \
&& rm -rf /var/lib/apt/lists/*

COPY --from=build-env /usr/local/openresty /usr/local/openresty

ENTRYPOINT ["/usr/local/openresty/bin/openresty", "-g", "daemon off;"]