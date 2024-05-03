#!/bin/bash
make -C ./code/host
DEVICE="/dev/$(sudo dmesg | tail | grep -oe "tty\w*")"
sudo ./code/host/build/host $DEVICE
