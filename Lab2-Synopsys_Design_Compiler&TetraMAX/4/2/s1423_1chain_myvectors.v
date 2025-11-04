STIL 1.0 { Design 2005; }
Header {
   Title "  TetraMAX(R)  T-2022.03-SP1-i20220414_145826 STIL output";
   Date "Mon Jun  2 20:02:09 2025";
   Source "Minimal STIL for design `s1423'";
   History {
      Ann {*  Incoming_Date "Mon Jun  2 20:01:52 2025"  *}
      Ann {*  Incoming_Src "DFT Compiler T-2022.03-SP1"  *}
      Ann {*     Uncollapsed Stuck Fault Summary Report *}
      Ann {* ----------------------------------------------- *}
      Ann {* fault class                     code   #faults *}
      Ann {* ------------------------------  ----  --------- *}
      Ann {* Detected                         DT       3274 *}
      Ann {* Possibly detected                PT          0 *}
      Ann {* Undetectable                     UD          4 *}
      Ann {* ATPG untestable                  AU          0 *}
      Ann {* Not detected                     ND          0 *}
      Ann {* ----------------------------------------------- *}
      Ann {* total faults                              3278 *}
      Ann {* test coverage                           100.00% *}
      Ann {* ----------------------------------------------- *}
      Ann {*  *}
      Ann {*            Pattern Summary Report *}
      Ann {* ----------------------------------------------- *}
      Ann {* #internal patterns                         130 *}
      Ann {*     #basic_scan patterns                   130 *}
      Ann {* ----------------------------------------------- *}
      Ann {*  *}
      Ann {* rule  severity  #fails  description *}
      Ann {* ----  --------  ------  --------------------------------- *}
      Ann {* N21   warning        1  unsupported UDP entry *}
      Ann {* B8    warning        2  unconnected module input pin *}
      Ann {*  *}
      Ann {* clock_name        off  usage *}
      Ann {* ----------------  ---  -------------------------- *}
      Ann {* CK                 0   master shift  *}
      Ann {*  *}
      Ann {* There are no constraint ports *}
      Ann {* There are no equivalent pins *}
      Ann {* There are no net connections *}
      Ann {* top_module_name = s1423 *}
      Ann {* Unified STIL Flow *}
      Ann {* serial_flag = 1 *}
      Ann {* PSDF = NO_PSD_FILE *}
      Ann {* PSDS = 0 *}
      Ann {* PSDA = #130#1#0/0 *}
      Ann {* internal_clock = CK *}
   }
}
Signals {
   "GND" In; "VDD" In; "CK" In; "G0" In; "G1" In; "G10" In; "G11" In; "G12" In; "G13" In;
   "G14" In; "G15" In; "G16" In; "G2" In; "G3" In; "G4" In; "G5" In; "G6" In; "G7" In;
   "G8" In; "G9" In; "test_si" In { ScanIn; } "test_se" In; "G701BF" Out; "G702" Out;
   "G726" Out; "G727" Out; "G729" Out; "test_so" Out { ScanOut; }
}
SignalGroups {
   "_pi" = '"CK" + "G0" + "G1" + "G10" + "G11" + "G12" + "G13" + "G14" + "G15" + "G16"
   + "G2" + "G3" + "G4" + "G5" + "G6" + "G7" + "G8" + "G9" + "GND" + "VDD" + "test_si"
   + "test_se"'; // #signals=22
   "_in" = '"GND" + "VDD" + "CK" + "G0" + "G1" + "G10" + "G11" + "G12" + "G13" + "G14"
   + "G15" + "G16" + "G2" + "G3" + "G4" + "G5" + "G6" + "G7" + "G8" + "G9" + "test_si"
   + "test_se"'; // #signals=22
   "all_inputs" = '"CK" + "G0" + "G1" + "G10" + "G11" + "G12" + "G13" + "G14" + "G15"
   + "G16" + "G2" + "G3" + "G4" + "G5" + "G6" + "G7" + "G8" + "G9" + "GND" + "VDD"
   + "test_si" + "test_se"'; // #signals=22
   "_po" = '"G701BF" + "G702" + "G726" + "G727" + "G729" + "test_so"'; // #signals=6
   "_si" = '"test_si"' { ScanIn; } // #signals=1
   "all_outputs" = '"G701BF" + "G702" + "G726" + "G727" + "G729" + "test_so"'; // #signals=6
   "all_ports" = '"all_inputs" + "all_outputs"'; // #signals=28
   "_clk" = '"CK"'; // #signals=1
   "_so" = '"test_so"' { ScanOut; } // #signals=1
   "_out" = '"G701BF" + "G702" + "G726" + "G727" + "G729" + "test_so"'; // #signals=6
}
Timing {
   WaveformTable "_allclock_launch_capture_WFT_" {
      Period '100ns';
      Waveforms {
         "all_inputs" { 0 { '0ns' D; } }
         "all_inputs" { 1 { '0ns' U; } }
         "all_inputs" { Z { '0ns' Z; } }
         "all_inputs" { N { '0ns' N; } }
         "all_outputs" { X { '0ns' X; '40ns' X; } }
         "all_outputs" { H { '0ns' X; '40ns' H; } }
         "all_outputs" { L { '0ns' X; '40ns' L; } }
         "all_outputs" { T { '0ns' X; '40ns' T; } }
         "CK" { P { '0ns' D; '45ns' U; '55ns' D; } }
      }
   }
   WaveformTable "_multiclock_capture_WFT_" {
      Period '100ns';
      Waveforms {
         "all_inputs" { 0 { '0ns' D; } }
         "all_inputs" { 1 { '0ns' U; } }
         "all_inputs" { Z { '0ns' Z; } }
         "all_inputs" { N { '0ns' N; } }
         "all_outputs" { X { '0ns' X; '40ns' X; } }
         "all_outputs" { H { '0ns' X; '40ns' H; } }
         "all_outputs" { L { '0ns' X; '40ns' L; } }
         "all_outputs" { T { '0ns' X; '40ns' T; } }
         "CK" { P { '0ns' D; '45ns' U; '55ns' D; } }
      }
   }
   WaveformTable "_allclock_launch_WFT_" {
      Period '100ns';
      Waveforms {
         "all_inputs" { 0 { '0ns' D; } }
         "all_inputs" { 1 { '0ns' U; } }
         "all_inputs" { Z { '0ns' Z; } }
         "all_inputs" { N { '0ns' N; } }
         "all_outputs" { X { '0ns' X; '40ns' X; } }
         "all_outputs" { H { '0ns' X; '40ns' H; } }
         "all_outputs" { L { '0ns' X; '40ns' L; } }
         "all_outputs" { T { '0ns' X; '40ns' T; } }
         "CK" { P { '0ns' D; '45ns' U; '55ns' D; } }
      }
   }
   WaveformTable "_allclock_capture_WFT_" {
      Period '100ns';
      Waveforms {
         "all_inputs" { 0 { '0ns' D; } }
         "all_inputs" { 1 { '0ns' U; } }
         "all_inputs" { Z { '0ns' Z; } }
         "all_inputs" { N { '0ns' N; } }
         "all_outputs" { X { '0ns' X; '40ns' X; } }
         "all_outputs" { H { '0ns' X; '40ns' H; } }
         "all_outputs" { L { '0ns' X; '40ns' L; } }
         "all_outputs" { T { '0ns' X; '40ns' T; } }
         "CK" { P { '0ns' D; '45ns' U; '55ns' D; } }
      }
   }
   WaveformTable "_default_WFT_" {
      Period '100ns';
      Waveforms {
         "all_inputs" { 0 { '0ns' D; } }
         "all_inputs" { 1 { '0ns' U; } }
         "all_inputs" { Z { '0ns' Z; } }
         "all_inputs" { N { '0ns' N; } }
         "all_outputs" { X { '0ns' X; '40ns' X; } }
         "all_outputs" { H { '0ns' X; '40ns' H; } }
         "all_outputs" { L { '0ns' X; '40ns' L; } }
         "all_outputs" { T { '0ns' X; '40ns' T; } }
         "CK" { P { '0ns' D; '45ns' U; '55ns' D; } }
      }
   }
}
ScanStructures {
   ScanChain "1" {
      ScanLength 74;
      ScanIn "test_si";
      ScanOut "test_so";
      ScanInversion 0;
      ScanCellType  { CellIn "SD"; CellOut "Q"; }
      ScanCells { "s1423.DFF_0.Q_reg" ; "s1423.DFF_1.Q_reg" ; "s1423.DFF_2.Q_reg"
      ; "s1423.DFF_3.Q_reg" ; "s1423.DFF_4.Q_reg" ; "s1423.DFF_5.Q_reg" ; "s1423.DFF_6.Q_reg"
      ; "s1423.DFF_7.Q_reg" ; "s1423.DFF_8.Q_reg" ; "s1423.DFF_9.Q_reg" ; "s1423.DFF_10.Q_reg"
      ; "s1423.DFF_11.Q_reg" ; "s1423.DFF_12.Q_reg" ; "s1423.DFF_13.Q_reg" ; "s1423.DFF_14.Q_reg"
      ; "s1423.DFF_15.Q_reg" ; "s1423.DFF_16.Q_reg" ; "s1423.DFF_17.Q_reg" ; "s1423.DFF_18.Q_reg"
      ; "s1423.DFF_19.Q_reg" ; "s1423.DFF_20.Q_reg" ; "s1423.DFF_21.Q_reg" ; "s1423.DFF_22.Q_reg"
      ; "s1423.DFF_23.Q_reg" ; "s1423.DFF_24.Q_reg" ; "s1423.DFF_25.Q_reg" ; "s1423.DFF_26.Q_reg"
      ; "s1423.DFF_27.Q_reg" ; "s1423.DFF_28.Q_reg" ; "s1423.DFF_29.Q_reg" ; "s1423.DFF_30.Q_reg"
      ; "s1423.DFF_31.Q_reg" ; "s1423.DFF_32.Q_reg" ; "s1423.DFF_33.Q_reg" ; "s1423.DFF_34.Q_reg"
      ; "s1423.DFF_35.Q_reg" ; "s1423.DFF_36.Q_reg" ; "s1423.DFF_37.Q_reg" ; "s1423.DFF_38.Q_reg"
      ; "s1423.DFF_39.Q_reg" ; "s1423.DFF_40.Q_reg" ; "s1423.DFF_41.Q_reg" ; "s1423.DFF_42.Q_reg"
      ; "s1423.DFF_43.Q_reg" ; "s1423.DFF_44.Q_reg" ; "s1423.DFF_45.Q_reg" ; "s1423.DFF_46.Q_reg"
      ; "s1423.DFF_47.Q_reg" ; "s1423.DFF_48.Q_reg" ; "s1423.DFF_49.Q_reg" ; "s1423.DFF_50.Q_reg"
      ; "s1423.DFF_51.Q_reg" ; "s1423.DFF_52.Q_reg" ; "s1423.DFF_53.Q_reg" ; "s1423.DFF_54.Q_reg"
      ; "s1423.DFF_55.Q_reg" ; "s1423.DFF_56.Q_reg" ; "s1423.DFF_57.Q_reg" ; "s1423.DFF_58.Q_reg"
      ; "s1423.DFF_59.Q_reg" ; "s1423.DFF_60.Q_reg" ; "s1423.DFF_61.Q_reg" ; "s1423.DFF_62.Q_reg"
      ; "s1423.DFF_63.Q_reg" ; "s1423.DFF_64.Q_reg" ; "s1423.DFF_65.Q_reg" ; "s1423.DFF_66.Q_reg"
      ; "s1423.DFF_67.Q_reg" ; "s1423.DFF_68.Q_reg" ; "s1423.DFF_69.Q_reg" ; "s1423.DFF_70.Q_reg"
      ; "s1423.DFF_71.Q_reg" ; "s1423.DFF_72.Q_reg" ; "s1423.DFF_73.Q_reg" ; }
      ScanMasterClock "CK" ;
   }
}
PatternBurst "_burst_" {
   PatList { "_pattern_" {
   }
}}
PatternExec {
   PatternBurst "_burst_";
}
Procedures {
   "multiclock_capture" {
      W "_multiclock_capture_WFT_";
      C { "all_inputs"=0NNNNNNNNNNNNNNNNNNNNN; "all_outputs"=XXXXXX; }
      V { "_pi"=######################; "_po"=######; }
   }
   "allclock_capture" {
      W "_allclock_capture_WFT_";
      C { "all_inputs"=0NNNNNNNNNNNNNNNNNNNNN; "all_outputs"=XXXXXX; }
      V { "_pi"=######################; "_po"=######; }
   }
   "allclock_launch" {
      W "_allclock_launch_WFT_";
      C { "all_inputs"=0NNNNNNNNNNNNNNNNNNNNN; "all_outputs"=XXXXXX; }
      V { "_pi"=######################; "_po"=######; }
   }
   "allclock_launch_capture" {
      W "_allclock_launch_capture_WFT_";
      C { "all_inputs"=0NNNNNNNNNNNNNNNNNNNNN; "all_outputs"=XXXXXX; }
      V { "_pi"=######################; "_po"=######; }
   }
   "load_unload" {
      W "_default_WFT_";
      C { "all_inputs"=0NNNNNNNNNNNNNNNNNNNNN; "all_outputs"=XXXXXX; }
      "Internal_scan_pre_shift": V { "test_se"=1; }
      Shift {          W "_default_WFT_";
         V { "_clk"=P; "_si"=#; "_so"=#; }
      }
   }
}
MacroDefs {
   "test_setup" {
      W "_default_WFT_";
      C { "all_inputs"=NNNNNNNNNNNNNNNNNNNNNN; "all_outputs"=XXXXXX; }
      V { "CK"=0; }
      V { }
   }
}
Pattern "_pattern_" {
   W "_multiclock_capture_WFT_";
   "precondition all Signals": C { "_pi"=0000000000000000000000; "_po"=XXXXXX; }
   Macro "test_setup";
   Ann {* chain_test *}
   "pattern 0": Call "load_unload" { 
      "test_si"=00110011001100110011001100110011001100110011001100110011001100110011001100; }
   Call "multiclock_capture" { 
      "_pi"=0001011110111110001111; "_po"=LHHHLL; }
   "pattern 1": Call "load_unload" { 
      "test_so"=LLHHLLHHLLHHLLHHLLHHLLHHLLHHLLHHLLHHLLHHLLHHLLHHLLHHLLHHLLHHLLHHLLHHLLHHLL; 
      "test_si"=11011000011101101111100101010001000000101000110001011001111100101110111010; }
   Call "multiclock_capture" { 
      "_pi"=P100101011011111000100; "_po"=LHLHHH; }
   "pattern 2": Call "load_unload" { 
      "test_so"=LLLHHHLLLLHLLLLHHHHHHLLLHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL; 
      "test_si"=11011100110101101000111000001011110001000101111010011111000111001010101000; }
   Call "multiclock_capture" { 
      "_pi"=P111001001010001101110; "_po"=HLLLHH; }
   "pattern 3": Call "load_unload" { 
      "test_so"=LLLHHHLLLLLHLLHHLLLLLLLLHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL; 
      "test_si"=11010101100101100110000010111111010010011111101101010010110000000010011101; }
   Call "multiclock_capture" { 
      "_pi"=P110111010010110111010; "_po"=LLLLHH; }
   "pattern 4": Call "load_unload" { 
      "test_so"=LLLHHHLLLLHLLHHLHLLLLLLHHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHH; 
      "test_si"=11000111000101111011110111010110010100101011000000001001011110010111000110; }
   Call "multiclock_capture" { 
      "_pi"=P010000011110101010000; "_po"=LLLLHH; }
   "pattern 5": Call "load_unload" { 
      "test_so"=LLLHHHLLLLLLLHLHLLLLLLHHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL; 
      "test_si"=10001110001011110111101110101100101001010110000000010010111101000110001101; }
   Call "multiclock_capture" { 
      "_pi"=P001000101111010100010; "_po"=HLLLHH; }
   "pattern 6": Call "load_unload" { 
      "test_so"=LLLHHHHLLLHLHHHHLHHHHLHHHLHLHHLLHLHLLHLLLLHLLLLLLLLHLLHLLHHHHHLLLHLLLLHHLL; 
      "test_si"=01100000011001011000101111110001100010111000011000001001000111011011000111; }
   Call "multiclock_capture" { 
      "_pi"=P001111010000011011110; "_po"=LHHHLL; }
   "pattern 7": Call "load_unload" { 
      "test_so"=LLLHHHLLLLHHLHLHHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHH; 
      "test_si"=11100100110010110001011111100011000101110000111110010110001110110110001101; }
   Call "multiclock_capture" { 
      "_pi"=P100111101000001100110; "_po"=HLHLHH; }
   "pattern 8": Call "load_unload" { 
      "test_so"=LHLLLHLHLHLLHLHHLLLHLHHHHHHLLLHHLLLHLHHHLHLHLHHHHLLHHLLHHLHLLLHHLHLLLLHHLH; 
      "test_si"=10100101101011010101001101101110111011110101111010001000100011111011000010; }
   Call "multiclock_capture" { 
      "_pi"=P111000101011110111110; "_po"=HLHLHH; }
   "pattern 9": Call "load_unload" { 
      "test_so"=LLLHHHLHHLHLHHLHLHLHLLHHLHHLHHHLHHHLHHHLLLHLLHLHLLLLHLLLLLHHLHHHHLLHLLLLHL; 
      "test_si"=01011011010110101010011011011101110111101011110000010001000111110110000101; }
   Call "multiclock_capture" { 
      "_pi"=P111100000101111011110; "_po"=HHLHLL; }
   "pattern 10": Call "load_unload" { 
      "test_so"=LLLHHHLLLLHHLHLHHLLLLLHHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLH; 
      "test_si"=10100010101101010100110110111011101110010111100000100010001111101100001011; }
   Call "multiclock_capture" { 
      "_pi"=P111110100010111101110; "_po"=HHHLHH; }
   "pattern 11": Call "load_unload" { 
      "test_so"=LLHHHHLHHLHHHHLHLHLHLLLHHHLLLLHHHHLLHLHLLLLLLLLLHLLLLLLHHLHLLHHHLLHLLHLHHL; 
      "test_si"=00000001010100011110011111011111110110111011011001101000100001001111001010; }
   Call "multiclock_capture" { 
      "_pi"=P110100110110101111010; "_po"=LHLLLL; }
   "pattern 12": Call "load_unload" { 
      "test_so"=LHLHHHHLHLLHLLLHHLLLLLHHHHHLLHHHHHHLHHLHHHLLLHLLLLLLLLLLLLHHHHLLHHLHLLHLLL; 
      "test_si"=01101110100110001011001100010111101101100010101011111101111100001001001000; }
   Call "multiclock_capture" { 
      "_pi"=P010001001100100110000; "_po"=HLHLLL; }
   "pattern 13": Call "load_unload" { 
      "test_so"=LLLHHHLLLLLLLHHLLLLLLLHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL; 
      "test_si"=11011101001100010110011000101111111011000101010111111011111000010010010001; }
   Call "multiclock_capture" { 
      "_pi"=P001000010110010011010; "_po"=LLLLHH; }
   "pattern 14": Call "load_unload" { 
      "test_so"=LLLHHHLLLLLHLHLLHLLLLLLLHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHH; 
      "test_si"=11010010010110011011010011110110000110011110110111011011001110110011111111; }
   Call "multiclock_capture" { 
      "_pi"=P001111101100111010000; "_po"=HHLLHH; }
   "pattern 15": Call "load_unload" { 
      "test_so"=LLHLLHLLLHLHLLLHHLLLLLLLHHHHHHHLHLHLHLLHHHLLLLHHHLLLLLHHLLHLLLHHLLHHHHHLHH; 
      "test_si"=10101000101100010011110111101100001100111101101110110110011101100111111111; }
   Call "multiclock_capture" { 
      "_pi"=P000111110110011100000; "_po"=LHHLHH; }
   "pattern 16": Call "load_unload" { 
      "test_so"=LHLLLLLHHHHHHLLHLHLLLLLHHHHHLHLLLLHHLHLLLLLHHHHHHLLLLLLHHHHLHHHLLHLHHHHLHH; 
      "test_si"=00110001010111011011111101110000101001101111000101000000000101011000100011; }
   Call "multiclock_capture" { 
      "_pi"=P001000001100111111110; "_po"=HHHHLL; }
   "pattern 17": Call "load_unload" { 
      "test_so"=LLLHHHLLLLLHLHHHHLLLLLHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHH; 
      "test_si"=00001010000000000000100100100110001100101001001010110011010000011001101110; }
   Call "multiclock_capture" { 
      "_pi"=P101011111100001010010; "_po"=LHLLLL; }
   "pattern 18": Call "load_unload" { 
      "test_so"=LLHLLLHLLHLLLLLLLLLLLLLHLLHLHHHLLLHHLHLLHHLHLLHLHLLLLLHLHHLLHLLHHHHHHLHLLL; 
      "test_si"=00110100000000000001001001001100011001010010010101100110100100110011011101; }
   Call "multiclock_capture" { 
      "_pi"=P010001111110001100010; "_po"=LLHLLL; }
   "pattern 19": Call "load_unload" { 
      "test_so"=LLLLLLLLLHLLLLLLLLLHLLHLLHLLHHLLLLLLLHLHLLLLLLHLLHHLLHHLHLLLHLHHLLHHLHHHHH; 
      "test_si"=01101100001110000010010010011100110010100100101011001101011001100110111011; }
   Call "multiclock_capture" { 
      "_pi"=P001010111111000111000; "_po"=LLHLLL; }
   "pattern 20": Call "load_unload" { 
      "test_so"=HHLHHHLLLLHHHLLLLLHLLHLLHLLHHHLLHHLLHLHLHLLLHLHLHHLLHHLLHHHLHHHLLHLLHHHLHH; 
      "test_si"=10101000001101011010110110011001010101011101001110110110101101011010101010; }
   Call "multiclock_capture" { 
      "_pi"=P001110101000010001000; "_po"=HHHHHH; }
   "pattern 21": Call "load_unload" { 
      "test_so"=LHLHHHLLHLHHLLLLHLHLHHLHHLLLLLHLLHLHHLLLLLLHLHHHHLHHLHHLLLHHHHLHHLLLHHLHHL; 
      "test_si"=01010100101000010001001110011100000101001000010011000011110111010011011011; }
   Call "multiclock_capture" { 
      "_pi"=P001101100110001100110; "_po"=HLLLLL; }
   "pattern 22": Call "load_unload" { 
      "test_so"=LHLLLLLHLHHLLLLHLLLHLLHHHLLHHHLLHLLHLHLLHLLLHLLHLHLLLLHHHHLLLHLHLLHHLHHLHH; 
      "test_si"=10001101010000101010011100111000001010010000100100111111101110100110011110; }
   Call "multiclock_capture" { 
      "_pi"=P100110110010000110000; "_po"=LLLLHH; }
   "pattern 23": Call "load_unload" { 
      "test_so"=LHLHHHHLHLLLLLHLHLHLLHHHLLHHHLLLLLHLHLLHLHLLHLLHLLHHHHHHLLHHLLHLLHLLLHHHLL; 
      "test_si"=01101010101111100011001011011000100100110101010010010001100010111101100000; }
   Call "multiclock_capture" { 
      "_pi"=0011000101110010011100; "_po"=HLHLLL; }
   "pattern 24": Call "load_unload" { 
      "test_so"=LHHLHLHLHLHHHHHLLLHHLLHLHHLHHLLLHLLHLLHHLHLHLHLLHLLHLLLHHLLLHLHHHHLHHLLLLL; 
      "test_si"=11111001011111000110010110110001001001101010100100000111000110110111000000; }
   Call "multiclock_capture" { 
      "_pi"=P101100110101001001110; "_po"=LHHLHH; }
   "pattern 25": Call "load_unload" { 
      "test_so"=HHHHHHHLLLHHHHLLLHHLLHLHHLHHHLLHHLHLLHHLHLHLHLLHLLLLLLHHLLLHLLHHLHHHLLHHLL; 
      "test_si"=10010110110000111011011111001010100011000001010001100010110011111011011101; }
   Call "multiclock_capture" { 
      "_pi"=P111101111100010101010; "_po"=LLLLHH; }
   "pattern 26": Call "load_unload" { 
      "test_so"=LLLLHHLHHHLLLLHHHLHHLHHHHHLLHLHLHLLLHHLLLLLHHLLLLHHLLLHLHHHHLHHHHLHHLHHHHH; 
      "test_si"=00101101101111110110111110010101000110000010100011000101110101110010111011; }
   Call "multiclock_capture" { 
      "_pi"=P011110111110001010100; "_po"=LLHLLL; }
   "pattern 27": Call "load_unload" { 
      "test_so"=HHLHHHHHHLHHHHHHLHHLHHHHHLLHLHLHHLLHHLLLLHHLHLLLHHLLLHLHLHLHHHHHLLLLLLLHHH; 
      "test_si"=01011011000011101101111000101010001100000101000110001011001111100101110111; }
   Call "multiclock_capture" { 
      "_pi"=P111111111111000100010; "_po"=LHLLLL; }
   "pattern 28": Call "load_unload" { 
      "test_so"=LLLLLLHLLHLLHHHLHHLHHHHLLLHHLLHLLLHHLLLLLHLHLLLHHLLLHLHHLLHHLHHLLHLHHHLHHH; 
      "test_si"=10100110000111011011111001010100011000001010001100010110011110100001101110; }
   Call "multiclock_capture" { 
      "_pi"=P010111101111100011000; "_po"=HLHLHH; }
   "pattern 29": Call "load_unload" { 
      "test_so"=HLLLLLLLHHLHHHLHHLHHHHHLLHLHLHLLHLLLLLLLHHLLLHHLHLLHLHLHHHHLLLHLLHHHHLHLHL; 
      "test_si"=11100111001101011010111011000001011010000101111101110001001100101110010010; }
   Call "multiclock_capture" { 
      "_pi"=P010001111001011101010; "_po"=LLHLHH; }
   "pattern 30": Call "load_unload" { 
      "test_so"=LHHLLLHHLHHHLHLHHLHLHHHLHHLLLLLHLHHLHLHLHLHLLHHLLHHHLLLLHLHLHLHLHHLLLHLLLL; 
      "test_si"=11000110011100011001110110001010110000001011111011100010011001010100100101; }
   Call "multiclock_capture" { 
      "_pi"=P001000111100101110100; "_po"=LLLLHH; }
   "pattern 31": Call "load_unload" { 
      "test_so"=LHLHHHHLLLHHLLLHHLLHHHLHHLLLHLHLHHLHLLHLHHLLLHLHLHHLLLLHHLLHHHLHHLHLHLLHHH; 
      "test_si"=01101111110110111111010111010000111000010010001010110100011110010111011001; }
   Call "multiclock_capture" { 
      "_pi"=P110101100111001010000; "_po"=HLHLLL; }
   "pattern 32": Call "load_unload" { 
      "test_so"=HLLLHHHHLHLHHLHHHHHHLHLHHHLHLLLLHHHLLLLHLHHLLLHLHLHHLHHHHHHHLLLHLHLLHLLHLH; 
      "test_si"=00111100100011110010010101100100101000100001111110111110110000000000100001; }
   Call "multiclock_capture" { 
      "_pi"=P001011101010111000000; "_po"=HLHLLL; }
   "pattern 33": Call "load_unload" { 
      "test_so"=LLLLLLLLHHLLHHHHLLHLLHLHLHHLLHLLHLHLLLHLLLLHHHHHHHLLLLHLHHLLHLLLLLLLHLLLLH; 
      "test_si"=10001010001001001001000000001100001001000110101101000100101100101111010001; }
   Call "multiclock_capture" { 
      "_pi"=P010100011100000000010; "_po"=LHLHHH; }
   "pattern 34": Call "load_unload" { 
      "test_so"=LLLHHHLLLLHLHLLLLLLHLHHHLLLLLLLLLLLLLLLLLLLLLLLLLHLLLHLLLLLLLLLLLLLLLLLLHH; 
      "test_si"=00110100010011010000100000011000010010001101011010001001011001011110100011; }
   Call "multiclock_capture" { 
      "_pi"=P000011101110000001000; "_po"=HLHLLL; }
   "pattern 35": Call "load_unload" { 
      "test_so"=LLLHLHLLLHLLHHLHLLLLHLLLLLLHHLLLHHLLHLHLHHLHHHLHHLLLHLLHLLLHHHLHHHHLHLLLHH; 
      "test_si"=10001111101100010000101011110100111100011111001000001011111110010011010101; }
   Call "multiclock_capture" { 
      "_pi"=P010100111010011100110; "_po"=LLLLHH; }
   "pattern 36": Call "load_unload" { 
      "test_so"=LLLHHHHHHLHHLLLHLLLLHLHLHHHHLHLLHHHHLLLLLLHHLHLLLLLLHLHHLHHHLLLHLLLHLHLLHH; 
      "test_si"=00010111010100011000110111101110111000111110010010000111111100100110101011; }
   Call "multiclock_capture" { 
      "_pi"=P101010111011001110000; "_po"=LLLLLL; }
   "pattern 37": Call "load_unload" { 
      "test_so"=LLHHHHHHLLLHLLLHHLLLHHLHHHHLHHHLHLLLLLHHHHLLLLLHHLLLLHHHHHHLHLHLLHHLHHLHHH; 
      "test_si"=11011001101100111011010100010010101001111001011010001110110100100011000101; }
   Call "multiclock_capture" { 
      "_pi"=P000100110110001010000; "_po"=LHLHHH; }
   "pattern 38": Call "load_unload" { 
      "test_so"=LHHHHHHHLLHLLHLHLLLLLLLHLLLLLHHHHLHLLHHHHLLHLHHLHLLLLLHLHHLHHLHLLLHHLLLLHH; 
      "test_si"=10010111011001011010111000100001010001110010110111111101101011000110001011; }
   Call "multiclock_capture" { 
      "_pi"=P000010111011011101010; "_po"=LLLLHH; }
   "pattern 39": Call "load_unload" { 
      "test_so"=LLLHHHHHLLHLLHLHHLLLLLLLLLLLLLHLLHLHLHHHLLLLLLHHHLLLLLLHHHLHLHLLLHHLLLHLHH; 
      "test_si"=00110110110111101101010001001011100111100101101111111011010110001100010110; }
   Call "multiclock_capture" { 
      "_pi"=P000001101101101110100; "_po"=HLHLLL; }
   "pattern 40": Call "load_unload" { 
      "test_so"=LLLHLHHLHHLHHHHLHHLHLHLLLHLLHLHHHLLHHHHLLHHLLHHHLHHHHLHHLHLLLLLLHHLLLHLHHL; 
      "test_si"=10001010101001011000111001010000010111001110100010000111100000110110111111; }
   Call "multiclock_capture" { 
      "_pi"=P110001011111101000000; "_po"=LHLHHH; }
   "pattern 41": Call "load_unload" { 
      "test_so"=LLLHHHLLLLLLHLLHLLLHLLHHHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHH; 
      "test_si"=11101010011100001000011001100101110110011000111001111110001101000011101101; }
   Call "multiclock_capture" { 
      "_pi"=P001001010110101001000; "_po"=LHHHHH; }
   "pattern 42": Call "load_unload" { 
      "test_so"=LLLHHHLLLLLHLLLHLLLLLHHLHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHH; 
      "test_si"=11101000111001011010010011001011101100110001110011111100011010000111011011; }
   Call "multiclock_capture" { 
      "_pi"=P000100101011010100100; "_po"=HHHLHH; }
   "pattern 43": Call "load_unload" { 
      "test_so"=LHHHHHLHLLHLHHLHHLHLHLLLHHLHLLHHHLHHLHLHLHLHHHLLHHHHHHHHHHHLLLLLLHLHLHHLHH; 
      "test_si"=00110101111000011000111010100100000011001100100010010011110001000001001001; }
   Call "multiclock_capture" { 
      "_pi"=P011001100110011011010; "_po"=HLHLLL; }
   "pattern 44": Call "load_unload" { 
      "test_so"=LLLLHHLHHHHLLLLHHLLLHHHLHLHLLHLLHLLLHHLLHHLHLLLHLLLHLLHHHHHHHHLLLLLHLLHLLH; 
      "test_si"=10011000111110111101001110001101011110011100010101000110101110101111011001; }
   Call "multiclock_capture" { 
      "_pi"=P011101100011010000100; "_po"=HHLLHH; }
   "pattern 45": Call "load_unload" { 
      "test_so"=HHHHLHLHHHHHHLHHHHLHLLHHHLLHLHLHHHHHHLLHHHLLLHLHLHLLLHHLHLHHLLHLHHHHLHHLLH; 
      "test_si"=11110110110111110010100111011110100100111101010110101000010001110110010000; }
   Call "multiclock_capture" { 
      "_pi"=P111111111000010101010; "_po"=LLHLHH; }
   "pattern 46": Call "load_unload" { 
      "test_so"=HLLLHHLHLHLHHHHHLLHLHLLHHHLHHHHLHLLHLLHHHHLHHLHHHLHLHLLLLHHHHHHHLHHLLHHHLL; 
      "test_si"=11001011001111011010011101111110010011110101011100001001000111011001000011; }
   Call "multiclock_capture" { 
      "_pi"=P101111110111000100010; "_po"=LHLLHH; }
   "pattern 47": Call "load_unload" { 
      "test_so"=HLLLLLHLLHHHHHLHHLHLHLHHLLLLLHHLHHLLLLLLLLLHHHHLHLLLHLLLHLLHLHLHHHHHLLHHHH; 
      "test_si"=00101001011101101001110111111001000111010101110111000110111101100100101101; }
   Call "multiclock_capture" { 
      "_pi"=0001011111101100000010; "_po"=LHHLLL; }
   "pattern 48": Call "load_unload" { 
      "test_so"=LLHLHLLHLHHHLHHLHLLHHHLHHHHHHLLHLLLHHHLHLHLHHHLHHHLLLHHLHHHHLHHLLHLLHLHHLH; 
      "test_si"=10111010010101011111010100110111000110101110010010111001110111100111011000; }
   Call "multiclock_capture" { 
      "_pi"=0010100000110101101010; "_po"=HLHHHH; }
   "pattern 49": Call "load_unload" { 
      "test_so"=HLHHHLHLLHLHLHLHHHHHLHLHLLHHLHHHLLLHHLHLHHHLLHLLHLHHHLLHHHLHHHHLLHHHLHHLLL; 
      "test_si"=10010010100100110010010010101011010101011001011010000010100010111100100010; }
   Call "multiclock_capture" { 
      "_pi"=P011011111011101010110; "_po"=LHLLHH; }
   "pattern 50": Call "load_unload" { 
      "test_so"=LLLLLLHLHHLHLLHHLLLLLLLLHLHHLLHHHHLHLHLHHLLHHHLHHLLLLLHLHLHHLLHHHHLLHLHHLL; 
      "test_si"=11011111010100101010110010001010010011011001011010101101100010000111001010; }
   Call "multiclock_capture" { 
      "_pi"=P111110111000011110010; "_po"=LLLLHH; }
   "pattern 51": Call "load_unload" { 
      "test_so"=LLHHHHHLLLHHLHHHHLLLLLLHHLLLLHHLLHLLHHLHHLLHLHHLHLLLLLLHHLLLLLLLLHHHLHLHLL; 
      "test_si"=00011100011101011010110111011100101011000000101110001110011001100101110010; }
   Call "multiclock_capture" { 
      "_pi"=P001111101011101101010; "_po"=HLLLLL; }
   "pattern 52": Call "load_unload" { 
      "test_so"=LHHHHHLLHHHHLHLHHLHLHHLHHHLHHHLLHLHLHHLLLLLLHLHHHLLLHHHLLHHLHHHLLHLHHHHHHL; 
      "test_si"=00101000110011100011001110110001010110000001011111011100010010110101100100; }
   Call "multiclock_capture" { 
      "_pi"=P000111100101110110100; "_po"=HHHLLL; }
   "pattern 53": Call "load_unload" { 
      "test_so"=LHHLHLLHHHLLLHHLLLLLLLHHHLHHHLLHHHLHHLHLLHLHLHHHHHHLLLHHHHLLLLHHHLHHHLLHLH; 
      "test_si"=01101101100101011010111000111010111111000010111110111000100110010111001001; }
   Call "multiclock_capture" { 
      "_pi"=P100011111010111010010; "_po"=LLHLLL; }
   "pattern 54": Call "load_unload" { 
      "test_so"=LHHLLLLHHHLHLHLHHLHLHHHLLHLLLLHLHLLLLLLLLHLLLHHHHLHHHLLLLLLHLLLHLHLHLLHLHH; 
      "test_si"=00010111111011011010111101001011011110101100111001010101010100100010110101; }
   Call "multiclock_capture" { 
      "_pi"=P011110111101011110010; "_po"=LLLLLL; }
   "pattern 55": Call "load_unload" { 
      "test_so"=HLLHHHHHHLHLHHLHHLHLHHHHLHLLHLHHHHHHHLHLHHLHLHLLHHLHLHLHLHLLHLHLLLHLHHLHHH; 
      "test_si"=00101111110101010010111010010110111101011001110010101010101001111101101011; }
   Call "multiclock_capture" { 
      "_pi"=P001111101010101111010; "_po"=HLHLLL; }
   "pattern 56": Call "load_unload" { 
      "test_so"=LLHHHHHHHHLHLHLHLLHLHHHLHLLHLHHLHHHHLHLHHHLHHHLLHLHLHLHLLLHLHLLLLLHHHHLHHH; 
      "test_si"=01001100010000001100101101100110100100011111011110000000000110101001100000; }
   Call "multiclock_capture" { 
      "_pi"=P011001100000001001100; "_po"=HLLLLL; }
   "pattern 57": Call "load_unload" { 
      "test_so"=LHHHHHLLLHLLLLLLHHLLHLHHLHHLLHHLHLLHLLLLLLHHLHHHLLLLLHHHHLLHLLHLHHHHHLHHLH; 
      "test_si"=10000011011010010001111110000110010110010010000001010101011001110001110001; }
   Call "multiclock_capture" { 
      "_pi"=P110010101101011000110; "_po"=HHLLHH; }
   "pattern 58": Call "load_unload" { 
      "test_so"=LLLHHHHHLLHLHLLHLLHLLLHHHLLLHHHLLHHLHLHHLHLLLLLLHLLLLLLLHLLHHHHHLHHHHHLLLL; 
      "test_si"=00011101001100011000110001000110110010001000111010001011110111000001010110; }
   Call "multiclock_capture" { 
      "_pi"=P100111100011110010000; "_po"=HLLLLL; }
   "pattern 59": Call "load_unload" { 
      "test_so"=LHHLLLHLHHHLLHLLHLLLLLHHHLLLLHHHHHLLHLLLHLLLHHHLHLLLLLHHHHLHLHLLLLLHLHLLHL; 
      "test_si"=00110110011111011010110010001110100100010001110110011111011110000010101100; }
   Call "multiclock_capture" { 
      "_pi"=P010011100001111001010; "_po"=HLHLLL; }
   "pattern 60": Call "load_unload" { 
      "test_so"=HLLHLHHLLHHHLHLHHLLLLLHHLLLLLHHHHLLHLLLHLLHLLLHHHLLLLLHHLHHLLLLLLLHLHLHLLL; 
      "test_si"=01110011000110001101011001010100010110001111010110000111001000100111101101; }
   Call "multiclock_capture" { 
      "_pi"=P000111100111000010110; "_po"=HHHLLL; }
   "pattern 61": Call "load_unload" { 
      "test_so"=LLHLLLHLLHLHLLLLHLLLLLHLLHLHHHLLHHHLHLLLHHLLLLHHHLLLLHHHLHLHHLHLLHHHHLHLLH; 
      "test_si"=11101110001101011010110010101000101110011110101101010110010001001111011010; }
   Call "multiclock_capture" { 
      "_pi"=P101011111010110001010; "_po"=LLHLHH; }
   "pattern 62": Call "load_unload" { 
      "test_so"=LHLLLLHLLHHHLHLHHLHLHHLLHLHLHLLLHLHHHLHLLLHLHHHLHHLHLHLHHHHHHHLLHHLHLHHLLL; 
      "test_si"=11011011100110011100111000011011000110010001100011111001110110111100000000; }
   Call "multiclock_capture" { 
      "_pi"=P001011101100000110110; "_po"=HHLLHH; }
   "pattern 63": Call "load_unload" { 
      "test_so"=HHLLLLHHHHLHLLLHHLLLLLHLLLHLLLHHHLLHHLLHLLLHHLLLHHHHHLLHHHLHLLHHHHLLLLLLLL; 
      "test_si"=10100011000100000100000000110100001100100011000111110011101101111000000000; }
   Call "multiclock_capture" { 
      "_pi"=P100101110110000001010; "_po"=LHHLHH; }
   "pattern 64": Call "load_unload" { 
      "test_so"=LLLLLLHLHHLHLLLLLHLLLLLLLLHHHHLLLHLLLHLLLHLLLLHHLHHHLLHHLLHLHHHHHHHLLLLLLL; 
      "test_si"=01101010001000010000100001101000011001000110001111100111011011110000000001; }
   Call "multiclock_capture" { 
      "_pi"=P010010111011000001110; "_po"=LHHLLL; }
   "pattern 65": Call "load_unload" { 
      "test_so"=LHLHHHHLLLHLLLLHLLLLHLLLLHHHLLLLHHHLHLLLHLHLLLHHHHHLLHHLHHHLLHHHLHHLLLLLHH; 
      "test_si"=11001011101001111011111110011011101100100000100110011011100011000010110110; }
   Call "multiclock_capture" { 
      "_pi"=P110111001000111100110; "_po"=HHLHHH; }
   "pattern 66": Call "load_unload" { 
      "test_so"=LLLHHHLLLLHLLLHHHLHHHHHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHL; 
      "test_si"=10000000101001010010100001111100000111101101110101100010010010100111011001; }
   Call "multiclock_capture" { 
      "_pi"=P100101110001000001000; "_po"=LHLLHH; }
   "pattern 67": Call "load_unload" { 
      "test_so"=LHLLLLLHHHHLLHLHLLHLHLLLLLLLLHLLHLLHLLLHLLHLLLHLLHHLLLLHHHHHLLHLLHLHLHHLHH; 
      "test_si"=00000001010001101011000011111000001111011011111111000100100101001110110010; }
   Call "multiclock_capture" { 
      "_pi"=P010010111000100001100; "_po"=LHLLLL; }
   "pattern 68": Call "load_unload" { 
      "test_so"=LLHHHHLHLLLLHHHLHLHHLHLLHLLLLLLLLHLLLLLHHHLLLHHHHHLLHLLLLLLLHHLLHHLLHHHHLL; 
      "test_si"=00010001011001111111011010111011000000011011101111001100011110111101011001; }
   Call "multiclock_capture" { 
      "_pi"=P110111101000001111110; "_po"=HLLLLL; }
   "pattern 69": Call "load_unload" { 
      "test_so"=LHHHLLHLHHHLLHHHHLLLLLHLHHLLLLHHHLLHLLHHHHLLLHHHHLLLLLHHHHHLLHLLLLHLHLLHLH; 
      "test_si"=00101010110011111110110101110110000000110111011110001100111101111110100111; }
   Call "multiclock_capture" { 
      "_pi"=P101011100111100110110; "_po"=HHHLLL; }
   "pattern 70": Call "load_unload" { 
      "test_so"=LLLHLHHLHHLLLHHHHLLLLLLHLHHHHHHLLLLLLHLLLLHHLHHHHLLLHHLLLHHHHHHHHHLLHLLHHH; 
      "test_si"=01000110011101010010100110100110011111000010000100101100101111011111110110; }
   Call "multiclock_capture" { 
      "_pi"=P100011100011001100000; "_po"=HLLLLL; }
   "pattern 71": Call "load_unload" { 
      "test_so"=LHLLLHHLLHHHLHLHLLHLHLLHHLHLLHHLLLLLHHLLLHLLLLHLHLHLHHLLLLHLLHLHHHLHHHLHHL; 
      "test_si"=10010111000100000010100000000100100000101000110000100100001010011101010001; }
   Call "multiclock_capture" { 
      "_pi"=P001111100010111001010; "_po"=HLLLHH; }
   "pattern 72": Call "load_unload" { 
      "test_so"=LLHLLLHLHHLHHLLLLLHLHHLLLLLLLHLLHLLLLLHLHLLHLLLLHLHLLHLLLHLHLLLHHHLHLHHHLH; 
      "test_si"=00100010000000000001100000001011000001010001100000001100010100111010100011; }
   Call "multiclock_capture" { 
      "_pi"=P000111110111011101100; "_po"=LHHLLL; }
   "pattern 73": Call "load_unload" { 
      "test_so"=LLLLLLLLHHLLHLLLLLLHHHLLLLLHLLHHLLLLHLLHLHHLLLLLHLLLLLHHHHLLHLHHHLLLHLHHHH; 
      "test_si"=01011000000000000011000000010110000010100011000000110000101001111101011011; }
   Call "multiclock_capture" { 
      "_pi"=P100011111000101101100; "_po"=LHLLLL; }
   "pattern 74": Call "load_unload" { 
      "test_so"=LHHLLLLLLHLLHLLLLLHHLHLLLLLHHHHLLLLLHLHLLLHHLLLLLLLLLLLLHLHLHLLLLLHLHLLHHH; 
      "test_si"=10010010000000000110000000101100011101000110000011100001010011101010101110; }
   Call "multiclock_capture" { 
      "_pi"=0110001111100110111110; "_po"=LLLLHH; }
   "pattern 75": Call "load_unload" { 
      "test_so"=HLLHLLHLLLLLLLLLLHHLLLLLLLHLHHLLLHHHLHLLLHHLLLLLHHHLLLLHLHLLHHHLHLHLHLHHHL; 
      "test_si"=00111010000000001100000001011000011011001110000111000010100111010100111100; }
   Call "multiclock_capture" { 
      "_pi"=0111000111110011011111; "_po"=LHHLLL; }
   "pattern 76": Call "load_unload" { 
      "test_so"=LLHHHLHLLLLLLLLLHHLLLLLLLHLHHLLLLHHLHHLLHHHLLLLHHHLLLLHLHLLHHHLHLHLLHHHHLL; 
      "test_si"=01100011011010110001011111111011000010110100110111010000011010111100101100; }
   Call "multiclock_capture" { 
      "_pi"=0100010001010010010100; "_po"=HHHHLL; }
   "pattern 77": Call "load_unload" { 
      "test_so"=LHHLLLHHLHHLHLHHLLLHLHHHHHHHHLHHLLLLHLHHLHLLHHLHHHLHLLLLLHHLHLHHHHLLHLHHLL; 
      "test_si"=11111000001111001011100010111101001011000101010110011101100000110110101101; }
   Call "multiclock_capture" { 
      "_pi"=P111111110011010111000; "_po"=LHHLHH; }
   "pattern 78": Call "load_unload" { 
      "test_so"=HHLLLLLLLHHHLHLLHLLLLLLLHHLLLHLHHLHLHHLLLHLHLHLHHLLHHHLHHLLLHLHHLHHLHLHHHH; 
      "test_si"=11011011001001111100110001100010010001001100101101011100101010111101011001; }
   Call "multiclock_capture" { 
      "_pi"=P100100111110101011100; "_po"=LHLLHH; }
   "pattern 79": Call "load_unload" { 
      "test_so"=LLLHHHHLLLHLLHHHHLLLLLLLLHHLHLHLHHLLLHLLHHLLHLHHLLLLLLLLHLHLLLHHHHLHLHHLHH; 
      "test_si"=10011001101001010000111110001111111100110101100010101100000000011111011011; }
   Call "multiclock_capture" { 
      "_pi"=P101100101011001011100; "_po"=HHLLHH; }
   "pattern 80": Call "load_unload" { 
      "test_so"=LHLHHHHHHLHLLHLHLLLLLLHHHLLHLHHHHHHHLLHHLHLHHLLLHLLLLLLLLLLLHLLHHHHHLHHLHH; 
      "test_si"=00000011010010100001111100011111111001101111000101011000000000111000011111; }
   Call "multiclock_capture" { 
      "_pi"=P110110100101000101110; "_po"=HLLLLL; }
   "pattern 81": Call "load_unload" { 
      "test_so"=LLLHHHHLHLLLHLHLLLHLLLHHLLHLLHHHHLLLHLLHLLLLLLHLHHLHHLHHHLHHHLHHHHHLLHHHHH; 
      "test_si"=01100010111111010101001011101001011011110101100111001010101010011100010110; }
   Call "multiclock_capture" { 
      "_pi"=P110010101011111111100; "_po"=HHHLLL; }
   "pattern 82": Call "load_unload" { 
      "test_so"=HHHHHHHLHLHHLHLHLLLLLLHLHHHHLLLHHHHLLLLLLLHLLLHHHLLLLLHLLHLHLLHLLLHLLHLHHL; 
      "test_si"=10001111111101011010111011111001100111010110011100101010101010010001011010; }
   Call "multiclock_capture" { 
      "_pi"=P111100101010111110010; "_po"=HLLLHH; }
   "pattern 83": Call "load_unload" { 
      "test_so"=LLLHHHHHHLHHLHLHHLHLHHHLHHHHHLLHHLHLLLLLLLLLLHHLLLHLHLHLLLHLLLLHLHHLHLLHHL; 
      "test_si"=01110110001001011010111110111001011010001101111001111000100100001001000111; }
   Call "multiclock_capture" { 
      "_pi"=P001000100001010111100; "_po"=HLHLLL; }
   "pattern 84": Call "load_unload" { 
      "test_so"=LHLHHHHLLLHLLHLHHLLLLLLLLLLLLLHLLHHLHLLLHHHLLHLLLLLLLLLLHLLLHLLLHLLHLLLHHH; 
      "test_si"=11111000010110010010111101110010110000011011110010110001001000010010011010; }
   Call "multiclock_capture" { 
      "_pi"=P100100110100101010110; "_po"=LHHLHH; }
   "pattern 85": Call "load_unload" { 
      "test_so"=LHLHHHLLLLLHLLLHLLLLLLHHLHHHHLHLHHLLLLLHHLHHHHLLHLLLLLLHLLHLHLLHLLHHHLLHLL; 
      "test_si"=10000110100111101100100101001100111000111010011110001110110100101101011001; }
   Call "multiclock_capture" { 
      "_pi"=P111010100011000011110; "_po"=HLLLHH; }
   "pattern 86": Call "load_unload" { 
      "test_so"=HLLHHHHLHLLHHHHLHHLLHLLHLHLLHHLLHLLLLLHHHHLLLHHHHLLHLLHLLHLLHLHHLLHLHLLHLH; 
      "test_si"=01110111000111011010110100000000101001111001000101001101001101010011110000; }
   Call "multiclock_capture" { 
      "_pi"=P110101111000110111010; "_po"=LLHLLL; }
   "pattern 87": Call "load_unload" { 
      "test_so"=LLLLLLHLLHLHLHLHHLHLHHLHLLLLLLLLHLHLLHHHHLLHHLHLLHLLHHLHLLHLHHLHLLHHHHLLLL; 
      "test_si"=10011000000011101001110110111000001011111111110010001110111110101110100110; }
   Call "multiclock_capture" { 
      "_pi"=P000010110111001100010; "_po"=LHLLHH; }
   "pattern 88": Call "load_unload" { 
      "test_so"=LLLHHHLLLLLLHHHLHLLHHHLHHHLLLLLLHLHLHHHHHHHHHHLLHLLLLLHLHHHHLLHLHHHLHLLLLL; 
      "test_si"=00110000000111010011101101110000010111111111100110001001111100011101001101; }
   Call "multiclock_capture" { 
      "_pi"=P001001101111000110000; "_po"=HHHLLL; }
   "pattern 89": Call "load_unload" { 
      "test_so"=HLHLLLLLLHLHLHLHLLLLLLHHLHHHHLLLHHHLHHHHHHLLLLHHLLLLHLLHHHHLHLLHHHLHLLHLLH; 
      "test_si"=00011110000101001111010101011000110111110010110110110011011110110011011100; }
   Call "multiclock_capture" { 
      "_pi"=P001100101100000101110; "_po"=HLLLLL; }
   "pattern 90": Call "load_unload" { 
      "test_so"=LLLHHHLLHLLHLHLLHHHHLHLHLHLHHLLLHHLHHHHHLLHLHHLHHLHHLLHHLHHHLLHHLLHHLHHLLL; 
      "test_si"=00110100001101011010111010110010101101100101101110000110111101100110111000; }
   Call "multiclock_capture" { 
      "_pi"=P100110101110000010100; "_po"=HLHLLL; }
   "pattern 91": Call "load_unload" { 
      "test_so"=LHLHHHLLHLHHLHLHHLHLHHHLHLHHLLHLHLHHLHHLLHHLLHHHHLLLLHHLHHHLHHHLLHHLLLLHLL; 
      "test_si"=00000110011101001010011011011110000111000110100110100101011111000100110110; }
   Call "multiclock_capture" { 
      "_pi"=P111011101010010110110; "_po"=HLLLLL; }
   "pattern 92": Call "load_unload" { 
      "test_so"=LLLLHHHLLHHHLHLLHLHLLHHLHHLHHHHLHLHLHHLLHLLLLLHHHLHLLHLLHHHLLHLLHLHLHHLLHL; 
      "test_si"=00001100111100001000010110111100001110001101001100000110111110001001101100; }
   Call "multiclock_capture" { 
      "_pi"=P101101110001001011010; "_po"=LLLLLL; }
   "pattern 93": Call "load_unload" { 
      "test_so"=LHLHHHLHHHHHLLLLHLLLLHLHHLHHHHLLHLHHHLLHLLLHLLHHLLLLLHHLLHHHLLLLHHHHHLHLLL; 
      "test_si"=00011001110111000100101101111000011100011010011010000101111100010011011001; }
   Call "multiclock_capture" { 
      "_pi"=P011110111111000101110; "_po"=LLLLLL; }
   "pattern 94": Call "load_unload" { 
      "test_so"=HHLHHHHHHLLHHHLLLHLLHLHHLLLLLLLLHHHHLLLHHLHLLHHLHLLLLHLHHHHHHLLHLLLLHLLHHH; 
      "test_si"=01011001100101000000000101001001100000111001001110001111011100101111110100; }
   Call "multiclock_capture" { 
      "_pi"=P100111110011000101000; "_po"=LHLLLL; }
   "pattern 95": Call "load_unload" { 
      "test_so"=LHHLLLHHLHLHLHLLLLLLLLLHLHLHLLLHHLLLLLHHHLLHLLHHHLLLHHHHLHHHHLHLHHHHHHLLLL; 
      "test_si"=11100101001111001001010100101010011001111111100111011110011101010110101110; }
   Call "multiclock_capture" { 
      "_pi"=P011011010011010100000; "_po"=LLHLHH; }
   "pattern 96": Call "load_unload" { 
      "test_so"=LLLHHHLLLLLHLLHLHLLLLLLHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL; 
      "test_si"=11001010000001111111111001010100110011111111001110111100111010101101011100; }
   Call "multiclock_capture" { 
      "_pi"=P001101101001101001000; "_po"=HHLLHH; }
   "pattern 97": Call "load_unload" { 
      "test_so"=LLLLLLLLLHLLHHHHHLLLLLHLLHLHHHLLHHLHLLLLLLLLLHHHLLLLLLLLLHHLLLHHLLHHLHHLLL; 
      "test_si"=11101010001100100001001100010000111111110011100100000001010001010011111111; }
   Call "multiclock_capture" { 
      "_pi"=P001110011101100001010; "_po"=LLHHHH; }
   "pattern 98": Call "load_unload" { 
      "test_so"=LLLHHHLLLLHHLLLLLLLHLLHHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHH; 
      "test_si"=11000000011100000000001000100001111111100111001000000010100010100111111110; }
   Call "multiclock_capture" { 
      "_pi"=P000111001110110000110; "_po"=HHLHHH; }
   "pattern 99": Call "load_unload" { 
      "test_so"=LLLHHHLLLLHLHLLLHLLLLHHLHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHL; 
      "test_si"=11000010110100011010111111111010100111000011101001111101100001000110111010; }
   Call "multiclock_capture" { 
      "_pi"=P101011001110001101100; "_po"=HHLHHH; }
   "pattern 100": Call "load_unload" { 
      "test_so"=LLLHHHLLLLLHHLHHLLHHLLLLHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHL; 
      "test_si"=10100011000001011011110010011000101100010101010100000111001100001001100100; }
   Call "multiclock_capture" { 
      "_pi"=P011110100111001001100; "_po"=HHHLHH; }
   "pattern 101": Call "load_unload" { 
      "test_so"=LLHHHHHLHLLLHHLHHHLLLLLLHLHLLLLLHLHHLLHLLLLHHLHLHLLLLLHLHLHLHLLLHHHHHLLLLL; 
      "test_si"=01001110000011101000000100110001011000101010101000001110011000010011001001; }
   Call "multiclock_capture" { 
      "_pi"=P101111000011100100100; "_po"=HLLLLL; }
   "pattern 102": Call "load_unload" { 
      "test_so"=LLLHHHLLLLHHLLHLLLLLLLLLHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLH; 
      "test_si"=10011000000111010000001001100010110001010101010000011100110000111101011010; }
   Call "multiclock_capture" { 
      "_pi"=P110111101000110010000; "_po"=HLLLHH; }
   "pattern 103": Call "load_unload" { 
      "test_so"=LHLLLLLLHHLHLHLHLLLLLLHLLHHLHLHLHHLLHLLLLLLHLLLLHLLHHHLLLHLLHHLLLLHLHLLHHL; 
      "test_si"=00101000001110100000010011000101100010101010100000111001100000111100100100; }
   Call "multiclock_capture" { 
      "_pi"=P011011110110111001010; "_po"=LHHLLL; }
   "pattern 104": Call "load_unload" { 
      "test_so"=LLLLLLLLLHHHHLHLLLLLHLLLHHLLHHLHHLLLHHLLHHHLHLLLLLLLLLLHLLLLHHLLLLHLHLLLLL; 
      "test_si"=00011110010010001001111000110010011101011000111001000011100110111101011011; }
   Call "multiclock_capture" { 
      "_pi"=P000101110011001011000; "_po"=LLLLLL; }
   "pattern 105": Call "load_unload" { 
      "test_so"=LLLHHHLLHHLLHLLLHLLHHHHLLLHHLLHLLHHHLHLHHLLLHHHLLHLLLLHHHLLHLLHHHHLHLHHLHH; 
      "test_si"=01110010100111011010101111011101100010111100001001101111101000111101011000; }
   Call "multiclock_capture" { 
      "_pi"=P001010100010110011010; "_po"=HHHLLL; }
   "pattern 106": Call "load_unload" { 
      "test_so"=LHLHHHHLHLLHLHLHHLLLLLHHHHHLLHLHHLLLHLHHHHLLHHLLHHHLHHHHHHLHHLHHHHLHLHHLLL; 
      "test_si"=01110010001011111000000000000100111011101011010100001111101010110111101111; }
   Call "multiclock_capture" { 
      "_pi"=P010110110111100111010; "_po"=LLHLLL; }
   "pattern 107": Call "load_unload" { 
      "test_so"=LLLHHHLLLLHLLHHHHLLLLLLLLLLLHHLLHLLLHHHLHLLLLLHLHLLLHHHHHHLHLLHHLHHHHLHHHH; 
      "test_si"=10010110011000111001001110110000101111011011010010000111110001100110011100; }
   Call "multiclock_capture" { 
      "_pi"=P001011110011000100010; "_po"=LLLLHH; }
   "pattern 108": Call "load_unload" { 
      "test_so"=LLLLHHHLLHHLLLHHHLLHLLHHHLHHLLLLHHLLHHLHHLLLLLLHHLLLLHHHHHHHHHHLLHHLLHHHLL; 
      "test_si"=00100100111101110010011101100000011110110110100110101111100011001100110101; }
   Call "multiclock_capture" { 
      "_pi"=P000101111001100011000; "_po"=LLHLLL; }
   "pattern 109": Call "load_unload" { 
      "test_so"=LHLLLHLHHHHHLHHHLLHLLHHHLHHLLLLLLLLLHLHLLLLLLLHHLLHLHHHHLLHHLHLHLLHLHHLHHH; 
      "test_si"=11011011100010110010010111101110010110000011011110000110001001000010010101; }
   Call "multiclock_capture" { 
      "_pi"=P110010100111011000010; "_po"=HHLLHH; }
   "pattern 110": Call "load_unload" { 
      "test_so"=LHLHHHHHHLLLHLHHLLHLLHLHHHHHLHHLLHLHHLLLLLHHLHHHHLLLLLHLLLHLHHLLLLHLLHLHLH; 
      "test_si"=11101001100101100111010111100010010110111101011110000110110000101000111010; }
   Call "multiclock_capture" { 
      "_pi"=P101010100111110011100; "_po"=HHHLHH; }
   "pattern 111": Call "load_unload" { 
      "test_so"=LHLHHHLHHLLHLHHLLLLLLLLHHHHLHLHLLHLHHHLLLLLHLHHHHLLLLHHLLHLLHLHLHHHLLLLHHH; 
      "test_si"=11011011001001001111101111000100101101111010111110110101100000111101011001; }
   Call "multiclock_capture" { 
      "_pi"=P100101000000011000110; "_po"=HHLHHH; }
   "pattern 112": Call "load_unload" { 
      "test_so"=LLLHHHLLLLHLLLLHHHHHHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLH; 
      "test_si"=01001011010011111010001001101011000101001000100010110010010010001011110000; }
   Call "multiclock_capture" { 
      "_pi"=0111000100000111110100; "_po"=HLLLLL; }
   "pattern 113": Call "load_unload" { 
      "test_so"=LHLLHLHHLHLLHHHHHLHLLLHLLHHLHLHHLLLHLHLLHLLLHLLLHLHHLLHLLHLLHLLLHLHHHHLLLL; 
      "test_si"=01011110000110010011000100110100001100101100011010101001010100111110011010; }
   Call "multiclock_capture" { 
      "_pi"=P110110110000101100110; "_po"=LLLLLL; }
   "pattern 114": Call "load_unload" { 
      "test_so"=HLLHHHLLLLLHHLLHLLHHLLLHLLHHLHLLHLHHLLHLHHLLLHHLHLHLHLLHLHLHHLHHHHHHHLLHLL; 
      "test_si"=01011101100101000011011110001010001111100101101010001000011001010101011011; }
   Call "multiclock_capture" { 
      "_pi"=P110001101000100101100; "_po"=HLLLLL; }
   "pattern 115": Call "load_unload" { 
      "test_so"=LHLLLLLHHHLHLHLLLLHHLHHHHLLLHLHLHLHHHHHLLHLHHLHLHLLLHLLLLHHLHHLHHLHLHLLHHH; 
      "test_si"=10110011000010000010111100010100011111001011010100001100110010101000011110; }
   Call "multiclock_capture" { 
      "_pi"=P111000100101000011100; "_po"=HLHLHH; }
   "pattern 116": Call "load_unload" { 
      "test_so"=LLHHHHHHLLLLLLLLLLLLLLHHLLLHHHLLHLLLHHLLHLLLLLHLLLLLHHLLHHHHLLHLHLLLLHHLHL; 
      "test_si"=00010111000011000101011110010100010001010111101010100010101011110000001101; }
   Call "multiclock_capture" { 
      "_pi"=P011011101001011100110; "_po"=HLLLLL; }
   "pattern 117": Call "load_unload" { 
      "test_so"=LLLLLLHHLHLLHHLLLHLHHLHHHLLHLHLLLHLHLHLHLHLLLHLHHLHLLLHLHHLHLHHHLLLLLLHHLH; 
      "test_si"=11000011100011101101101011001000110100010010001000110111100110111110100001; }
   Call "multiclock_capture" { 
      "_pi"=P100111100100011101100; "_po"=HHLLHH; }
   "pattern 118": Call "load_unload" { 
      "test_so"=LLHLLLHHLHLLHHHLHHLHHHHLHHLHLLLLHHHLLLHHLHLLLHLLHLLLLLHHLLLLLLHHHHLLHLHHLH; 
      "test_si"=10001111000101011010110011111001110011100100010001101111001110010001000010; }
   Call "multiclock_capture" { 
      "_pi"=P110011111010001110100; "_po"=LLLLHH; }
   "pattern 119": Call "load_unload" { 
      "test_so"=LLHLLLHHLHLHLHLHHLHLHHLLHHHHHLLHHHLLLLLLHLLLHHLLLHHLHHHLHLHHLLLHLHHHLLLLLL; 
      "test_si"=00000110001101011010111000111011010011001000100011011110011100100010000100; }
   Call "multiclock_capture" { 
      "_pi"=P111001111001000110010; "_po"=LLLLLL; }
   "pattern 120": Call "load_unload" { 
      "test_so"=LLHLLLHLLHHHLHLHHLHLHHHLLHLLLLHHLHLLLLLLHHLHLLLHLHLHHHLHHHHLHLHLLLLLLLLHLL; 
      "test_si"=11101101111001011010111011111000101111101110011001100110001001101100110010; }
   Call "multiclock_capture" { 
      "_pi"=P010110111100010001110; "_po"=LLHLHH; }
   "pattern 121": Call "load_unload" { 
      "test_so"=LHLHHHHHLLHLLHLHHLHLHHHLHHHHHLLLHHLLLLLHLLLLLHHLLHHLLHLHHHLHHHHHLLHLHHLLLL; 
      "test_si"=00011110010101110111001010101011111111100101101100110110100011110011011010; }
   Call "multiclock_capture" { 
      "_pi"=P100001111110111011000; "_po"=LLLLLL; }
   "pattern 122": Call "load_unload" { 
      "test_so"=LLLHHHHLLHLLLHLHHLLLLLHLHLLLLHHHHHHHHHHLLHLHHLHHLLLLLLHLHLLLLHHHLLHHLHHLLL; 
      "test_si"=00001000101001000110000101010111111111001011011000101101000111100010111100; }
   Call "multiclock_capture" { 
      "_pi"=P010000101111011101110; "_po"=HHLLLL; }
   "pattern 123": Call "load_unload" { 
      "test_so"=LLHHHHLLHLHLHHLLLHHLLHLHLHLHHHHHHLLLLLLLHHLLLHHLLLLLLLLLHLLHLHHLLLLLHHHHLL; 
      "test_si"=11000000110000010100101101001101101000101011101110000000111111101101000010; }
   Call "multiclock_capture" { 
      "_pi"=P100010010111011100000; "_po"=LHLHHH; }
   "pattern 124": Call "load_unload" { 
      "test_so"=LLLHHHLLLLLLHLHHHHLLHHLHHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL; 
      "test_si"=10101001100100100101001010011011010001010111011100000001111111011010000100; }
   Call "multiclock_capture" { 
      "_pi"=P010001001011101101000; "_po"=HHHHHH; }
   "pattern 125": Call "load_unload" { 
      "test_so"=LLLHHHLLLLLLHLHHLHLHLHLHLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL; 
      "test_si"=10101010101100001100010011010100110100010011100111011001001110011100110010; }
   Call "multiclock_capture" { 
      "_pi"=P000010100101000100010; "_po"=HHHLHH; }
   "pattern 126": Call "load_unload" { 
      "test_so"=LLLHHHHLHLHHHLLLHHLLHLLLHHLHHHLLHHLHLLHHLHHHHLLHHHLHHLLLHLHHLLHLLLHLHHLLHL; 
      "test_si"=00110101110011101100100010010110111100110100100010000001011000111101011010; }
   Call "multiclock_capture" { 
      "_pi"=P100101101001001001000; "_po"=HLHLLL; }
   "pattern 127": Call "load_unload" { 
      "test_so"=LHLHLHHHHHLLHHHLHHLLHLLLHLLHLHHLHHHHLHLLLLLHLLLHLLLLLLLLHLLHHHLLLLHLHLLHHL; 
      "test_si"=01000111101100111001110100101110111001101001000110001110110001000101111100; }
   Call "multiclock_capture" { 
      "_pi"=P010010110100100101100; "_po"=LLLLLL; }
   "pattern 128": Call "load_unload" { 
      "test_so"=LHHHHHHHHLHHLLHHHLLHHHLHLLHLHHHLHHHLLHHLHHLHHLHHHLLLHHHLLHHHHHLLHLHHHHHLLL; 
      "test_si"=10000111011110110011001001011110110011010010001100110001100010001011111000; }
   Call "multiclock_capture" { 
      "_pi"=P101001111010010010100; "_po"=LLLLHH; }
   "pattern 129": Call "load_unload" { 
      "test_so"=LLHLHHHHLHHHHLHHLLHHLLHLLHLHHHHLHHLHHHLHLHLLLHHLLLHHLLLHLLHHLLLLHLLHLLLHLL; 
      "test_si"=11110100011110101011110010011100011011110101101010110000111000000111011010; }
   Call "multiclock_capture" { 
      "_pi"=P010000110110010111000; "_po"=LLHLHH; }
   "end 129 unload": Call "load_unload" { 
      "test_so"=HHLHHHLLLLHHHLHLHLHHHHLLHLHLLHLLHHHLLLLHLHHLLHLHLLHHLLLLHLLHHLLLLHLLHLLHLL; }
}

// Patterns reference 394 V statements, generating 9957 test cycles
