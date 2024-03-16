FROM ubuntu:22.04

RUN apt-get update && apt-get install -y sqlite3 libsqlite3-dev

COPY shared /shared
COPY db/src/db.c /db/src/

WORKDIR /db

RUN cc -O2 -c -o db.o db.c -I/shared/include -lsqlite3

WORKDIR /

COPY api/src/ api/src/
COPY lb/ lb/

WORKDIR /app

RUN cc -O2 -o app api.c db.o /shared/src/common.o -lsqlite3 -I/shared/include

COPY docker-compose.yml .

EXPOSE 8080

CMD ["./app"]