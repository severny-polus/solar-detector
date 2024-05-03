#!/bin/bash
make -C ./code/host
DEVICE="/dev/$(sudo dmesg | tail | grep -oe "tty[A-Z0-9]*")"
sudo ./code/host/build/host $DEVICE
