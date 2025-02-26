#!/usr/bin/env bash
current_datetime=$(date -u +%Y.%m.%d-%H.%M.%S)
tar -cvf pinglite-v$current_datetime.tar ./usr ./var
