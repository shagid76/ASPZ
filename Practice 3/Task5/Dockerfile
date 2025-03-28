FROM debian:latest

RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY file_copy.c .
RUN gcc file_copy.c -o file_copy
CMD ["./file_copy"]