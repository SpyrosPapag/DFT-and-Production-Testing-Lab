####################################################################
# Simple script to synthesize a design and prepare it for tetramax
####################################################################

# define variables for the design name and the clock name
set mydesign s1423
set myclk CK

# clear any previously loaded designs
remove_design -all

# Analyzes  the specified HDL source files; stores the design templates 
# they define into the specified library in a format  ready to elaborate 
# and specialize as needed to link a full design.
analyze -f verilog ${mydesign}.v

# Builds  a  design from the intermediate format of a Verilog module, 
# a VHDL entity and architecture, or a VHDL configuration.
elaborate ${mydesign}

#  Set the working design.
current_design ${mydesign}

# Create a  clock object and define its waveform in the current design.
create_clock -period 5.5  ${myclk}

# Specify the clock network latency
set_clock_latency    2  ${myclk}

# Sets input delay on input ports relative to the clock signal
# (clock is excluded)
set_input_delay 2 -clock ${myclk} [remove_from_collection [all_inputs] ${myclk}]

# Sets  output  delay  on output ports relative to the clock signal
set_output_delay 2 -clock ${myclk} [all_outputs]

# Sets  attributes  on  input ports of the current design
# that specify that a library cell or output pin of a library cell
# drives the specified ports.
set_driving_cell -library umcl18u250t2_wc -lib_cell INVD1 [remove_from_collection [all_inputs] ${myclk}]

# Sets the load attribute (capacitance in library units) on the specified ports and nets
set_load 0.1 [all_outputs]

#Sets  the max_fanout attribute to a specified value on specified
#input ports and designs.
set_max_fanout 8 [all_inputs]

#Set the fanout_load attribute on the specified output ports of
#the current design (in units of the target library)
set_fanout_load 2 [all_outputs]

#Set the max_area attribute to a specified value on the current design.
set_max_area 0


#Perform logic-level  and gate-level synthesis and optimization on the current design.
compile

#Check the current design for consistency
check_design

# Display  a  summary  of all of the optimization and design rule
# constraints with violations in the current design
report_constraint -all_violators

# Write output files
write -format verilog -hierarchy -output ${mydesign}_synth.v
write_sdf ${mydesign}_synth.sdf
write_sdc  ${mydesign}.sdc

# create reports
report_area
report_timing


####################################################################
# Testing Part...
####################################################################

set test_default_delay       0
set test_default_bidir_delay 0
set test_default_strobe      40
set test_default_period      100

set test_default_scan_style multiplexed_flip_flop

set_scan_configuration -create_dedicated_scan_out_ports true
create_test_protocol -infer_async -infer_clock

# 2 chains
set_scan_configuration -chain_count 2

compile -scan
report_constraint -all_violators
dft_drc -verbose

insert_dft
set_drive 2 test_si
set_drive 2 test_se

# since you've already inserted scan-ff's, we don't want that to happen again,
# when we run insert_dft

set_scan_configuration -replace false
insert_dft

report_constraint -all_violators
dft_drc -verbose -coverage_estimate
report_scan_path -view existing -chain all
report_cell 

## set_dft_signal -view existing_dft -type ScanClock -timing [list 45 55] -port CK

write_test_protocol -output ${mydesign}.spf

check_design

change_names -rules verilog -hierarchy -verbose

write -format ddc -hierarchy -output  ${mydesign}_scan_netlist.ddc
write -format verilog -hierarchy -output  ${mydesign}_scan_netlist.v
write_sdf -version 2.1  ${mydesign}_scan_netlist.sdf


preview_dft -show cells

report_timing -delay max

exit

