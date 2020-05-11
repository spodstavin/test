#!/bin/sh

#    Copyright (c) International Business Machines  Corp., 2003
#
#    This program is free software;  you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY;  without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
#    the GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program;  if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#
#   FILE        : ltpstress.sh
#   DESCRIPTION : A script that will stress your system using the LTP testsuite.
#   REQUIREMENTS: 
#                 1) The 'rsh' daemon must be running and NFS (versions 2 &3) must be
#                    configured into the kernel and installed.
#		  2) The 'sar' application must be installed to use the "-S" option
#   HISTORY     :
#       02/11/2003 Robbie Williamson (robbiew@austin.ibm.com)
#               written
####################################################

export LTPROOT=${PWD}
echo $LTPROOT | grep testscripts > /dev/null 2>&1
if [ $? -eq 0 ]; then
 cd ..
 export LTPROOT=${PWD}
fi
export TMPBASE="/tmp"
export TMP="${TMPBASE}/ltpstress-$$"
export PATH=$LTPROOT/testcases/bin:$PATH
memsize=0
PROC_NUM=0
leftover_memsize=0
duration=86400
datafile="/tmp/ltpstress.data"
interval=10
Sar=0
Top=0

usage()
{

	cat <<-END >&2
	usage: ${0##*/} [ -d datafile ] [ -i # (in seconds) ] [ -l logfile ] [ -m # (in Mb) ] [ -t duration ] [ [-S]|[-T] ]

    -d datafile     Data file for 'sar' or 'top' to log to. Default is "/tmp/ltpstress.data".
    -i # (in sec)   Interval that 'sar' or 'top' should take snapshots. Default is 10 seconds.
    -l logfile      Log results of test in a logfile.
    -m # (in Mb)    Specify the _minimum_ memory load of # megabytes in background. Default is 64Mb.
    -S              Use 'sar' to measure data. 
    -T              Use LTP's modified 'top' tool to measure data.
    -t duration     Execute the testsuite for given duration in hours. Default is 24.

	example: ${0##*/} -d /tmp/sardata -l /tmp/ltplog.$$ -m 128 -t 24 -S
	END
exit
}

check_memsize()
{
  while [ $memsize -gt 1048576 ]   #if greater than 1GB
  do
    PROC_NUM=$(( PROC_NUM + 1 ))
    memsize=$(( $memsize - 1048576 ))
  done  
  leftover_memsize=$memsize
}


mkdir -p ${TMP}

cd ${TMP}
if [ $? -ne 0 ]; then
  echo "could not cd ${TMP} ... exiting"
  exit
fi

while getopts d:hi:l:STt:m:n\? arg
do  case $arg in

	d)	datafile="$OPTARG";;

        h)      echo "Help info:"
		usage;;

	i)	interval=$OPTARG;;

        l)      logfile="-l $OPTARG";;

        m)	memsize=$(($OPTARG * 1024))
		check_memsize;;	

        S)      if [ $Top -eq 0 ]; then
                  Sar=1
                else
                  echo "Cannot specify -S and -T...exiting"
                  exit
                fi;;

	T)	if [ $Sar -eq 0 ]; then
                  $LTPROOT/testcases/bin/top -h 2>&1 | grep "\-f filename" >/dev/null
		  if [ $? -eq 0 ]; then
                    Top=1
                  else
		    echo "ERROR: Please build and install the version of top in the /tools dir"
		    exit
 		  fi
                else
                  echo "Cannot specify -S and -T...exiting"
                  exit
                fi;;

        t)      hours=$OPTARG
		duration=$(($hours * 60 * 60));;

        \?)     echo "Help info:"
		usage;;
        esac
done

# Networking setup
echo `hostname` >> /root/.rhosts
chmod 644 /root/.rhosts

netstat -an | grep 514
if [ $? -eq 1 ];then
  echo "Error: 'rsh' deamon not active on this machine."
  exit 1
fi

ps -ef | grep portmap | grep -v grep
if [ $? -eq 1 ];then
  /sbin/portmap &
