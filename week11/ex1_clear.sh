#!/bin/bash
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

umount lofsdisk
rmdir lofsdisk

loopnumber=$(losetup -a | grep "lofs.img" | grep "loop")
loopnumber=${loopnumber%%:*}
losetup -d $loopnumber

rm lofs.img

