FROM ubuntu:latest
WORKDIR /app

RUN apt update && apt install -y \
    build-essential \
    git \
    && rm -rf /var/lib/apt/lists/*

COPY . /app

RUN make -C /app
