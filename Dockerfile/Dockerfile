FROM ubuntu:20.04

COPY sources.list /root/

RUN ls /root/ \
    && mv /etc/apt/sources.list  /etc/apt/sources.list.back \
    && mv /root/sources.list /etc/apt/sources.list \
    && apt-get update \
    && apt-get -y --assume-yes install gcc g++ make cmake vim \    
    && apt-get -y --assume-yes install autoconf automake libtool \
    && apt-get -y --assume-yes install libffi-dev \
    && apt-get -y --assume-yes install curl wget \
    && apt-get -y --assume-yes install libgoogle-glog-dev \
    && apt-get -y --assume-yes install clang