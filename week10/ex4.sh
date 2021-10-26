mkdir tmp -p
echo "" > tmp/file1
echo "" > tmp/file2
ln tmp/file1 tmp/link1 -f
gcc ex4.c -o ex4.o
chmod 777 ex4.o
./ex4.o > ex4.txt
cat ex4.txt
rm ex4.o
