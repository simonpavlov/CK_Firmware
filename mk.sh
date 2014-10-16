#!/bin/bash

SRCDIR=`pwd`/`dirname ${BASH_SOURCE[0]}`
USAGE="USAGE: mk.sh [COMMAND] [TARGET]\n\t-c --clean\t\t- Clean directory\n\t-b --build\t\t- Build project\n\t-r --run TARGET\t\t- Run menu test\n\t-rv --run-vlg TARGET\t- Run wiht valgrind"

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
   # echo "cd $SRCDIR/data && ../build/src/tests/$1 & "
   build && cd $SRCDIR/data && ../build/src/tests/$1 &
}

function run_vlg() {
   # echo "cd $SRCDIR/data && valgrind -q ../build/src/tests/$1 & "
   build && cd $SRCDIR/data && valgrind -q ../build/src/tests/$1 &
}

if [[ $# == 1 ]]; then

    case $1 in
        "-b" | "--build")
            build;;
        "-c" | "--clean")
            clean;;
        "-r" | "--run")
            run "main_test";;
        "-rv" | "--run_vlg")
            run_vlg "main_test";;
        "-k" | "--kill")
            kill_test;;
         *)
        echo -e $USAGE
    esac

elif [[ $# == 2 ]]; then

    case $1 in
        "-r" | "--run")
            run $2;;
        "-rv" | "--run_vlg")
            run_vlg $2;;
         *)
        echo -e $USAGE
    esac

else
	echo -e $USAGE
fi
