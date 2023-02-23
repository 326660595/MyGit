#!/bin/bash

CURRENT_DIR=$(cd $(dirname $0); pwd)

cmake -B build 

cd $CURRENT_DIR/build

#make
make

#install
make install
