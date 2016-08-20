#!/bin/bash
make
cd vl_gmm
make
cp vlgmm ../debug/
cd ..
./debug/getGMM
