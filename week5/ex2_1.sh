while :
do
	num=$( tail -n 1 ex2f)
	echo `expr $num + 1` >> ex2f
done
# Race example:
#  th0      th1
#  read 0   read 0
#  write 1  write 1
# 
# Race output example:
# 0
# 1 
# 2
# 2
# 3
# 3
# 4
# 4 ...
