#!/bin/bash

mkdir build
cd build && cmake .. && make && ./acceptance_glowingsceptre && ./test_gs
