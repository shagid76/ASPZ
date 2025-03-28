FROM debian:latest

RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY stack_limit_demo.c .
RUN gcc stack_limit_demo.c -o stack_limit_demo
CMD ["bash", "-c", "ulimit -s 1024 && ./stack_limit_demo"]