#!/bin/bash
mount /dev/sda /mnt
useradd qq
chown -R qq:qq /mnt/
cd disk-stress
./disk-stress config
cd ../ltp-filesystems
./runalltests.sh -i 1024 -m 128 -p -q  -l /tmp/resultlog.11402 -d /mnt
cd ../bonnie++-1.98
./bonnie++  -d /mnt -u qq 
cd ..

