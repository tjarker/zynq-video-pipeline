set SynModuleInfo {
  {SRCNAME invstripe MODELNAME invstripe RTLNAME invstripe IS_TOP 1
    SUBMODULES {
      {MODELNAME invstripe_fsub_32ns_32ns_32_9_full_dsp_1 RTLNAME invstripe_fsub_32ns_32ns_32_9_full_dsp_1 BINDTYPE op TYPE fsub IMPL fulldsp LATENCY 8 ALLOW_PRAGMA 1}
      {MODELNAME invstripe_fmul_32ns_32ns_32_5_max_dsp_1 RTLNAME invstripe_fmul_32ns_32ns_32_5_max_dsp_1 BINDTYPE op TYPE fmul IMPL maxdsp LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME invstripe_uitofp_32ns_32_7_no_dsp_1 RTLNAME invstripe_uitofp_32ns_32_7_no_dsp_1 BINDTYPE op TYPE uitofp IMPL auto LATENCY 6 ALLOW_PRAGMA 1}
      {MODELNAME invstripe_sitofp_32ns_32_7_no_dsp_1 RTLNAME invstripe_sitofp_32ns_32_7_no_dsp_1 BINDTYPE op TYPE sitofp IMPL auto LATENCY 6 ALLOW_PRAGMA 1}
      {MODELNAME invstripe_sdiv_9ns_9ns_9_13_1 RTLNAME invstripe_sdiv_9ns_9ns_9_13_1 BINDTYPE op TYPE sdiv IMPL auto LATENCY 12 ALLOW_PRAGMA 1}
      {MODELNAME invstripe_invstripe_stream_stream_axis_ap_uint_32_1ul_1ul_1ul_0_float_hist_RAM_AUTO_1R1W RTLNAME invstripe_invstripe_stream_stream_axis_ap_uint_32_1ul_1ul_1ul_0_float_hist_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME invstripe_regslice_both RTLNAME invstripe_regslice_both BINDTYPE interface TYPE interface_regslice INSTNAME invstripe_regslice_both_U}
    }
  }
}
