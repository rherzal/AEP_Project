list=$(ls)

echo $list

for l in $list
do
	echo "file://${l} \ "
done
