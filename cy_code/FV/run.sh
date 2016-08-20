#!/bin/bash
make
cd vl_fisher
make
cp vlfisher ../debug/
cd ..
./debug/FV
