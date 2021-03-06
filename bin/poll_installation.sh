#!/bin/bash

# launches installation in background if it is not already running, 
# then exists with 0. Does nothing if installation is running, exits with 1

env DISPLAY=:0
echo $USER

BASENAME=$(dirname $0)

if [ !  "$(pidof -x LEDWallVideoPlayer)" ]; then
	echo "Installation NOT running. Launching $BASENAME/LEDWallVideoPlayer"
	"$BASENAME/LEDWallVideoPlayer" > ~/Desktop/test.out #>/dev/null 2>&1 &
	exit 0
else
	echo "Installation running."
	exit 1
fi
