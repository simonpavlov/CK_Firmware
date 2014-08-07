#!/bin/bash

SRCDIR=`dirname ${BASH_SOURCE[0]}`
USAGE="USAGE: mk.sh [COMMAND]\n\tc clean - Clean directory\n\tb build - Build project\
\n\tr run - Run project"

function build() {
    echo "mkdir ${SRCDIR}/build; cd ${SRCDIR}/build && cmake .. && make"
    mkdir ${SRCDIR}/build; cd build && cmake .. && make && cd ..
}

function clean() {
    echo rm -rf $SRCDIR/build
    rm -rf $SRCDIR/build
}

function run() {
   build && cd $SRCDIR/data && ../build/src/main;
}

if [[ $2 != "" || $1 == "" ]]; then echo -e $USAGE && exit 1; fi

case $1 in
    "b" | "build")
        build ;;
    "c" | "clean")
        clean ;;
    "r" | "run")
        run;;
esac
