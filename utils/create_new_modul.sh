#!/bin/bash

SRCDIR=`pwd`/`dirname ${BASH_SOURCE[0]}`/..

# echo $SRCDIR

if ! [[ $# == 2 ]]; then
	echo "USAGE: create_new_modul.sh [LIB_NAME] [MODUL_NAME]"
else

	LIB_NAME=$1
	MODUL_NAME=$2
	MODUL_NAME_UP=`echo "$2" | sed 's/[[:lower:]]/\u&/g'`

	HEADER=$SRCDIR/src/lib/$LIB_NAME/$MODUL_NAME.h
	CPP_FILE=$SRCDIR/src/lib/$LIB_NAME/src/$MODUL_NAME.cpp

	CMAKEFILE=$SRCDIR/src/lib/$LIB_NAME/CMakeLists.txt

	# echo LIB_NAME: $LIB_NAME
	# echo MODUL_NAME: $MODUL_NAME
	# echo MODUL_NAME_UP: $MODUL_NAME_UP

	# echo HEADER: $HEADER
	# echo CPP_FILE: $CPP_FILE


	touch $HEADER
	echo "#ifndef "$MODUL_NAME_UP >> $HEADER
	echo "#define "$MODUL_NAME_UP >> $HEADER
	echo >> $HEADER
	echo >> $HEADER
	echo >> $HEADER
	echo "#endif "//$MODUL_NAME_UP >> $HEADER

	touch $CPP_FILE
	echo "#include \"../$MODUL_NAME.h\"" >> $CPP_FILE
	echo >> $CPP_FILE

	awk 'FNR == 1 {print}' $CMAKEFILE > buffer
	echo -e "\tsrc/$MODUL_NAME.cpp" >> buffer
	awk 'FNR >= 2 {print}' $CMAKEFILE >> buffer
	mv buffer $CMAKEFILE

fi