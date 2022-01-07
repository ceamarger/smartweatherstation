#!/bin/bash

uuid=$1

max_kelvin=323
min_kelvin=223
delta=$((max_kelvin - min_kelvin))

echo "max temp kelvin = $max_kelvin"
echo "min temp kelvin = $min_kelvin"

while [ true ]
do
    nombre=$(($(($(($RANDOM % delta)) + min_kelvin)) * 100))
    mosquitto_pub -t sensors/temperature -m "$uuid $nombre"
    mosquitto_pub -t sensors/humidity -m "$uuid 0"

    sleep 2
done
