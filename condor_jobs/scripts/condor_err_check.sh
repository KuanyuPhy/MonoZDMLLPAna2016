#!/bin/bash
set -eu -o pipefail

### This script is used to clear condor output file ###

directory="/afs/cern.ch/user/k/kuanyu/ZtoLL"
### clear error file
log_file="condor_errorjob.log"

#1.check the ERROR message in err file and create condor_errorjob.log
for file in "$directory/error"/*.err; do
    if grep -iq "error" "$file" ; then
        echo "$file" >> "condor_errorjob.log"
    fi
done








