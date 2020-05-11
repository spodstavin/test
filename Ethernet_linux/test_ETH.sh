#!/bin/bash

cd iperf-3.7
./configure
make
make install
iperf3 -c 172.19.4.2 -i 1 -t 30
iperf3 -c 172.19.4.2 -i 1 -t 20 -r
iperf3 -c 172.19.4.2 -i 1 -t 20 -w 32M -P 4
iperf3 -c 172.19.4.2 -u -i 1 -b 200M
iperf3 -c 172.19.4.2 -i.5 -0 2
iperf3 -Z -c 172.19.4.2
iperf3 -c 172.19.4.2
iperf3 -c 172.19.4.2 -T s1 & iperf3 -c 172.19.4.2 -T s2
iperf3 -c 172.19.4.2 -J
iperf3 -A 4,4 -c 172.19.4.2 
iperf3 -c 172.19.4.2 -A2,2 -T "1"  
iperf3 -c 172.19.4.2 -p 5400 -A3,3 -T "2"
iperf3 -c 172.19.4.2 -i 1 -t 30 -u
iperf3 -c 172.19.4.2 -i 1 -t 20 -r -u
iperf3 -c 172.19.4.2 -i 1 -t 20 -w 32M -P 4 -u
iperf3 -c 172.19.4.2 -u -i 1 -b 200M -u
iperf3 -c 172.19.4.2 -i.5 -0 2 -u
iperf3 -Z -c 172.19.4.2 -u
iperf3 -c 172.19.4.2 -u
iperf3 -c 172.19.4.2 -T s1 -u & iperf3 -c 172.19.4.2 -T s2 -u
iperf3 -c 172.19.4.2 -J -u
iperf3 -A 4,4 -c 172.19.4.2 -u
iperf3 -c 172.19.4.2 -A2,2 -T "1" -u  
iperf3 -c 172.19.4.2 -p 5400 -A3,3 -T "2" -u
