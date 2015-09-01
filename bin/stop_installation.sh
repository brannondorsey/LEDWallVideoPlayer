#!/bin/bash
pkill -f LEDWallVideoPlayer

sleep 1

BASEDIR=$(dirname $0)
"$BASEDIR/LEDWallClearPixels"
