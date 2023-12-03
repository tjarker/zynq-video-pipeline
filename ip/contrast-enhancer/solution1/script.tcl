############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project contrast-enhancer
set_top hfilt
add_files contrast-enhancer/src/hfilt.cpp
add_files -tb contrast-enhancer/src/streamulator/axipng.cpp
add_files -tb contrast-enhancer/src/streamulator/axipng.h
add_files -tb contrast-enhancer/src/streamulator/miniz.c
add_files -tb contrast-enhancer/src/streamulator/miniz.h
add_files -tb contrast-enhancer/src/streamulator/spng.c
add_files -tb contrast-enhancer/src/streamulator/spng.h
add_files -tb contrast-enhancer/src/streamulator/streamulator.cpp
add_files -tb contrast-enhancer/src/streamulator/streamulator.h
open_solution "solution1" -flow_target vivado
set_part {xc7z020clg400-1}
create_clock -period 7 -name default
#source "./contrast-enhancer/solution1/directives.tcl"
csim_design -clean
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog
