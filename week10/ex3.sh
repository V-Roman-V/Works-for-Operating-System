echo "Roman Voronov" > _ex3.txt
chmod ugo-x  _ex3.txt -v > ex3.txt
chmod uo+rwx _ex3.txt -v >> ex3.txt
chmod g=u _ex3.txt -v >> ex3.txt
echo "660 gives read and write permissions to owner and group, removes all permissions to others" >> ex3.txt
echo "775 gives all permissions to owner and group, read and execute permissions to others" >> ex3.txt
echo "777 gives all permissions to everyone" >> ex3.txt
