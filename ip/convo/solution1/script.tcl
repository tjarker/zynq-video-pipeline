############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project convo
set_top convo
add_files convo/convo.cpp
add_files -tb streamulator/axipng.cpp
add_files -tb streamulator/axipng.h
add_files -tb streamulator/miniz.c
add_files -tb streamulator/miniz.h
add_files -tb streamulator/spng.c
add_files -tb streamulator/spng.h
add_files -tb streamulator/streamulator.cpp
add_files -tb streamulator/streamulator.h
open_solution "solution1" -flow_target vivado
set_part {xc7z020-clg400-1}
create_clock -period 7 -name default
#source "./convo/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
