
set TopModule "invstripe"
set ClockPeriod 7
set ClockList ap_clk
set HasVivadoClockPeriod 1
set CombLogicFlag 0
set PipelineFlag 1
set DataflowTaskPipelineFlag 1
set TrivialPipelineFlag 0
set noPortSwitchingFlag 0
set FloatingPointFlag 1
set FftOrFirFlag 0
set NbRWValue 0
set intNbAccess 0
set NewDSPMapping 1
set HasDSPModule 0
set ResetLevelFlag 0
set ResetStyle control
set ResetSyncFlag 1
set ResetRegisterFlag 0
set ResetVariableFlag 1
set ResetRegisterNum 0
set FsmEncStyle onehot
set MaxFanout 0
set RtlPrefix {}
set RtlSubPrefix invstripe_
set ExtraCCFlags {}
set ExtraCLdFlags {}
set SynCheckOptions {}
set PresynOptions {}
set PreprocOptions {}
set SchedOptions {}
set BindOptions {}
set RtlGenOptions {}
set RtlWriterOptions {}
set CbcGenFlag {}
set CasGenFlag {}
set CasMonitorFlag {}
set AutoSimOptions {}
set ExportMCPathFlag 0
set SCTraceFileName mytrace
set SCTraceFileFormat vcd
set SCTraceOption all
set TargetInfo xc7z020:-clg400:-1
set SourceFiles {sc {} c ../../PYNQ-Z2/hls/invstripe.cpp}
set SourceFlags {sc {} c {{}}}
set DirectiveFile {}
set TBFiles {verilog {../../PYNQ-Z2/hls/streamulator/axipng.cpp ../../PYNQ-Z2/hls/streamulator/axipng.h ../../PYNQ-Z2/hls/streamulator/miniz.c ../../PYNQ-Z2/hls/streamulator/miniz.h ../../PYNQ-Z2/hls/streamulator/spng.c ../../PYNQ-Z2/hls/streamulator/spng.h ../../PYNQ-Z2/hls/streamulator/streamulator.cpp ../../PYNQ-Z2/hls/streamulator/streamulator.h} bc {../../PYNQ-Z2/hls/streamulator/axipng.cpp ../../PYNQ-Z2/hls/streamulator/axipng.h ../../PYNQ-Z2/hls/streamulator/miniz.c ../../PYNQ-Z2/hls/streamulator/miniz.h ../../PYNQ-Z2/hls/streamulator/spng.c ../../PYNQ-Z2/hls/streamulator/spng.h ../../PYNQ-Z2/hls/streamulator/streamulator.cpp ../../PYNQ-Z2/hls/streamulator/streamulator.h} sc {../../PYNQ-Z2/hls/streamulator/axipng.cpp ../../PYNQ-Z2/hls/streamulator/axipng.h ../../PYNQ-Z2/hls/streamulator/miniz.c ../../PYNQ-Z2/hls/streamulator/miniz.h ../../PYNQ-Z2/hls/streamulator/spng.c ../../PYNQ-Z2/hls/streamulator/spng.h ../../PYNQ-Z2/hls/streamulator/streamulator.cpp ../../PYNQ-Z2/hls/streamulator/streamulator.h} vhdl {../../PYNQ-Z2/hls/streamulator/axipng.cpp ../../PYNQ-Z2/hls/streamulator/axipng.h ../../PYNQ-Z2/hls/streamulator/miniz.c ../../PYNQ-Z2/hls/streamulator/miniz.h ../../PYNQ-Z2/hls/streamulator/spng.c ../../PYNQ-Z2/hls/streamulator/spng.h ../../PYNQ-Z2/hls/streamulator/streamulator.cpp ../../PYNQ-Z2/hls/streamulator/streamulator.h} c {} cas {../../PYNQ-Z2/hls/streamulator/axipng.cpp ../../PYNQ-Z2/hls/streamulator/axipng.h ../../PYNQ-Z2/hls/streamulator/miniz.c ../../PYNQ-Z2/hls/streamulator/miniz.h ../../PYNQ-Z2/hls/streamulator/spng.c ../../PYNQ-Z2/hls/streamulator/spng.h ../../PYNQ-Z2/hls/streamulator/streamulator.cpp ../../PYNQ-Z2/hls/streamulator/streamulator.h}}
set SpecLanguage C
set TVInFiles {bc {} c {} sc {} cas {} vhdl {} verilog {}}
set TVOutFiles {bc {} c {} sc {} cas {} vhdl {} verilog {}}
set TBTops {verilog {} bc {} sc {} vhdl {} c {} cas {}}
set TBInstNames {verilog {} bc {} sc {} vhdl {} c {} cas {}}
set XDCFiles {}
set ExtraGlobalOptions {"area_timing" 1 "clock_gate" 1 "impl_flow" map "power_gate" 0}
set TBTVFileNotFound {}
set AppFile ../hls.app
set ApsFile solution2.aps
set AvePath ../../.
set DefaultPlatform DefaultPlatform
set multiClockList {}
set SCPortClockMap {}
set intNbAccess 0
set PlatformFiles {{DefaultPlatform {xilinx/zynq/zynq}}}
set HPFPO 0
