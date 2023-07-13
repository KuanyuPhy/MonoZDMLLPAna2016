#!/bin/bash
# shellcheck disable=SC2046

set -eu -o pipefail

FileMainLocation=/home/kuanyu/Documents/CMS/Background_Estimate/cut_opt/punzi/alpha

g++ -o $FileMainLocation/ee_DY_punzi.o $(root-config --cflags) $FileMainLocation/ee_HT_alpha.C $(root-config --glibs)
g++ -o $FileMainLocation/ee_Top_punzi.o $(root-config --cflags) $FileMainLocation/ee_Top_alpha.C $(root-config --glibs)
g++ -o $FileMainLocation/ee_Diboson_punzi.o $(root-config --cflags) $FileMainLocation/ee_Diboson_alpha.C $(root-config --glibs)
g++ -o $FileMainLocation/ee_Triboson_punzi.o $(root-config --cflags) $FileMainLocation/ee_Triboson_alpha.C $(root-config --glibs)

#---------------------
#  Run background
#---------------------
DYoutputfile="$FileMainLocation/output/DY_output"
Topoutputfile="$FileMainLocation/output/Top_output"
Dibosonoutputfile="$FileMainLocation/output/Di_output"
Tribosonoutputfile="$FileMainLocation/output/Tri_output"



StartStep=1
MaxStep=20

#--------------------------------------------------------------------
# Use parallel to contral njob to prevent computer memory reach max 
#--------------------------------------------------------------------

parallel -j 10 --link ::: $FileMainLocation/ee_DY_punzi.o ::: $(seq "$StartStep" "$MaxStep") ::: $(seq "$StartStep" "$MaxStep" | xargs printf "${DYoutputfile}_%s.root\n")
echo "Finish Scan Drell-Yan process"

parallel -j 10 --link ::: $FileMainLocation/ee_Top_punzi.o ::: $(seq "$StartStep" "$MaxStep") ::: $(seq "$StartStep" "$MaxStep" | xargs printf "${Topoutputfile}_%s.root\n")
echo "Finish Scan Top process"

parallel -j 10 --link ::: $FileMainLocation/ee_Diboson_punzi.o ::: $(seq "$StartStep" "$MaxStep") ::: $(seq "$StartStep" "$MaxStep" | xargs printf "${Dibosonoutputfile}_%s.root\n")
echo "Finish Scan Diboson process"

parallel -j 10 --link ::: $FileMainLocation/ee_Triboson_punzi.o ::: $(seq "$StartStep" "$MaxStep") ::: $(seq "$StartStep" "$MaxStep" | xargs printf "${Tribosonoutputfile}_%s.root\n")
echo "Finish Scan Triboson process"


#-------------------------------
# Clear process files
#-------------------------------
# if [ "ls -A $FileMainLocation/output/*" = "" ]; then
    # echo "$FileMainLocation/output/* is indeed empty"
# else
    # echo "$FileMainLocation/output/* is not empty"
    # echo "Clear output directory" && rm $FileMainLocation/output/*
# fi
test -e "$FileMainLocation/ee_DY_punzi.o" && { echo "Delete ee_DY_punzi.o"; rm $FileMainLocation/ee_DY_punzi.o ;}
test -e "$FileMainLocation/ee_Top_punzi.o" && { echo "Delete ee_Top_punzi.o"; rm $FileMainLocation/ee_Top_punzi.o ;}
test -e "$FileMainLocation/ee_Diboson_punzi.o" && { echo "Delete ee_Diboson_punzi.o"; rm $FileMainLocation/ee_Diboson_punzi.o ;}
test -e "$FileMainLocation/ee_Triboson_punzi.o" && { echo "Delete ee_Triboson_punzi.o"; rm $FileMainLocation/ee_Triboson_punzi.o ;}

for i in {1..20}
{
    hadd "$FileMainLocation/bg_alpha$i.root" "$FileMainLocation/output/"*_"$i".root
}

root -q $FileMainLocation/ee_punzi.C 

#root -q $FileMainLocation/draw_alpha_punzi.C

test -e "$FileMainLocation/output/*.root" && { echo "Delete output root"; rm $FileMainLocation/output/*.root ;}

test -e "$FileMainLocation/bg_alpha*" && { echo "Delete bg_alpha root"; rm $FileMainLocation/bg_alpha* ;}


echo "Done Scan Alpha cut"

# Draw punzi result





