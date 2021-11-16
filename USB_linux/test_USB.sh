#!/bin/bash
mkfs -t ext4 /dev/sda
mount /dev/sda /mnt
useradd qq
chown -R qq:qq /mnt/
cd disk-stress
date
./disk-stress config
error0=$?
date
if [ $error0 -ne 0 ] ; then
  echo "USB tests: disk-stress failed: we have an exit code of $error0"
fi
cd ../ltp-filesystems
date
./runalltests.sh -i 1024 -m 128 -p -q  -l /tmp/resultlog.11402 -d /mnt
error1=$?
date
if [ $error1 -ne 0 ] ; then
  echo "USB tests: ltp-filesystems failed: we have an exit code of $error1"
fi
cd ../bonnie++-1.98
date
./bonnie++ -d /mnt -u qq
error2=$?
if [ $error2 -ne 0 ] ; then
  echo "USB tests: first bonnie++ failed: we have an exit code of $error2"
fi
date
./bonnie++ -d /mnt -s 4G -n 0 -f -b -u qq
error3=$?
date
umount /mnt/
if [ $error3 -ne 0 ] ; then
  echo "USB tests: secon bonnie++ failed: we have an exit code of $error3"
fi
cd ..
mkfs -t ext3 /dev/sda
mount /dev/sda /mnt
chown -R qq:qq /mnt/
cd disk-stress
date
./disk-stress config
error4=$?
date
if [ $error4 -ne 0 ] ; then
  echo "USB tests: disk-stress failed: we have an exit code of $error4"
fi
cd ../ltp-filesystems
date
./runalltests.sh -i 1024 -m 128 -p -q  -l /tmp/resultlog.11402 -d /mnt
error5=$?
date
if [ $error5 -ne 0 ] ; then
  echo "USB tests: ltp-filesystems failed: we have an exit code of $error5"
fi
cd ../bonnie++-1.98
date
./bonnie++ -d /mnt -u qq
error6=$?
if [ $error6 -ne 0 ] ; then
  echo "USB tests: first bonnie++ failed: we have an exit code of $error6"
fi
date
./bonnie++ -d /mnt -s 4G -n 0 -f -b -u qq
error7=$?
if [ $error7 -ne 0 ] ; then
  echo "USB tests: second bonnie++ failed: we have an exit code of $error7"
fi
date
umount /mnt/
cd ..
mkfs -t ext2 /dev/sda
mount /dev/sda /mnt
chown -R qq:qq /mnt/
cd disk-stress
date
./disk-stress config
error8=$?
if [ $error8 -ne 0 ] ; then
  echo "USB tests: disk-stress failed: we have an exit code of $error8"
fi
date
cd ../ltp-filesystems
./runalltests.sh -i 1024 -m 128 -p -q  -l /tmp/resultlog.11402 -d /mnt
error9=$?
if [ $error9 -ne 0 ] ; then
  echo "USB tests: ltp-filesystems failed: we have an exit code of $error9"
fi
cd ../bonnie++-1.98
date
./bonnie++ -d /mnt -u qq
error10=$?
if [ $error10 -ne 0 ] ; then
  echo "USB tests: first bonnie++ failed: we have an exit code of $error10"
fi
date
./bonnie++ -d /mnt -s 4G -n 0 -f -b -u qq
error11=$?
if [ $error11 -ne 0 ] ; then
  echo "USB tests: bonnie++ failed: we have an exit code of $error11"
fi
date
umount /mnt/
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
echo "All USB tests passed OK"
exit 0
