#!/usr/bin/env bash

branch="$1"
basefilename="pinglite-"
compiledat=$(date -u +%Y-%m-%d)
compiletim=$(date -u +%H:%M:%S)

getCompileDate() {
    compiledat=$1
    compiletim=$2
    branch=$3

    L1="Compiled on $compiledat\n"
    L2="at $compiletim\n"
    L3="from branch: $branch.\n"

    return "$L1$L2$L3"
}

ensureFilePermissions() {
    chmod 755 ./usr/bin/pinglite
    chomod 755 ./usr/lib/*.sh
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
echo $(getCompileDate $compiledat $compiletim $branch) > ./var/lib/pinglite/VERSION

#Place license information in package location.
cp ./LICENSE ./var/lib/pinglite/LICENSE

#Set executables to executable.
ensureFilePermissions

tar -cvf $filename.tar ./usr ./var