fi
sleep 1
ps -ef | grep portmap | grep -v grep
if [ $? -eq 1 ];then
  echo "Error: Could not start portmap daemon."
  exit 1
fi

rpcinfo -p | grep status 
if [ $? -eq 1 ];then
  /sbin/rpc.statd 
fi
sleep 1
rpcinfo -p | grep status 
if [ $? -eq 1 ];then
  echo "Error: Could not start statd daemon."
  exit 1
fi

rpcinfo -p | grep nfs 
if [ $? -eq 1 ];then
  /usr/sbin/rpc.nfsd 
fi
sleep 1
rpcinfo -p | grep nfs 
if [ $? -eq 1 ];then
  echo "Error: Could not start nfs server daemon."
  exit 1
fi

rpcinfo -p | grep mount 
if [ $? -eq 1 ];then
  /usr/sbin/rpc.mountd 
fi
sleep 1
rpcinfo -p | grep mount 
if [ $? -eq 1 ];then
  echo "Error: Could not start mountd daemon."
  exit 1
fi
# End of network setup



if [ $memsize -eq 0 ]; then
  memsize=$((64 * 1024 * 1024))
fi

if [ $PROC_NUM -gt 0 ];then
  genload --vm $PROC_NUM --vm-bytes 1073741824 2>&1 1>/dev/null &
fi
if [ $leftover_memsize -gt 0 ];then
  genload --vm 1 --vm-bytes $(($leftover_memsize * 1024)) 2>&1 1>/dev/null & 
fi

netpipe.sh >/dev/null 2>/dev/null &

${LTPROOT}/tools/rand_lines -g ${LTPROOT}/runtest/stress.part1 > ${TMP}/stress.part1
${LTPROOT}/tools/rand_lines -g ${LTPROOT}/runtest/stress.part2 > ${TMP}/stress.part2
${LTPROOT}/tools/rand_lines -g ${LTPROOT}/runtest/stress.part3 > ${TMP}/stress.part3

sleep 2

if [ $Sar -eq 1 ]; then
  sar -o $datafile $interval 0 &
fi

if [ $Top -eq 1 ]; then
  screen -d -m $LTPROOT/testcases/bin/top -o $datafile -d $interval &
  SCREEN_PID=$(ps -e | grep screen | awk {'print $1'})
fi

sleep 2

output1=${TMPBASE}/ltpstress.$$.output1
output2=${TMPBASE}/ltpstress.$$.output2
output3=${TMPBASE}/ltpstress.$$.output3

${LTPROOT}/pan/pan -e -p -q -S -t ${hours}h -a stress1 -n stress1 $logfile -f ${TMP}/stress.part1 -o $output1 & 
${LTPROOT}/pan/pan -e -p -q -S -t ${hours}h -a stress2 -n stress2 $logfile -f ${TMP}/stress.part2 -o $output2 &
${LTPROOT}/pan/pan -e -p -q -S -t ${hours}h -a stress3 -n stress3 $logfile -f ${TMP}/stress.part3 -o $output3 &

echo "Running LTP Stress for $hours hour(s)"
echo ""
echo "Test output recorded in:"
echo "        $output1"
echo "        $output2"
echo "        $output3"

# Sleep a little longer than duration to let pan "try" to gracefully end itself.
sleep $(($duration + 10))  

if [ $Sar -eq 1 ]; then
  killall -9 sadc >/dev/null 2>&1
fi
if [ $Top -eq 1 ]; then
  kill $SCREEN_PID >/dev/null 2>&1
fi
killall -9 pan >/dev/null 2>&1
killall -9 genload >/dev/null 2>&1
killall -9 netpipe.sh >/dev/null 2>&1
killall -9 NPtcp >/dev/null 2>&1

rm -rf ${TMP}
echo "Testing done"
grep FAIL $logfile >/dev/null 2>&1
if [ $? -eq 1 ]; then
  echo "All Tests PASSED!"
else
  echo "Testing yielded failures. See logfile: $logfile"
fi

