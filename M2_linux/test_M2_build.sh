#!/bin/bash
cd disk-stress
make
cd ../ltp-filesystems
make 
make install
cd ../bonnie++-1.98
./configure
make
