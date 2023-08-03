#!/bin/sh
#Choose bset schedd
#myschedd bump

#Show where schedd are we
myschedd show

#create condor output file
mkdir -p ./../output error log

function examplestring(){
    echo 'Example: bash submit.sh typelist'
    echo 'If you want to run , you need to "bash submit.sh typelist"'
}
function exampletypelist(){
    echo 'Example: typelist = DoubleEG, DoubleMuon, MuonEG, SingleElectron, SingleMuon'
}

if [[ -z $1 ]]; then
    exampletypelist
    examplestring
    exit
fi

# background type 
background_type=$1

# If type is DoubleEG
if [ $1 = "DoubleEG" ]; then
    DoubleEG_list=("DoubleEG_Run2016B-07Aug17_ver2-v2")
    #Submit condor job
    for DoubleEG_list in ${DoubleEG_list[*]}; do
    #echo $DoubleEG_list
    sed -i "/maintype = /c maintype = $1" DoubleEG.sub
    sed -i "/subtype_list = /c subtype_list = ${DoubleEG_list}" DoubleEG.sub
    condor_submit DoubleEG.sub
    done
fi

# If type is DoubleMuon
if [ $1 = "DoubleMuon" ]; then
    DoubleMuon_list=("DoubleMuon_Run2016B-07Aug17_ver2-v1")
    #Submit condor job
    for DoubleMuon_list in ${DoubleMuon_list[*]}; do
    echo $DoubleMuon_list
    sed -i "/maintype = /c maintype = $1" DoubleMuon.sub
    sed -i "/subtype_list = /c subtype_list = ${DoubleMuon_list}" DoubleMuon.sub
    condor_submit DoubleMuon.sub 
    done
fi
# If type is MuonEG
if [ $1 = "MuonEG" ]; then
    MuonEG_list=("MuonEG_Run2016B-07Aug17_ver2-v1")
    #Submit condor job
    for MuonEG_list in ${MuonEG_list[*]}; do
    echo $MuonEG_list
    sed -i "/maintype = /c maintype = $1" MuonEG.sub
    sed -i "/subtype_list = /c subtype_list = ${MuonEG_list}" MuonEG.sub
    condor_submit MuonEG.sub
    done
fi
# If type is SingleElectron
if [ $1 = "SingleElectron" ]; then
    SingleElectron_list=("SingleElectron_Run2016B-07Aug17_ver2-v2")
    #Submit condor job
    for SingleElectron_list in ${SingleElectron_list[*]}; do
    echo $SingleElectron_list
    sed -i "/maintype = /c maintype = $1" SingleElectron.sub
    sed -i "/subtype_list = /c subtype_list = ${SingleElectron_list}" SingleElectron.sub
    condor_submit SingleElectron.sub
    done
fi
# If type is SingleMuon
if [ $1 = "SingleMuon" ]; then
    SingleMuon_list=("SingleMuon_Run2016B-07Aug17_ver2-v1")
    #Submit condor job
    for SingleMuon_list in ${SingleMuon_list[*]}; do
    echo $SingleMuon_list
    sed -i "/maintype = /c maintype = $1" SingleMuon.sub
    sed -i "/subtype_list = /c subtype_list = ${SingleMuon_list}" SingleMuon.sub
    condor_submit SingleMuon.sub
    done
fi
echo 'End of script'


