set mydesign c7552

remove_design -all
analyze -f verilog ${mydesign}.v

elaborate $mydesign
current_design $mydesign
create_clock -period 8  -name clk

set_clock_latency    2  clk
set_input_delay      2 -clock clk [remove_from_collection [all_inputs] clk]
set_output_delay     2 -clock clk [all_outputs]
set_driving_cell -library umcl18u250t2_wc -lib_cell INVD1 [remove_from_collection [all_inputs] clk]
set_load 0.1 [all_outputs]
set_max_fanout 8 [all_inputs]
set_fanout_load 8 [all_outputs]
set_max_area 0
compile
check_design
report_constraint -all_violators
write -format verilog -hierarchy -output ${mydesign}_synth.v
write_sdf ${mydesign}_synth.sdf
write_sdc  ${mydesign}.sdc


report_area
report_timing

quit