FROM debian:latest

RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY memory_lock_demo.c .
RUN gcc memory_lock_demo.c -o memory_lock_demo
CMD ["bash", "-c", "ulimit -l 4096 && ./memory_lock_demo"]