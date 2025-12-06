FROM --platform=linux/amd64 ubuntu:22.04

RUN apt update && apt install -y \
    build-essential \
	curl \
    clang \
    valgrind

WORKDIR /project