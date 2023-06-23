FROM ubuntu:latest

ENV CMAKE_MODULE_PATH="/usr/share/cmake/Modules"

ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US:en
ENV LC_ALL=en_US.UTF-8


RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    libsdl2-dev \
    libsdl2-mixer-dev

RUN apt-get install libfribidi-dev

WORKDIR /smart_house

COPY . /smart_house