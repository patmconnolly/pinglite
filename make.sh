#!/usr/bin/env bash

branch="$1"
basefilename="pinglite"
compiledat=$(date -u +%Y-%m-%d)
compiletim=$(date -u +%H:%M:%S)

getCompileDate() {
    compiledat=$1
    compiletim=$2
    branch=$3

    VERSION="Compiled on $compiledat at $compiletim from branch: $branch."
    echo $VERSION > ./var/lib/pinglite/VERSION
    return 0
}

ensureFilePermissions() {
    # Main executable
    chmod 755 ./usr/bin/pinglite

    #Helper executables, called out one by one for security purposes.
    chmod 755 ./usr/lib/alert_api.sh
    chmod 755 ./usr/lib/alert_handler.sh
    chmod 755 ./usr/lib/target_ping.sh
    chmod 755 ./usr/lib/target_resolve.sh

    return 0
}

if [ $branch == "development" ]; then
    filename=$basefilename-dev-$compiledat
elif [ $branch == "nightly" ]; then
    current_datetime=$(date -u +%Y.%m.%d)
    filename=$basefilename-nightly-$current_datetime
elif [ $branch == "stable" ]; then
    current_datetime=$(date -u +%Y.%m.%d)
    filename=$basefilename-stable-$current_datetime
else
    echo "Invalid Make Command!"
    echo "---------------------"
    echo "Valid options are:"
    echo "$0 development"
    echo "$0 nightly"
    echo "$0 stable"
    exit 1
fi

#Place compile date/time information in VERSION file.
getCompileDate $compiledat $compiletim $branch

#Place license information in package location.
cp ./LICENSE ./var/lib/pinglite/LICENSE

#Set executables to executable.
ensureFilePermissions

tar -cvf $filename.tar ./usr ./var
