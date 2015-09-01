#!/bin/bash
BASENAME=$(dirname $0)

while true
do
	"$BASENAME/poll_installation.sh"
	sleep 5
done
