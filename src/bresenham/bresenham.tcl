############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project bresenham_accelerator
set_top bresenham
add_files bresenham.cpp
add_files bresenham.hpp
add_files -tb bresenham_tb.cpp
open_solution "naive"
set_part {xc7z020clg484-1} -tool vivado
create_clock -period 10 -name default
source "naive_directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
