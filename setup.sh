#!/bin/bash

USER=level
#USER=bonus

# GDB PEDA
cat password.txt
scp -P 4242 -r ~/peda/ $USER$1@target:/tmp/.

cat password.txt
ssh $USER$1@target -p 4242 << EOF
  chmod 777 .
  mv /tmp/peda .
  echo "source ~/peda/peda.py" >> ~/.gdbinit
EOF
