#!/usr/bin/bash

branch="$1"
compileos="$2"
basefilename="pinglite"
year=$(date -u +%Y)
month=$(date -u +%m)
day=$(date -u +%d)
hour=$(date -u +%H)
minute=$(date -u +%M)

#Add each filename to be included in final package, separated by a space.
IncludedFilenames="$basefilename"

if [[ "$branch" == "development" ]]; then
	outputfile="$basefilename-dev-$year.$month.$day-$hour.$minute.$compileos.tar"
elif [[ "$branch" == "nightly" ]]; then
	outputfile="$basefilename-$branch-$year.$month.$day.$compileos.tar"
elif [[ "$branch" == "stable" ]]; then
	outputfile="$basefilename-$branch-$year.$month.$day.$compileos.tar"
fi


tar --owner 0 --group 0 -cvf $outputfile $IncludedFilenames
