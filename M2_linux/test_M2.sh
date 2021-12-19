#!/bin/bash
mount /dev/sda /mnt
useradd qq
chown -R qq:qq /mnt/
bonnie++  -d /mnt -u qq 
error2=$?
if [ $error2 -ne 0 ] ; then
  echo "M2 tests: bonnie++ failed: we have an exit code of $error2"
fi
if [ $error2 -ne 0 ] ; then
  exit 1
fi
echo "All M2 tests passed OK"
exit 0
