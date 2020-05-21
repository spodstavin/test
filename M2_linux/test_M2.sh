#!/bin/bash
mount /dev/sda /mnt
useradd qq
chown -R qq:qq /mnt/
cd disk-stress
./disk-stress config
error0=$?
if [ $error0 -ne 0 ] ; then
  echo "M2 tests: disk-stress failed: we have an exit code of $error0"
fi
cd ../ltp-filesystems
./runalltests.sh -i 1024 -m 128 -p -q  -l /tmp/resultlog.11402 -d /mnt
error1=$?
if [ $error1 -ne 0 ] ; then
  echo "M2 tests: ltp-filesystems failed: we have an exit code of $error1"
fi
cd ../bonnie++-1.98
./bonnie++  -d /mnt -u qq 
error2=$?
if [ $error2 -ne 0 ] ; then
  echo "M2 tests: bonnie++ failed: we have an exit code of $error2"
fi
cd ..
if [ $error0 -ne 0 ] ; then
  exit 1
fi
if [ $error1 -ne 0 ] ; then
  exit 1
fi
if [ $error2 -ne 0 ] ; then
  exit 1
fi
echo "All M2 tests passed OK"
exit 0
