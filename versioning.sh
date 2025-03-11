#!/usr/bin/bash

if [ -z "$1" ]; then
  echo "Usage: $0 <branch_name>"
  exit 1
fi

branch="$1"
year=$(date -u +%Y)
month=$(date -u +%m)
day=$(date -u +%d)
hour=$(date -u +%H)
minute=$(date -u +%M)

cat <<EOF > include/version.hpp
// version.h
//
// Contains version info passed in immediately before compile time.
#ifndef VERSION_H
#define VERSION_H
COMPILE_DATE=$year-$month-$day
COMPILE_TIME=$hour:$minute
COMPILE_BRANCH=$branch
#endif //VERSION_H
EOF