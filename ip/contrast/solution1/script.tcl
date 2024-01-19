############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project contrast
set_top contrast
add_files contrast/contrast.cpp
add_files -tb streamulator/axipng.cpp -cflags "-Wno-unknown-pragmas"
add_files -tb streamulator/axipng.h -cflags "-Wno-unknown-pragmas"
add_files -tb streamulator/miniz.c -cflags "-Wno-unknown-pragmas"
add_files -tb streamulator/miniz.h -cflags "-Wno-unknown-pragmas"
add_files -tb streamulator/spng.c -cflags "-Wno-unknown-pragmas"
add_files -tb streamulator/spng.h -cflags "-Wno-unknown-pragmas"
add_files -tb streamulator/streamulator.cpp -cflags "-Wno-unknown-pragmas"
add_files -tb streamulator/streamulator.h -cflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z020-clg400-1}
create_clock -period 7 -name default
config_export -format ip_catalog -rtl verilog
source "./contrast/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog
