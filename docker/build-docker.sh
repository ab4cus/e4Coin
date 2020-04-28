#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR/..

DOCKER_IMAGE=${DOCKER_IMAGE:-e4coinpay/e4coind-develop}
DOCKER_TAG=${DOCKER_TAG:-latest}

BUILD_DIR=${BUILD_DIR:-.}

rm docker/bin/*
mkdir docker/bin
cp $BUILD_DIR/src/e4coind docker/bin/
cp $BUILD_DIR/src/e4coin-cli docker/bin/
cp $BUILD_DIR/src/e4coin-tx docker/bin/
strip docker/bin/e4coind
strip docker/bin/e4coin-cli
strip docker/bin/e4coin-tx

docker build --pull -t $DOCKER_IMAGE:$DOCKER_TAG -f docker/Dockerfile docker
