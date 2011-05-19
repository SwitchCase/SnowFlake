for((i=0;i<32;i++))
do
time ./a.out <in"$i" >out"$i"
echo "DONE $i"
done

