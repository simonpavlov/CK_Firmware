#!/bin/bash

SRCDIR=`pwd`/`dirname ${BASH_SOURCE[0]}`
USAGE="USAGE: mk.sh [COMMAND]\n\t-c --clean\t- Clean directory\n\t-b --build\t- Build project\
\n\t-r --run\t- Run menu test\n\t-rv --run-vlg\t- Run wiht valgrind\n\t-k --kill\t- Kill menu test"

function build() {
    if [ ${SRCDIR}/data/the_menu_structure/menu.md -nt ${SRCDIR}/data/the_menu_structure/menu.md.h ];
    then
        echo "${SRCDIR}/utils/menu_gen.py ${SRCDIR}/data/the_menu_structure/menu.md > \
${SRCDIR}/data/the_menu_structure/menu.md.h"
        ${SRCDIR}/utils/menu_gen.py ${SRCDIR}/data/the_menu_structure/menu.md > \
${SRCDIR}/data/the_menu_structure/menu.md.h
    fi

    if ! [ -d ${SRCDIR}/build/ ]; then
        echo "build not found!"
        echo "mkdir ${SRCDIR}/build;"
        mkdir ${SRCDIR}/build;
    fi

    echo "cd ${SRCDIR}/build && cmake .. && make"
    cd ${SRCDIR}/build && cmake .. && make && cd ..
}

function clean() {
    echo rm -rf $SRCDIR/build $SRCDIR/data/the_menu_structure/menu.md.h
    rm -rf $SRCDIR/build $SRCDIR/data/the_menu_structure/menu.md.h
}

function run() {
   # echo "cd $SRCDIR/data && ../build/src/tests/menu_test & "
   build && cd $SRCDIR/data && ../build/src/tests/menu_test &
}

function run_vlg() {
   # echo "cd $SRCDIR/data && valgrind -q ../build/src/tests/menu_test & "
   build && cd $SRCDIR/data && valgrind -q ../build/src/tests/menu_test &
}

function kill_test() {
   kill -31 `ps | grep menu_test | awk '{print $1}'`
}

if [[ $2 != "" || $1 == "" ]]; then echo -e $USAGE && exit 1; fi

case $1 in
    "-b" | "--build")
        build ;;
    "-c" | "--clean")
        clean ;;
    "-r" | "--run")
        run;;
    "-k" | "--kill")
        kill_test;;
     *)
	echo -e $USAGE
esac
