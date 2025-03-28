
FROM debian:latest

RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN gcc dice_roll.c -o dice_roll

CMD ["/bin/bash", "-c", "\
    echo 'Starting dice roll simulation with file size limit'; \
    ./dice_roll; \
    echo 'Contents of dice_rolls.txt:'; \
    cat dice_rolls.txt"]