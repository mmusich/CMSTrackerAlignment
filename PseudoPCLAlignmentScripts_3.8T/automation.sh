#!/bin/sh
cd /afs/cern.ch/work/j/jcastle/CMSSW_7_4_6/src/pp3.8T_2015_Alignment/

python CheckFinished.py
if [ $? -ne 1 ]
then 
exit
fi

echo "New Job `date`" >> acronjobTestSTDOUT.txt
echo "New Job `date`" >> CurrentlyRunning.txt
python DoByRuns.py >> acronjobTestSTDOUT.txt
echo "Job Finished `date`" >> acronjobTestSTDOUT.txt
echo "Job Finished `date`" >> CurrentlyRunning.txt
