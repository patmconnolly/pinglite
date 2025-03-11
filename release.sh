#!/usr/bin/bash

branch="$1"
basefilename="pinglite"
year=$(date -u +%Y)
month=$(date -u +%m)
day=$(date -u +%d)
hour=$(date -u +%H)
minute=$(date -u +%M)

#Add each filename to be included in final package, separated by a space.
IncludedFilenames="$basefilename LICENSE"

if [[ "$branch" == "dev" ]]; then
	outputfile="$basefilename-$branch-$year.$month.$day-$hour.$minute.tar"
elif [[ "$branch" == "nightly" ]]; then
	outputfile="$basefilename-$branch-$year.$month.$day.tar"
elif [[ "$branch" == "stable" ]]; then
	outputfile="$basefilename-$branch-$year.$month.$day.tar"
fi


tar -cvf $outputfile $IncludedFilenames
