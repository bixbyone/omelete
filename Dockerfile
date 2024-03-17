FROM bash:5.1.4-alpine3.16

COPY api/app.sh /app.sh 
COPY api/libcodorna.so /libcodorna.so

ENTRYPOINT ["/bin/bash", "/app.sh"]

RUN clang-15 -O2 -o main main.c -lcjson -lmicrohttpd -lpthread -lregex
RUN apt-get update && apt-get install -y libpq-dev  # Instala a biblioteca PostgreSQL

FROM ${BUILDER_IMAGE} as builder

RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    clang-15 libcjson-dev \
    libmicrohttpd12 libmicrohttpd-dev \
    libpq-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

ENV C_INCLUDE_PATH="/usr/include/cjson:/usr/include/microhttpd:/usr/include/postgresql"

WORKDIR /app

COPY main.c .

RUN clang-15 -O2 -o main main.c -lpq -lcjson -lmicrohttpd

CMD ["/app/main"]