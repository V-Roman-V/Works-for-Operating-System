#!/bin/bash
if [ "$EUID" -ne 0 ]
  then echo "Please run using sudo"
  exit
fi

LOF=./lofsdisk

copy_dependencies (){
	mkdir $LOF/bin -p
	for d in $@; do
		#echo "~~${d}"
		cp -f "/bin/${d}" $LOF/bin
		list="$(ldd /bin/${d} | egrep -o '/lib.*\.[0-9]')"
		for i in $list; do mkdir -p $(dirname "${LOF}${i}") && cp -f "$i" "${LOF}${i}"; done
	done
}


#### main ####

./ex1_clear.sh
./ex1.sh

echo "Roman"   > $LOF/file1
echo "Voronov" > $LOF/file2
gcc ex2.c -o ex2.out
gcc ex2.c -o $LOF/ex2.out

copy_dependencies {bash,cat,echo,ls}

echo "from LOFS:" > ex2.txt
chroot $LOF ./ex2.out >> ex2.txt
echo "" >> ex2.txt
echo "from base root:" >> ex2.txt
./ex2.out >> ex2.txt

chmod 777 ex2.txt
rm $LOF/ex2.out
rm ex2.out
