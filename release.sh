#!/usr/bin/bash

branch="$1"
basefilename="pinglite"
year=$(date -u +%Y)
month=$(date -u +%m)
day=$(date -u +%d)
hour=$(date -u +%H)
minute=$(date -u +%M)

echo "Compiled and packaged on $year-$month-$day at $hour:$minute UTC from the $branch branch." > VERSION

#Add each filename to be included in final package, separated by a space.
IncludedFilenames="$basefilename LICENSE VERSION"

tar -cvf $basefilename-$branch-$year.$month.$day-$hour.$minute.tar $IncludedFilenames
