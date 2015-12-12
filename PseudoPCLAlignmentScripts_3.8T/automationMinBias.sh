#!/bin/sh
RUN="$1"
COUNTER="$2"
cd /afs/cern.ch/work/j/jcastle/CMSSW_7_4_6/src/
eval `scram runtime -sh`
cd /afs/cern.ch/work/j/jcastle/CMSSW_7_4_6/src/pp3.8T_2015_Alignment/Results$RUN/

python DoMINBIAS.py $RUN $COUNTER

