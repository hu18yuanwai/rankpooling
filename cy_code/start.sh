#!/bin/bash
cd improved_trajectory
bash run.sh
cd ..
cd GMM
bash run.sh
cd ..
cd FV
bash run.sh
cd ..
cd Darwin
bash run.sh
cd ..
cd trainAndTest
bash run.sh
cd ..

