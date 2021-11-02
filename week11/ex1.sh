#!/bin/bash
if [ "$EUID" -ne 0 ]
  then echo "Please run as using sudo"
  exit
fi

dd if=/dev/zero of=lofs.img count=50 bs=1MiB
losetup -fP lofs.img
mkfs.ext4 ./lofs.img

#loopnumber=$(losetup -a | grep "lofs.img" | grep "loop")
#loopnumber=${loopnumber%%:*}

mkdir lofsdisk -p
mount -o loop lofs.img ./lofsdisk
