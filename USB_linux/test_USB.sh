#!/bin/bash

mount /dev/sda /mnt
cd disk-stress
make 
./disk-stress config
cd ../ltp-filesystems
make 
make install
./runalltests.sh -i 1024 -m 128 -p -q  -l /tmp/resultlog.11402 -d /mnt
cd ../bonnie++-1.98
./configure
make
./bonnie++ -d /mnt
