#!/bin/bash

ssh -i ~/.ssh/id_rsa pi@192.168.2.100 'echo raspberry | sudo reboot'
ssh -i ~/.ssh/id_rsa pi@192.168.2.101 'echo raspberry | sudo reboot'
ssh -i ~/.ssh/id_rsa pi@192.168.2.102 'echo raspberry | sudo reboot'
ssh -i ~/.ssh/id_rsa pi@192.168.2.103 'echo raspberry | sudo reboot'

sleep 120 # 2 minutes

if [ ! "$(pidof -x LEDWallVideoPlayer)" ]; then
	BASEDIR=$(dirname $0)
	"$BASEDIR/LEDWallVideoPlayer" > ~/Desktop/out.txt
fi
