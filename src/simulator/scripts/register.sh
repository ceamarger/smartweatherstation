#!/bin/bash

uuid=$1
mosquitto_pub -t sensors/register -m "$uuid"
echo "Register uuid: $uuid"
