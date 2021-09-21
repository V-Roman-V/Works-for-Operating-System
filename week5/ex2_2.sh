while :
do
	lockfile ex2f.lock
	num=$( tail -n 1 ex2f)
	echo `expr $num + 1` >> ex2f
	rm -f ex2f.lock
done

