FROM alpine:latest
WORKDIR /app

RUN apk add --no-cache build-base git

COPY Makefile main.c ./
COPY src/*.c src/*.h ./src/
COPY test/*.c ./test/
COPY externals/unity/src/*.c externals/unity/src/*.h ./externals/unity/src/

RUN make
