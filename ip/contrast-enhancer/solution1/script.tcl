############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project contrast-enhancer
set_top hfilt
add_files contrast-enhancer/src/hfilt.cpp
add_files -tb contrast-enhancer/src/streamulator/axipng.cpp -cflags "-Wno-unknown-pragmas"
add_files -tb contrast-enhancer/src/streamulator/axipng.h -cflags "-Wno-unknown-pragmas"
add_files -tb contrast-enhancer/src/streamulator/miniz.c -cflags "-Wno-unknown-pragmas"
add_files -tb contrast-enhancer/src/streamulator/miniz.h -cflags "-Wno-unknown-pragmas"
add_files -tb contrast-enhancer/src/streamulator/spng.c -cflags "-Wno-unknown-pragmas"
add_files -tb contrast-enhancer/src/streamulator/spng.h -cflags "-Wno-unknown-pragmas"
add_files -tb contrast-enhancer/src/streamulator/streamulator.cpp -cflags "-Wno-unknown-pragmas"
add_files -tb contrast-enhancer/src/streamulator/streamulator.h -cflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z020-clg400-1}
create_clock -period 7 -name default
config_export -format ip_catalog -rtl verilog
source "./contrast-enhancer/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog
