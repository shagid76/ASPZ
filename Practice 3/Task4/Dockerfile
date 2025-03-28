FROM debian:latest

RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY lottery_simulation.c .
RUN gcc lottery_simulation.c -o lottery_simulation
CMD ["bash", "-c", "ulimit -t 2 && ./lottery_simulation"]