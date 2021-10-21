mkdir week01 -p
echo "Roman Voronov" > week01/file.txt
mkdir week10 -p
ln week01/file.txt week10/_ex2.txt -f
inodenumber=$(ls -i week01/file.txt)
inodenumber=${inodenumber%% *}
find week10 -inum $inodenumber > ex2.txt
find week10 -inum $inodenumber -exec rm {} \; >> ex2.txt
