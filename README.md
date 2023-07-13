# MonoZDMLLPAna2016
Welcome to the README file for my master's research project. This project is a collection of the code used in my master's research.

### Table of Content
-----
- [optimizing-cut-performance](#optimizing-cut-performance)





### optimizing-cut-performance
This folder contains calculations and optimizations related to cut efficiency($\epsilon$). 
#### For the cut efficiency 
the ($\epsilon_{sig}$) and ($\epsilon_{top}$) is stored in the following:  
```
# For Signal
/optimizing-cut-performance/Signal/src

# For Top
/optimizing-cut-performance/Top/src

# For Topemu
/optimizing-cut-performance/Topemu/src
```
Here, I compare the cut flow efficiency of the signal for each sample and compare the efficiency between the top ee and top e($\mu$).  
The approach involves extracting the histogram (__h_ee_pass__) and applying offline cuts to calculate the number of events that pass each individual cut. For reference on __h_ee_pass__, you can consult the code in the 'ana' directory


