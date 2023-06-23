# FROM debian:bullseye-slim


# # APT Update
# RUN apt-get update && apt-get upgrade -y

# # APT install (base) packages
# RUN apt-get install -y build-essential cmake libboost-all-dev pkg-config
# RUN apt-get install libsdl2

# # Get cppcheck dependencies from stable; that's good enough
# RUN echo "deb-src http://deb.debian.org/debian bullseye main" >>/etc/apt/sources.list
# RUN apt-get update
# RUN apt-get build-dep -y cppcheck
# # Download cppcheck source code, build and install
# COPY CMakeLists.txt .
# ENV CXX=/usr/bin/g++



# RUN cmake . -B build
# RUN cd build && make


# # APT install additional packages
# RUN apt-get install -y --no-install-recommends \
#     locales

# WORKDIR /smart_house


# COPY . /smart_house

# CMD ["./smart_house"]



FROM ubuntu:latest

ENV CMAKE_MODULE_PATH="/usr/share/cmake/Modules"

RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    libsdl2-dev \
    libsdl2-mixer-dev

WORKDIR /smart_house

COPY . /smart_house