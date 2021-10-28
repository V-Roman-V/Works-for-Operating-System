#!/bin/bash
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

dd if=/dev/zero of=lofs.img count=50 bs=1MiB
#du -sh lofs.img 
losetup -fP lofs.img
#losetup -a 
mkfs.ext4 ./lofs.img 
mkdir lofsdisk -p
loopnumber=$(losetup -a | grep "lofs.img" | grep "loop")
loopnumber=${loopnumber%%:*}
#echo $loopnumber
mount -o loop $loopnumber ./lofsdisk
#df -hP ./lofsdisk
#mount | grep lofsdisk
