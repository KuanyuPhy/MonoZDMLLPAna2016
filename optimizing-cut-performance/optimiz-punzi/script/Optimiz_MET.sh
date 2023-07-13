#!/bin/bash
set -eu -o pipefail 
#----------------------------------------------------------------
# Compile .C file
#----------------------------------------------------------------
FileMainLocation=/home/kuanyu/Documents/CMS/Background_Estimate/cut_opt/punzi/MET


g++ -o $FileMainLocation/ee_DY_punzi.o $(root-config --cflags) $FileMainLocation/ana_DY_punzi.C $(root-config --glibs)
g++ -o $FileMainLocation/ee_Top_punzi.o $(root-config --cflags) $FileMainLocation/ana_Top_punzi.C $(root-config --glibs)
g++ -o $FileMainLocation/ee_Diboson_punzi.o $(root-config --cflags) $FileMainLocation/ana_Diboson_punzi.C $(root-config --glibs)
g++ -o $FileMainLocation/ee_Triboson_punzi.o $(root-config --cflags) $FileMainLocation/ana_Triboson_punzi.C $(root-config --glibs)

#---------------------
#  Run background
#---------------------

DYoutputfile="$FileMainLocation/output/DY_output"
Topoutputfile="$FileMainLocation/output/Top_output"
Dibosonoutputfile="$FileMainLocation/output/Di_output"
Tribosonoutputfile="$FileMainLocation/output/Tri_output"

Pre_DY_output=ee_DY_punzi_MET.root
Pre_Top_output=ee_Top_punzi_MET.root
Pre_Diboson_output=ee_Diboson_punzi_MET.root
Pre_Triboson_output=ee_Triboson_punzi_MET.root

#----------------------
# Delete old files
#----------------------
test -e "$FileMainLocation/$Pre_DY_output" && 
    { echo "delete ee_DY_punzi_MET.root"; rm "$FileMainLocation/$Pre_DY_output" ;}

test -e "$FileMainLocation/$Pre_Top_output" && 
    { echo "delete ee_Top_punzi_MET.root"; rm "$FileMainLocation/$Pre_Top_output" ;}

test -e "$FileMainLocation/$Pre_Diboson_output" &&
    { echo "delete ee_Diboson_punzi_MET.root"; rm "$FileMainLocation/$Pre_Diboson_output" ;}

test -e "$FileMainLocation/$Pre_Triboson_output" &&
    { echo "delete ee_Triboson_punzi_MET.root"; rm "$FileMainLocation/$Pre_Triboson_output" ;}

if [ ! -e "$FileMainLocation/$Pre_DY_output" ] &&
 [ ! -e "$FileMainLocation/$Pre_Top_output" ] &&
 [ ! -e "$FileMainLocation/$Pre_Diboson_output" ] &&
 [ ! -e "$FileMainLocation/$Pre_Triboson_output" ]; then
    echo "old punzi file not found."
    echo "Start Scanning for MET cut"
else
    echo "file found, check existing old root."
    exit 1
fi

#--------------------------------
# Calculate punzi significant
#--------------------------------
StartStep=1
MaxStep=150

#--------------------------------------------------------------------
# Use parallel to contral njob to prevent computer memory reach max 
#--------------------------------------------------------------------

parallel -j 50 --link ::: $FileMainLocation/ee_DY_punzi.o ::: $(seq "$StartStep" "$MaxStep") ::: $(seq "$StartStep" "$MaxStep" | xargs printf "${DYoutputfile}_%s.root\n")
echo "Finish Scan Drell-Yan process"
parallel -j 50 --link ::: $FileMainLocation/ee_Top_punzi.o ::: $(seq "$StartStep" "$MaxStep") ::: $(seq "$StartStep" "$MaxStep" | xargs printf "${Topoutputfile}_%s.root\n")
echo "Finish Scan Top process"
parallel -j 50 --link ::: $FileMainLocation/ee_Diboson_punzi.o ::: $(seq "$StartStep" "$MaxStep") ::: $(seq "$StartStep" "$MaxStep" | xargs printf "${Dibosonoutputfile}_%s.root\n")
echo "Finish Scan Diboson process"
parallel -j 50 --link ::: $FileMainLocation/ee_Triboson_punzi.o ::: $(seq "$StartStep" "$MaxStep") ::: $(seq "$StartStep" "$MaxStep" | xargs printf "${Tribosonoutputfile}_%s.root\n")
echo "Finish Scan Triboson process"

hadd $FileMainLocation/ee_DY_punzi_MET.root $DYoutputfile*.root 
hadd $FileMainLocation/ee_Top_punzi_MET.root $Topoutputfile*.root
hadd $FileMainLocation/ee_Diboson_punzi_MET.root $Dibosonoutputfile*.root
hadd $FileMainLocation/ee_Triboson_punzi_MET.root $Tribosonoutputfile*.root

#-------------------------------
# Combine to 2016 MC background
#-------------------------------
test -e "$FileMainLocation/ee_bgall_punzi_MET.root" && { echo "delete ee_bgall_punzi_MET.root"; rm $FileMainLocation/ee_bgall_punzi_MET.root ;}

hadd $FileMainLocation/ee_bgall_punzi_MET.root $FileMainLocation/ee_DY_punzi_MET.root $FileMainLocation/ee_Diboson_punzi_MET.root $FileMainLocation/ee_Top_punzi_MET.root $FileMainLocation/ee_Triboson_punzi_MET.root

wait
echo "Start Scan signal process"

#---------------------------------------
# Scan Signal process && Calculate punzi
#---------------------------------------



#-------------------------------
# Clear process files
#-------------------------------
if [ "ls -A $FileMainLocation/output/*" = "" ]; then
    echo "$FileMainLocation/output/* is indeed empty"
else
    echo "$FileMainLocation/output/* is not empty"
    echo "Clear output directory" && rm $FileMainLocation/output/*
fi
test -e "$FileMainLocation/ana_DY_punzi.o" && { echo "Delete ana_DY_punzi.o"; rm $FileMainLocation/ana_DY_punzi.o ;}
test -e "$FileMainLocation/ana_Top_punzi.o" && { echo "Delete ana_Top_punzi.o"; rm $FileMainLocation/ana_Top_punzi.o ;}
test -e "$FileMainLocation/ana_Diboson_punzi.o" && { echo "Delete ana_Diboson_punzi.o"; rm $FileMainLocation/ana_Diboson_punzi.o ;}
test -e "$FileMainLocation/ana_Triboson_punzi.o" && { echo "Delete ana_Triboson_punzi.o"; rm $FileMainLocation/ana_Triboson_punzi.o ;}

root -l $FileMainLocation/ana_sig.C