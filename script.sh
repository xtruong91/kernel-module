#!/bin/bash

echo "building kernel module and install it";

make 
sudo insmod simplemodule.ko
lsmod | grep simplemodule
sudo rmmod simplemodule.ko
