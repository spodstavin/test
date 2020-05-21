#!/bin/bash
echo server $1
iperf3 -c $1 -i 1 -t 30
error0=$?
if [ $error0 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -c $1 -i 1 -t 30 failed: we have an exit code of $error0"
fi
iperf3 -c $1 -i 1 -t 20 -R
error1=$?
if [ $error1 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -c $1 -i 1 -t 20 -R failed: we have an exit code of $error1"
fi
iperf3 -c $1 -i 1 -t 20 -w 32K -P 4
error2=$?
if [ $error2 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -c $1 -i 1 -t 20 -w 32K -P 4 failed: we have an exit code of $error2"
fi
iperf3 -c $1 -u -i 1 -b0
error3=$?
if [ $error3 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -c $1 -u -i 1 -b0 failed: we have an exit code of $error3"
fi
iperf3 -c $1 -i.5 -O 2
error4=$?
if [ $error4 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -c $1 -i.5 -O 2 failed: we have an exit code of $error4"
fi
iperf3 -Z -c $1
error5=$?
if [ $error5 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -Z -c $1 failed: we have an exit code of $error5"
fi
iperf3 -c $1
error6=$?
if [ $error6 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -c $1 failed: we have an exit code of $error6"
fi
iperf3 -c $1 -J
error7=$?
if [ $error7 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -c $1 -J failed: we have an exit code of $error7"
fi
iperf3 -c $1 -i 1 -t 30 -u -b0
error8=$?
if [ $error8 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -c $1 -i 1 -t 30 -u -b0 failed: we have an exit code of $error8"
fi
iperf3 -c $1 -i 1 -t 20 -R -u -b0
error9=$?
if [ $error9 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -c $1 -i 1 -t 20 -R -u -b0 failed: we have an exit code of $error9"
fi
iperf3 -c $1 -i 1 -t 20 -w 32K -P 4 -u -b0
error10=$?
if [ $error10 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -c $1 -i 1 -t 20 -w 32K -P 4 -u -b0 failed: we have an exit code of $error10"
fi
iperf3 -c $1 -i 1 -b0
error11=$?
if [ $error11 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -c $1 -i 1 -b0 failed: we have an exit code of $error11"
fi
iperf3 -c $1 -i.5 -O 2 -u -b0
error12=$?
if [ $error12 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -c $1 -i.5 -O 2 -u -b0 failed: we have an exit code of $error12"
fi
iperf3 -Z -c $1 -u -b0
error13=$?
if [ $error13 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -Z -c $1 -u -b0 failed: we have an exit code of $error13"
fi
iperf3 -c $1 -u -b0
error14=$?
if [ $error14 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -c $1 -u -b0 failed: we have an exit code of $error14"
fi
iperf3 -c $1 -T s1 -u -b0
error15=$?
if [ $error15 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -c $1 -T s1 -u -b0 failed: we have an exit code of $error15"
fi
iperf3 -c $1 -J -u -b0
error16=$?
if [ $error16 -ne 0 ] ; then
  echo "Ethernet tests: iperf3 -c $1 -J -u -b0 failed: we have an exit code of $error16"
fi
if [ $error0 -ne 0 ] ; then
  exit 1
fi
if [ $error1 -ne 0 ] ; then
  exit 1
fi
if [ $error2 -ne 0 ] ; then
  exit 1
fi
if [ $error3 -ne 0 ] ; then
  exit 1
fi
if [ $error4 -ne 0 ] ; then
  exit 1
fi
if [ $error5 -ne 0 ] ; then
  exit 1
fi
if [ $error6 -ne 0 ] ; then
  exit 1
fi
if [ $error7 -ne 0 ] ; then
  exit 1
fi
if [ $error8 -ne 0 ] ; then
  exit 1
fi
if [ $error9 -ne 0 ] ; then
  exit 1
fi
if [ $error10 -ne 0 ] ; then
  exit 1
fi
if [ $error11 -ne 0 ] ; then
  exit 1
fi
if [ $error12 -ne 0 ] ; then
  exit 1
fi
if [ $error13 -ne 0 ] ; then
  exit 1
fi
if [ $error14 -ne 0 ] ; then
  exit 1
fi
if [ $error15 -ne 0 ] ; then
  exit 1
fi
if [ $error16 -ne 0 ] ; then
  exit 1
fi
echo "All Ethernet tests passed OK"
exit 0
