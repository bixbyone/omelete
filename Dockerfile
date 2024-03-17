FROM bash:5.1.4-alpine3.16

COPY api/app.sh /app.sh 
COPY api/libcodorna.so /libcodorna.so

ENTRYPOINT ["/bin/bash", "/app.sh"]