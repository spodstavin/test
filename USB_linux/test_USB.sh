#!/bin/bash
mkfs -t ext4 /dev/sda
mount /dev/sda /mnt
useradd qq
chown -R qq:qq /mnt/
date
bonnie++ -d /mnt -u qq
error2=$?
if [ $error2 -ne 0 ] ; then
  echo "USB tests: first bonnie++ failed: we have an exit code of $error2"
fi
date
bonnie++ -d /mnt -s 4G -n 0 -f -b -u qq
error3=$?
date
umount /mnt/
if [ $error3 -ne 0 ] ; then
  echo "USB tests: secon bonnie++ failed: we have an exit code of $error3"
fi
mkfs -t ext3 /dev/sda
mount /dev/sda /mnt
chown -R qq:qq /mnt/
date
bonnie++ -d /mnt -u qq
error6=$?
if [ $error6 -ne 0 ] ; then
  echo "USB tests: first bonnie++ failed: we have an exit code of $error6"
fi
date
bonnie++ -d /mnt -s 4G -n 0 -f -b -u qq
error7=$?
if [ $error7 -ne 0 ] ; then
  echo "USB tests: second bonnie++ failed: we have an exit code of $error7"
fi
date
umount /mnt/
mkfs -t ext2 /dev/sda
mount /dev/sda /mnt
chown -R qq:qq /mnt/
date
bonnie++ -d /mnt -u qq
error10=$?
if [ $error10 -ne 0 ] ; then
  echo "USB tests: first bonnie++ failed: we have an exit code of $error10"
fi
date
bonnie++ -d /mnt -s 4G -n 0 -f -b -u qq
error11=$?
if [ $error11 -ne 0 ] ; then
  echo "USB tests: bonnie++ failed: we have an exit code of $error11"
fi
date
umount /mnt/
if [ $error2 -ne 0 ] ; then
  exit 1
fi
if [ $error3 -ne 0 ] ; then
  exit 1
fi
if [ $error6 -ne 0 ] ; then
  exit 1
fi
if [ $error7 -ne 0 ] ; then
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
