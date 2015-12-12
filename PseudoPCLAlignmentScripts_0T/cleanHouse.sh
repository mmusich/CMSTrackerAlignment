RUNNUM="$1"
eval `scram runtime -sh`
cp PCLplot.C Results$RUNNUM/MinBias_2015
cd Results$RUNNUM/MinBias_2015
rm milleBinary_*
root -l -b <<EOF
.L PCLplot.C
PCLplot($RUNNUM)
.q
EOF
cd ../
rm -r MinBias_2015_*
cd ../
mv Results$RUNNUM ~/public/pp0T_PCL_Alignment
echo "DONE!"