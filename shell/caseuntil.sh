#!/bin/bash

cmd_num=0

until [ ${cmd_num} -eq "4" ]; do
echo "Enter the number to test you want
	1. ls
	2. ls -a
	3. ls -al
	4. exit"
echo "Enter: "
read cmd_num

case ${cmd_num} in 
1) ls ;;
2) ls -a;;
3) ls -al;;
4) exit;;
*) echo "Please enter the number between 1 to 4"
esac
done


