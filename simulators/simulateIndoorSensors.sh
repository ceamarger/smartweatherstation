#!/bin/bash

max_kelvin=323
min_kelvin=223
delta=$((max_kelvin - min_kelvin))

echo "max temp kelvin = $max_kelvin"
echo "min temp kelvin = $min_kelvin"

while [ true ]
do
    nombre=$(($(($(($RANDOM % delta)) + min_kelvin)) * 100))
    mosquitto_pub -t sensors/temperature -m "34276f89-2a8a-4882-9a9e-5cd8510febb9 $nombre"
    mosquitto_pub -t sensors/humidity -m "34276f89-2a8a-4882-9a9e-5cd8510febb9 0"

    sleep 2
done
