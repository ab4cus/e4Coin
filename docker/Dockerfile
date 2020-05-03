FROM debian:stretch
LABEL maintainer="e4Coin Developers <dev@e4coin.org>"
LABEL description="Dockerised e4CoinCore, built from Travis"

RUN apt-get update && apt-get -y upgrade && apt-get clean && rm -fr /var/cache/apt/*

COPY bin/* /usr/bin/
