#!/bin/bash
make -C ./code/host
DEVICE=$(sudo dmesg | tail | grep -oe "tty\w*")
sudo ./code/host/host $DEVICE
