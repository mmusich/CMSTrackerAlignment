RUNNUM="$1"
cd Results$RUNNUM/MinBias_2015
rm milleBinary_*
cd ../
rm -r MinBias_2015_*
cd ../
mv Results$RUNNUM ~/public/pp3.8T_PCL_Alignment
echo "DONE!"