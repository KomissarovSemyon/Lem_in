ARG=$(ls map | grep err)
for map in $ARG
do
	echo $map
	cat map/$map | ./lem_in1 
done