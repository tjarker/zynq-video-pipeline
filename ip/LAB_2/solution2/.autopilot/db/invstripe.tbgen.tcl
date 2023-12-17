set moduleName invstripe
set isTopModule 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type function
set FunctionProtocol ap_ctrl_none
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set DLRegFirstOffset 0
set DLRegItemOffset 0
set C_modelName {invstripe}
set C_modelType { void 0 }
set C_modelArgList {
	{ src_V_data_V int 32 regular {axi_s 0 volatile  { src Data } }  }
	{ src_V_keep_V int 4 regular {axi_s 0 volatile  { src Keep } }  }
	{ src_V_strb_V int 4 regular {axi_s 0 volatile  { src Strb } }  }
	{ src_V_user_V int 1 regular {axi_s 0 volatile  { src User } }  }
	{ src_V_last_V int 1 regular {axi_s 0 volatile  { src Last } }  }
	{ src_V_id_V int 1 regular {axi_s 0 volatile  { src ID } }  }
	{ src_V_dest_V int 1 regular {axi_s 0 volatile  { src Dest } }  }
	{ dst_V_data_V int 32 regular {axi_s 1 volatile  { dst Data } }  }
	{ dst_V_keep_V int 4 regular {axi_s 1 volatile  { dst Keep } }  }
	{ dst_V_strb_V int 4 regular {axi_s 1 volatile  { dst Strb } }  }
	{ dst_V_user_V int 1 regular {axi_s 1 volatile  { dst User } }  }
	{ dst_V_last_V int 1 regular {axi_s 1 volatile  { dst Last } }  }
	{ dst_V_id_V int 1 regular {axi_s 1 volatile  { dst ID } }  }
	{ dst_V_dest_V int 1 regular {axi_s 1 volatile  { dst Dest } }  }
	{ f float 32 regular  }
}
set hasAXIMCache 0
set C_modelArgMapList {[ 
	{ "Name" : "src_V_data_V", "interface" : "axis", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_V_keep_V", "interface" : "axis", "bitwidth" : 4, "direction" : "READONLY"} , 
 	{ "Name" : "src_V_strb_V", "interface" : "axis", "bitwidth" : 4, "direction" : "READONLY"} , 
 	{ "Name" : "src_V_user_V", "interface" : "axis", "bitwidth" : 1, "direction" : "READONLY"} , 
 	{ "Name" : "src_V_last_V", "interface" : "axis", "bitwidth" : 1, "direction" : "READONLY"} , 
 	{ "Name" : "src_V_id_V", "interface" : "axis", "bitwidth" : 1, "direction" : "READONLY"} , 
 	{ "Name" : "src_V_dest_V", "interface" : "axis", "bitwidth" : 1, "direction" : "READONLY"} , 
 	{ "Name" : "dst_V_data_V", "interface" : "axis", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_V_keep_V", "interface" : "axis", "bitwidth" : 4, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_V_strb_V", "interface" : "axis", "bitwidth" : 4, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_V_user_V", "interface" : "axis", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_V_last_V", "interface" : "axis", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_V_id_V", "interface" : "axis", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_V_dest_V", "interface" : "axis", "bitwidth" : 1, "direction" : "WRITEONLY"} , 
 	{ "Name" : "f", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} ]}
# RTL Port declarations: 
set portNum 22
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst_n sc_in sc_logic 1 reset -1 active_low_sync } 
	{ src_TDATA sc_in sc_lv 32 signal 0 } 
	{ src_TVALID sc_in sc_logic 1 invld 6 } 
	{ src_TREADY sc_out sc_logic 1 inacc 6 } 
	{ src_TKEEP sc_in sc_lv 4 signal 1 } 
	{ src_TSTRB sc_in sc_lv 4 signal 2 } 
	{ src_TUSER sc_in sc_lv 1 signal 3 } 
	{ src_TLAST sc_in sc_lv 1 signal 4 } 
	{ src_TID sc_in sc_lv 1 signal 5 } 
	{ src_TDEST sc_in sc_lv 1 signal 6 } 
	{ dst_TDATA sc_out sc_lv 32 signal 7 } 
	{ dst_TVALID sc_out sc_logic 1 outvld 13 } 
	{ dst_TREADY sc_in sc_logic 1 outacc 13 } 
	{ dst_TKEEP sc_out sc_lv 4 signal 8 } 
	{ dst_TSTRB sc_out sc_lv 4 signal 9 } 
	{ dst_TUSER sc_out sc_lv 1 signal 10 } 
	{ dst_TLAST sc_out sc_lv 1 signal 11 } 
	{ dst_TID sc_out sc_lv 1 signal 12 } 
	{ dst_TDEST sc_out sc_lv 1 signal 13 } 
	{ f sc_in sc_lv 32 signal 14 } 
	{ f_ap_vld sc_in sc_logic 1 invld 14 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst_n", "role": "default" }} , 
 	{ "name": "src_TDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_V_data_V", "role": "default" }} , 
 	{ "name": "src_TVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "invld", "bundle":{"name": "src_V_dest_V", "role": "default" }} , 
 	{ "name": "src_TREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "inacc", "bundle":{"name": "src_V_dest_V", "role": "default" }} , 
 	{ "name": "src_TKEEP", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "src_V_keep_V", "role": "default" }} , 
 	{ "name": "src_TSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "src_V_strb_V", "role": "default" }} , 
 	{ "name": "src_TUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "src_V_user_V", "role": "default" }} , 
 	{ "name": "src_TLAST", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "src_V_last_V", "role": "default" }} , 
 	{ "name": "src_TID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "src_V_id_V", "role": "default" }} , 
 	{ "name": "src_TDEST", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "src_V_dest_V", "role": "default" }} , 
 	{ "name": "dst_TDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_V_data_V", "role": "default" }} , 
 	{ "name": "dst_TVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_V_dest_V", "role": "default" }} , 
 	{ "name": "dst_TREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "outacc", "bundle":{"name": "dst_V_dest_V", "role": "default" }} , 
 	{ "name": "dst_TKEEP", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "dst_V_keep_V", "role": "default" }} , 
 	{ "name": "dst_TSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "dst_V_strb_V", "role": "default" }} , 
 	{ "name": "dst_TUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "dst_V_user_V", "role": "default" }} , 
 	{ "name": "dst_TLAST", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "dst_V_last_V", "role": "default" }} , 
 	{ "name": "dst_TID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "dst_V_id_V", "role": "default" }} , 
 	{ "name": "dst_TDEST", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "dst_V_dest_V", "role": "default" }} , 
 	{ "name": "f", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "f", "role": "default" }} , 
 	{ "name": "f_ap_vld", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "invld", "bundle":{"name": "f", "role": "ap_vld" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24"],
		"CDFG" : "invstripe",
		"Protocol" : "ap_ctrl_none",
		"ControlExist" : "0", "ap_start" : "0", "ap_ready" : "0", "ap_done" : "0", "ap_continue" : "0", "ap_idle" : "0", "real_start" : "0",
		"Pipeline" : "Aligned", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "20",
		"VariableLatency" : "0", "ExactLatency" : "43", "EstimateLatencyMin" : "43", "EstimateLatencyMax" : "43",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "src_V_data_V", "Type" : "Axis", "Direction" : "I", "BaseName" : "src",
				"BlockSignal" : [
					{"Name" : "src_TDATA_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "src_V_keep_V", "Type" : "Axis", "Direction" : "I", "BaseName" : "src"},
			{"Name" : "src_V_strb_V", "Type" : "Axis", "Direction" : "I", "BaseName" : "src"},
			{"Name" : "src_V_user_V", "Type" : "Axis", "Direction" : "I", "BaseName" : "src"},
			{"Name" : "src_V_last_V", "Type" : "Axis", "Direction" : "I", "BaseName" : "src"},
			{"Name" : "src_V_id_V", "Type" : "Axis", "Direction" : "I", "BaseName" : "src"},
			{"Name" : "src_V_dest_V", "Type" : "Axis", "Direction" : "I", "BaseName" : "src"},
			{"Name" : "dst_V_data_V", "Type" : "Axis", "Direction" : "O", "BaseName" : "dst",
				"BlockSignal" : [
					{"Name" : "dst_TDATA_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "dst_V_keep_V", "Type" : "Axis", "Direction" : "O", "BaseName" : "dst"},
			{"Name" : "dst_V_strb_V", "Type" : "Axis", "Direction" : "O", "BaseName" : "dst"},
			{"Name" : "dst_V_user_V", "Type" : "Axis", "Direction" : "O", "BaseName" : "dst"},
			{"Name" : "dst_V_last_V", "Type" : "Axis", "Direction" : "O", "BaseName" : "dst"},
			{"Name" : "dst_V_id_V", "Type" : "Axis", "Direction" : "O", "BaseName" : "dst"},
			{"Name" : "dst_V_dest_V", "Type" : "Axis", "Direction" : "O", "BaseName" : "dst"},
			{"Name" : "f", "Type" : "Vld", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "f_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "y", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "x", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "first_r", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "last_r", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "first_g", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "last_g", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "first_b", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "last_b", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "invstripe_stream_stream_axis_ap_uint_32_1ul_1ul_1ul_0_float_hist", "Type" : "Memory", "Direction" : "IO"},
			{"Name" : "invstripe_stream_stream_axis_ap_uint_32_1ul_1ul_1ul_0_float_hist_1", "Type" : "Memory", "Direction" : "IO"},
			{"Name" : "invstripe_stream_stream_axis_ap_uint_32_1ul_1ul_1ul_0_float_hist_2", "Type" : "Memory", "Direction" : "IO"},
			{"Name" : "scale_r", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "scale_g", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "scale_b", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "threshold", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "stop", "Type" : "OVld", "Direction" : "IO"},
			{"Name" : "max", "Type" : "OVld", "Direction" : "IO"}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.invstripe_stream_stream_axis_ap_uint_32_1ul_1ul_1ul_0_float_hist_U", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.invstripe_stream_stream_axis_ap_uint_32_1ul_1ul_1ul_0_float_hist_1_U", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.invstripe_stream_stream_axis_ap_uint_32_1ul_1ul_1ul_0_float_hist_2_U", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fsub_32ns_32ns_32_9_full_dsp_1_U1", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fmul_32ns_32ns_32_5_max_dsp_1_U2", "Parent" : "0"},
	{"ID" : "6", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.uitofp_32ns_32_7_no_dsp_1_U3", "Parent" : "0"},
	{"ID" : "7", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.sitofp_32ns_32_7_no_dsp_1_U4", "Parent" : "0"},
	{"ID" : "8", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.sdiv_9ns_9ns_9_13_1_U5", "Parent" : "0"},
	{"ID" : "9", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.sdiv_9ns_9ns_9_13_1_U6", "Parent" : "0"},
	{"ID" : "10", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.sdiv_9ns_9ns_9_13_1_U7", "Parent" : "0"},
	{"ID" : "11", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.regslice_both_src_V_data_V_U", "Parent" : "0"},
	{"ID" : "12", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.regslice_both_src_V_keep_V_U", "Parent" : "0"},
	{"ID" : "13", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.regslice_both_src_V_strb_V_U", "Parent" : "0"},
	{"ID" : "14", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.regslice_both_src_V_user_V_U", "Parent" : "0"},
	{"ID" : "15", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.regslice_both_src_V_last_V_U", "Parent" : "0"},
	{"ID" : "16", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.regslice_both_src_V_id_V_U", "Parent" : "0"},
	{"ID" : "17", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.regslice_both_src_V_dest_V_U", "Parent" : "0"},
	{"ID" : "18", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.regslice_both_dst_V_data_V_U", "Parent" : "0"},
	{"ID" : "19", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.regslice_both_dst_V_keep_V_U", "Parent" : "0"},
	{"ID" : "20", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.regslice_both_dst_V_strb_V_U", "Parent" : "0"},
	{"ID" : "21", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.regslice_both_dst_V_user_V_U", "Parent" : "0"},
	{"ID" : "22", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.regslice_both_dst_V_last_V_U", "Parent" : "0"},
	{"ID" : "23", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.regslice_both_dst_V_id_V_U", "Parent" : "0"},
	{"ID" : "24", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.regslice_both_dst_V_dest_V_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	invstripe {
		src_V_data_V {Type I LastRead 0 FirstWrite -1}
		src_V_keep_V {Type I LastRead 0 FirstWrite -1}
		src_V_strb_V {Type I LastRead 0 FirstWrite -1}
		src_V_user_V {Type I LastRead 0 FirstWrite -1}
		src_V_last_V {Type I LastRead 0 FirstWrite -1}
		src_V_id_V {Type I LastRead 0 FirstWrite -1}
		src_V_dest_V {Type I LastRead 0 FirstWrite -1}
		dst_V_data_V {Type O LastRead -1 FirstWrite 41}
		dst_V_keep_V {Type O LastRead -1 FirstWrite 41}
		dst_V_strb_V {Type O LastRead -1 FirstWrite 41}
		dst_V_user_V {Type O LastRead -1 FirstWrite 41}
		dst_V_last_V {Type O LastRead -1 FirstWrite 41}
		dst_V_id_V {Type O LastRead -1 FirstWrite 41}
		dst_V_dest_V {Type O LastRead -1 FirstWrite 41}
		f {Type I LastRead 0 FirstWrite -1}
		y {Type IO LastRead -1 FirstWrite -1}
		x {Type IO LastRead -1 FirstWrite -1}
		first_r {Type IO LastRead -1 FirstWrite -1}
		last_r {Type IO LastRead -1 FirstWrite -1}
		first_g {Type IO LastRead -1 FirstWrite -1}
		last_g {Type IO LastRead -1 FirstWrite -1}
		first_b {Type IO LastRead -1 FirstWrite -1}
		last_b {Type IO LastRead -1 FirstWrite -1}
		invstripe_stream_stream_axis_ap_uint_32_1ul_1ul_1ul_0_float_hist {Type IO LastRead -1 FirstWrite -1}
		invstripe_stream_stream_axis_ap_uint_32_1ul_1ul_1ul_0_float_hist_1 {Type IO LastRead -1 FirstWrite -1}
		invstripe_stream_stream_axis_ap_uint_32_1ul_1ul_1ul_0_float_hist_2 {Type IO LastRead -1 FirstWrite -1}
		scale_r {Type IO LastRead -1 FirstWrite -1}
		scale_g {Type IO LastRead -1 FirstWrite -1}
		scale_b {Type IO LastRead -1 FirstWrite -1}
		threshold {Type IO LastRead -1 FirstWrite -1}
		stop {Type IO LastRead -1 FirstWrite -1}
		max {Type IO LastRead -1 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "43", "Max" : "43"}
	, {"Name" : "Interval", "Min" : "20", "Max" : "20"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	src_V_data_V { axis {  { src_TDATA in_data 0 32 } } }
	src_V_keep_V { axis {  { src_TKEEP in_data 0 4 } } }
	src_V_strb_V { axis {  { src_TSTRB in_data 0 4 } } }
	src_V_user_V { axis {  { src_TUSER in_data 0 1 } } }
	src_V_last_V { axis {  { src_TLAST in_data 0 1 } } }
	src_V_id_V { axis {  { src_TID in_data 0 1 } } }
	src_V_dest_V { axis {  { src_TVALID in_vld 0 1 }  { src_TREADY in_acc 1 1 }  { src_TDEST in_data 0 1 } } }
	dst_V_data_V { axis {  { dst_TDATA out_data 1 32 } } }
	dst_V_keep_V { axis {  { dst_TKEEP out_data 1 4 } } }
	dst_V_strb_V { axis {  { dst_TSTRB out_data 1 4 } } }
	dst_V_user_V { axis {  { dst_TUSER out_data 1 1 } } }
	dst_V_last_V { axis {  { dst_TLAST out_data 1 1 } } }
	dst_V_id_V { axis {  { dst_TID out_data 1 1 } } }
	dst_V_dest_V { axis {  { dst_TVALID out_vld 1 1 }  { dst_TREADY out_acc 0 1 }  { dst_TDEST out_data 1 1 } } }
	f { ap_vld {  { f in_data 0 32 }  { f_ap_vld in_vld 0 1 } } }
}

set maxi_interface_dict [dict create]

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
