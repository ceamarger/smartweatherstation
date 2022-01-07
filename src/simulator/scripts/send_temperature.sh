#!/bin/bash

if [ "$#" -ne 2 ]; then
	echo "Missing parameters : ./send_temperature uuid temperature"
	exit
fi

uuid=$1
temperature=$2

echo "Warning : temperature should be in Kelvin"
mosquitto_pub -t sensors/temperature -m "$uuid $temperature"
