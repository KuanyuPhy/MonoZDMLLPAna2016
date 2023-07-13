#!/bin/bash
set -eu -o pipefail 
#----------------------------------------------------------------
# Compile .C file
#----------------------------------------------------------------
g++ -o Scan_DY_bg.o $(root-config --cflags) Scan_DY_bg.C $(root-config --glibs)
g++ -o Scan_Top_bg.o $(root-config --cflags) Scan_Top_bg.C $(root-config --glibs)
g++ -o Scan_Diboson_bg.o $(root-config --cflags) Scan_Diboson_bg.C $(root-config --glibs)
g++ -o Scan_Triboson_bg.o $(root-config --cflags) Scan_Triboson_bg.C $(root-config --glibs)

#-----------------------------------------------------
#  Run background
#
#  Pre : Scan dilepPT cut, prepare to Calculate punzi
#-----------------------------------------------------
DYoutputfile="./output/DY_output"
Topoutputfile="./output/Top_output"
Dibosonoutputfile="./output/Di_output"
Tribosonoutputfile="./output/Tri_output"


Pre_DY_output=./ee_DY_punzi.root
Pre_Top_output=./ee_Top_punzi.root
Pre_Diboson_output=./ee_Diboson_punzi.root
Pre_Triboson_output=./ee_Triboson_punzi.root

#----------------------
# Delete old files
#----------------------
test -e "./ee_DY_punzi.root" && { echo "delete ee_DY_punzi.root"; rm ./ee_DY_punzi.root ;}
test -e "./ee_Top_punzi.root" && { echo "delete ee_Top_punzi.root"; rm ./ee_Top_punzi.root ;}
test -e "./ee_Diboson_punzi.root" && { echo "delete ee_Diboson_punzi.root"; rm ./ee_Diboson_punzi.root ;}
test -e "./ee_Triboson_punzi.root" && { echo "delete ee_Triboson_punzi.root"; rm ./ee_Triboson_punzi.root ;}
if [ ! -e "$Pre_DY_output" ] &&
 [ ! -e "$Pre_Top_output" ] &&
 [ ! -e "$Pre_Diboson_output" ] &&
 [ ! -e "$Pre_Triboson_output" ]; then
    echo "old punzi file not found."
else
    echo "file found, check existing old root."
    exit 
fi
#--------------------------------
# Calculate punzi significant
#--------------------------------
for ((j=1;j<=100;j++))
do  
    ./Scan_DY_bg.o "$j" "${DYoutputfile}_$j.root" &
done
wait
echo "Finish Scan Drell-Yan process"
for ((j=1;j<=100;j++))
do  
    ./Scan_Top_bg.o "$j" "${Topoutputfile}_$j.root" &
done
wait
echo "Finish Scan Top process"
for ((j=1;j<=100;j++))
do  
    ./Scan_Diboson_bg.o "$j" "${Dibosonoutputfile}_$j.root" &
done
wait
echo "Finish Scan Diboson process"
for ((j=1;j<=100;j++))
do  
    ./Scan_Triboson_bg.o "$j" "${Tribosonoutputfile}_$j.root" &
done
wait
echo "Finish Scan Triboson process"

wait

hadd ee_DY_punzi.root ./output/DY_output*.root 
hadd ee_Top_punzi.root ./output/Top_output*.root
hadd ee_Diboson_punzi.root ./output/Di_output*.root
hadd ee_Triboson_punzi.root ./output/Tri_output_*.root
#-------------------------------
# Combine to 2016 MC background
#-------------------------------
test -e "./ee_bgall_punzi.root" && { echo "delete ee_bgall_punzi.root"; rm ./ee_bgall_punzi.root ;}

hadd ee_bgall_punzi.root ee_DY_punzi.root ee_Diboson_punzi.root ee_Top_punzi.root ee_Triboson_punzi.root

wait
echo "Start scan signal process"

#-------------------------------
# Clear process files
#-------------------------------
if [ "ls -A ./output/*" = "" ]; then
    echo "./output/* is indeed empty"
else
    echo "./output/* is not empty"
    echo "Clear output directory" && rm ./output/*
fi
test -e "./Scan_DY_bg.o" && { echo "Delete Scan_DY_bg.o"; rm ./Scan_DY_bg.o ;}
test -e "./Scan_Top_bg.o" && { echo "Delete Scan_Top_bg.o"; rm ./Scan_Top_bg.o ;}
test -e "./Scan_Diboson_bg.o" && { echo "Delete Scan_Diboson_bg.o"; rm ./Scan_Diboson_bg.o ;}
test -e "./Scan_Triboson_bg.o" && { echo "Delete Scan_Triboson_bg.o"; rm ./Scan_Triboson_bg.o ;}

root -b -q Scan_sig.C
#
##rm ./output/DY_output*.root
##rm ./output/Top_output*.root
##rm ./output/Di_output*.root
##rm ./output/Tri_output*.root
#