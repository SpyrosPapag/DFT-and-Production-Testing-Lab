synthesis:
	dc_shell -f run.tcl | tee syn.log
.PHONY: synthesis

atpg:
	tmax -shell -notcl tmax.script | tee tmax.log
.PHONY: atpg

clean:
	$(RM) -r WORK *.log *.svf *.sdf \
	*_netlist.* *.sdc *.spf *_synth.v \
	*_myvectors.v *.dat \
	csrc ucli.key vc_hdrs.h DVEfiles *.daidir *.vpd s5378_tb_sim
.PHONY:clean


SHELL = /bin/bash
VCS_OPTS = -timescale=1ps/1ps -full64 -debug_access+r

compile_tb:
	vcs $(VCS_OPTS) -sdf max:s5378_tb.DUT:s5378_scan_netlist.sdf s5378_tb.v s5378_scan_netlist.v \
	/home/eda/libraries/UMCL18U250D2_2.4/verilog_simulation_models/*.v -o s5378_tb_sim +sdfverbose +neg_tchk | tee compile_tb.log
.PHONY: compile_tb

run_tb:
	./s5378_tb_sim | tee run_tb.log
.PHONY: run_tb