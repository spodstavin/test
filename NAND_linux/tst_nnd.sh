#!/bin/bash
umount /mnt/
mkfs -t ext4 /dev/mmcblk0p1 
mount /dev/mmcblk0p1  /mnt
useradd qq
chown -R qq:qq /mnt/
date
bonnie++ -d /mnt -u qq
error0=$?
if [ $error0 -ne 0 ] ; then
  echo "NAND tests: first ext4 bonnie++ failed: we have an exit code of $error0"
fi
date
bonnie++ -d /mnt -s 4G -n 0 -f -b -u qq
error1=$?
date
umount /mnt/
if [ $error1 -ne 0 ] ; then
  echo "NAND tests: secon ext4 bonnie++ failed: we have an exit code of $error1"
fi
mkfs -t ext3 /dev/mmcblk0p1 
mount /dev/mmcblk0p1  /mnt
chown -R qq:qq /mnt/
bonnie++ -d /mnt -u qq
error2=$?
if [ $error2 -ne 0 ] ; then
  echo "NAND tests: first ext3 bonnie++ failed: we have an exit code of $error2"
fi
date
bonnie++ -d /mnt -s 4G -n 0 -f -b -u qq
error3=$?
if [ $error3 -ne 0 ] ; then
  echo "NAND tests: second ext3 bonnie++ failed: we have an exit code of $error3"
fi
date
umount /mnt/
mkfs -t ext2 /dev/mmcblk0p1 
mount /dev/mmcblk0p1  /mnt
chown -R qq:qq /mnt/
date
bonnie++ -d /mnt -u qq
error4=$?
if [ $error4 -ne 0 ] ; then
  echo "NAND tests: first ext2 bonnie++ failed: we have an exit code of $error4"
fi
date
bonnie++ -d /mnt -s 4G -n 0 -f -b -u qq
error5=$?
if [ $error5 -ne 0 ] ; then
  echo "NAND tests: second bonnie++ ext2 failed: we have an exit code of $error5"
fi
date
umount /mnt/
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
echo "All NAND tests passed OK"
exit 0
