#!/usr/bin/bash

branch="$1"
year=$(date -u +%Y)
month=$(date -u +%m)
day=$(date -u +%d)
hour=$(date -u +%H)
minute=$(date -u +%M)

COMPILE_DATE=$year-$month-$day
COMPILE_TIME=$hour:$minute
COMPILE_BRANCH=$branch

L1="// version.h\n"
L2="//\n"
L3="// Contains version info passed in immedietly before compile time.\n"
L4="#ifndef VERSION_H\n"
L5="#define VERSION_H\n"
L6="COMPILE_DATE="+$COMPILE_DATE+"\n"
L7="COMPILE_TIME="+$COMPILE_TIME+"\n"
L8="COMPILE_BRANCH="+$COMPILE_BRANCH+"\n"
L9="#endif //VERSION_H\n"


echo $L1 > include/version.hpp
echo $L2 > include/version.hpp
echo $L3 > include/version.hpp
echo $L4 > include/version.hpp
echo $L5 > include/version.hpp
echo $L6 > include/version.hpp
echo $L7 > include/version.hpp
echo $L8 > include/version.hpp
echo $L9 > include/version.hpp
