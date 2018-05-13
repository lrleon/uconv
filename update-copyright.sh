
#l=`ls include/units/*.H`
l=`ls include/*.H include/units/*.H tests/*.cc Tests/*.cc Tests/*.H lib/*.cc`

for f in $l
do
    echo $f
    mv $f $f.tmp
    ./put-copyright $f.tmp > $f
done
	 
