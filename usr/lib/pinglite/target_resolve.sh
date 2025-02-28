#!/usr/bin/bash

## This checks if the host resolves to an IP.
## returns 1 if no
## returns 0 if yes

TARGETHOST=$1

host $TARGETHOST > /dev/null
if (( $? == 1 )); then
    exit 1
else
    exit 0
fi

exit 0