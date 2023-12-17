############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project LAB_2
set_top invstripe
add_files PYNQ-Z2/hls/invstripe.cpp
add_files -tb PYNQ-Z2/hls/streamulator/axipng.cpp -cflags "-Wno-unknown-pragmas"
add_files -tb PYNQ-Z2/hls/streamulator/axipng.h -cflags "-Wno-unknown-pragmas"
add_files -tb PYNQ-Z2/hls/streamulator/miniz.c -cflags "-Wno-unknown-pragmas"
add_files -tb PYNQ-Z2/hls/streamulator/miniz.h -cflags "-Wno-unknown-pragmas"
add_files -tb PYNQ-Z2/hls/streamulator/spng.c -cflags "-Wno-unknown-pragmas"
add_files -tb PYNQ-Z2/hls/streamulator/spng.h -cflags "-Wno-unknown-pragmas"
add_files -tb PYNQ-Z2/hls/streamulator/streamulator.cpp -cflags "-Wno-unknown-pragmas"
add_files -tb PYNQ-Z2/hls/streamulator/streamulator.h -cflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z020-clg400-1}
create_clock -period 7 -name default
source "./LAB_2/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
