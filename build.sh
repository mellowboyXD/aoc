#!/bin/bash

CMD=$1
OPT=$2
SRC_FOLDER="src"
SRC="main.c"
TARGET="$SRC_FOLDER/$OPT/$SRC"
CC=gcc
CFLAGS="-Wall"
OUT="$SRC_FOLDER/$OPT/a.out"
LOG="[INFO]:"
ERROR="[ERROR]:"

if [[ -n $CMD ]]; then
	if [[ $CMD == "new" && -n $OPT ]]; then
		mkdir -p "$SRC_FOLDER/$OPT"
		touch "$SRC_FOLDER/$OPT/$SRC"
		echo "$LOG $OPT folder created"
	elif [[ $CMD == "run" && -n $OPT ]]; then
		if [[ -e $TARGET ]]; then
			echo "$LOG Compiling file"
			$CC $CFLAGS -o $OUT $TARGET
			if [[ $? -eq 0 ]]; then
				echo "$LOG Running file"
				echo ""
				./$OUT
			else
				echo "$ERROR There were build errors"
			fi
		else
			echo " $ERROR $TARGET missing"
		fi
	elif [[ $CMD == "clean" && -e $TARGET ]]; then
		echo "$LOG Cleaning files"
		rm $OUT
	else
		echo "$ERROR Missing arguments"
	fi
else
	echo "$ERROR Available commands: new, run, clean"
fi

