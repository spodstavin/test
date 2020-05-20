#!/bin/bash

cd iperf-3.7
./configure
make
make install
iperf3 -c 192.168.1.1 -i 1 -t 30
iperf3 -c 192.168.1.1 -i 1 -t 20 -R
iperf3 -c 192.168.1.1 -i 1 -t 20 -w 32K -P 4
iperf3 -c 192.168.1.1 -u -i 1 -b0
iperf3 -c 192.168.1.1 -i.5 -O 2
iperf3 -Z -c 192.168.1.1
iperf3 -c 192.168.1.1
iperf3 -c 192.168.1.1 -J
iperf3 -c 192.168.1.1 -i 1 -t 30 -u -b0
iperf3 -c 192.168.1.1 -i 1 -t 20 -R -u -b0
iperf3 -c 192.168.1.1 -i 1 -t 20 -w 32K -P 4 -u -b0
iperf3 -c 192.168.1.1 -i 1 -b0
iperf3 -c 192.168.1.1 -i.5 -O 2 -u -b0
iperf3 -Z -c 192.168.1.1 -u -b0
iperf3 -c 192.168.1.1 -u -b0
iperf3 -c 192.168.1.1 -T s1 -u -b0
iperf3 -c 192.168.1.1 -J -u -b0
