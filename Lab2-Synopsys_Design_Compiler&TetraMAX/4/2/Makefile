synthesis:
	dc_shell -f run.tcl | tee syn.log
.PHONY: synthesis

atpg:
	tmax -shell -notcl tmax.script | tee tmax.log
.PHONY: atpg

clean:
	$(RM) -r WORK *.log *.svf *.sdf \
	*_netlist.* *.sdc *.spf *_synth.v \
	*_myvectors.v *.dat
.PHONY:clean