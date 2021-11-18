#!/bin/bash
date
memtester 500 100
error0=$?
date
if [ $error0 -ne 0 ] ; then
  echo "Memory tests: memtester failed: we have an exit code of $error0"
fi
if [ $error0 -ne 0 ] ; then
  exit 1
fi
echo "All memory tests passed OK"
exit 0

