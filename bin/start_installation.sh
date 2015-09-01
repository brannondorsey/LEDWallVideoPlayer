#!/bin/bash

sleep 60 # 2 minutes

if [ ! "$(pidof -x LEDWallVideoPlayer)" ]; then
	BASEDIR=$(dirname $0)
	"$BASEDIR/LEDWallVideoPlayer" > ~/Desktop/out.txt
fi
