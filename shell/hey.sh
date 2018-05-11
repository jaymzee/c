for i in $*
do
    echo $i
done

b=0
while [ $b != 1 ]
do
    echo inside while loop
    b=1
done

echo enter some text:
read s
echo you typed $s

c=5
if [ $c -eq 5 ]
then
    echo c is 5
else
    echo "c=$c"
fi

