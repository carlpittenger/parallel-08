#!/bin/bash
sci_notation_regex='^[0-9]+([.][0-9]+)?(e[0-9]+|e-[0-9]+)?$'
function test_time(){
if [[ ! $1 =~ $sci_notation_regex ]];then
echo ERROR: time is not on stderr or not formatted properly
echo
rm .time
exit 1
fi
rm .time
}
SUCCESS_FILE=.passed_mergesort
if [ -e $SUCCESS_FILE ];then
rm $SUCCESS_FILE
fi
for n in 7 10 1000 1111 1017 10000 10017;do
for nbt in 1 2 3 4;do
TEST=$(./mergesort-loop $n $nbt 2>.time)
if [ "$TEST" = "checked" ];then
test_time $(cat .time)
else
echo FAIL: "./mergesort-loop $n $nbt is not sorted correctly"
exit 1
fi
done
done
touch $SUCCESS_FILE
echo "================================"
echo
echo "Success! All mergesort-loop tests passed! :)"
