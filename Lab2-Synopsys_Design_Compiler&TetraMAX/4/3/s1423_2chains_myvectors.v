STIL 1.0 { Design 2005; }
Header {
   Title "  TetraMAX(R)  T-2022.03-SP1-i20220414_145826 STIL output";
   Date "Mon Jun  2 20:04:47 2025";
   Source "Minimal STIL for design `s1423'";
   History {
      Ann {*  Incoming_Date "Mon Jun  2 20:03:35 2025"  *}
      Ann {*  Incoming_Src "DFT Compiler T-2022.03-SP1"  *}
      Ann {*     Uncollapsed Stuck Fault Summary Report *}
      Ann {* ----------------------------------------------- *}
      Ann {* fault class                     code   #faults *}
      Ann {* ------------------------------  ----  --------- *}
      Ann {* Detected                         DT       2531 *}
      Ann {* Possibly detected                PT          0 *}
      Ann {* Undetectable                     UD          0 *}
      Ann {* ATPG untestable                  AU          0 *}
      Ann {* Not detected                     ND          0 *}
      Ann {* ----------------------------------------------- *}
      Ann {* total faults                              2531 *}
      Ann {* test coverage                           100.00% *}
      Ann {* ----------------------------------------------- *}
      Ann {*  *}
      Ann {*            Pattern Summary Report *}
      Ann {* ----------------------------------------------- *}
      Ann {* #internal patterns                         128 *}
      Ann {*     #basic_scan patterns                   128 *}
      Ann {* #external patterns (s1423_test_set.v)      124 *}
      Ann {*     #basic_scan patterns                   124 *}
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
      Ann {* PSDA = #124#2#0/0 *}
      Ann {* internal_clock = CK *}
   }
}
Signals {
   "GND" In; "VDD" In; "CK" In; "G0" In; "G1" In; "G10" In; "G11" In; "G12" In; "G13" In;
   "G14" In; "G15" In; "G16" In; "G2" In; "G3" In; "G4" In; "G5" In; "G6" In; "G7" In;
   "G8" In; "G9" In; "test_si1" In { ScanIn; } "test_si2" In { ScanIn; } "test_se" In;
   "G701BF" Out; "G702" Out; "G726" Out; "G727" Out; "G729" Out; "test_so1" Out {
   ScanOut; } "test_so2" Out { ScanOut; }
}
SignalGroups {
   "_pi" = '"CK" + "G0" + "G1" + "G10" + "G11" + "G12" + "G13" + "G14" + "G15" + "G16"
   + "G2" + "G3" + "G4" + "G5" + "G6" + "G7" + "G8" + "G9" + "GND" + "VDD" + "test_si1"
   + "test_si2" + "test_se"'; // #signals=23
   "_in" = '"GND" + "VDD" + "CK" + "G0" + "G1" + "G10" + "G11" + "G12" + "G13" + "G14"
   + "G15" + "G16" + "G2" + "G3" + "G4" + "G5" + "G6" + "G7" + "G8" + "G9" + "test_si1"
   + "test_si2" + "test_se"'; // #signals=23
   "all_inputs" = '"CK" + "G0" + "G1" + "G10" + "G11" + "G12" + "G13" + "G14" + "G15"
   + "G16" + "G2" + "G3" + "G4" + "G5" + "G6" + "G7" + "G8" + "G9" + "GND" + "VDD"
   + "test_si1" + "test_si2" + "test_se"'; // #signals=23
   "_po" = '"G701BF" + "G702" + "G726" + "G727" + "G729" + "test_so1" + "test_so2"';
   // #signals=7
   "_si" = '"test_si1" + "test_si2"' { ScanIn; } // #signals=2
   "all_outputs" = '"G701BF" + "G702" + "G726" + "G727" + "G729" + "test_so1" + "test_so2"';
   // #signals=7
   "all_ports" = '"all_inputs" + "all_outputs"'; // #signals=30
   "_clk" = '"CK"'; // #signals=1
   "_so" = '"test_so1" + "test_so2"' { ScanOut; } // #signals=2
   "_out" = '"G701BF" + "G702" + "G726" + "G727" + "G729" + "test_so1" + "test_so2"';
   // #signals=7
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
      ScanLength 37;
      ScanIn "test_si1";
      ScanOut "test_so1";
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
      ; "s1423.DFF_35.Q_reg" ; "s1423.DFF_36.Q_reg" ; }
      ScanMasterClock "CK" ;
   }
   ScanChain "2" {
      ScanLength 37;
      ScanIn "test_si2";
      ScanOut "test_so2";
      ScanInversion 0;
      ScanCellType  { CellIn "SD"; CellOut "Q"; }
      ScanCells { "s1423.DFF_37.Q_reg" ; "s1423.DFF_38.Q_reg" ; "s1423.DFF_39.Q_reg"
      ; "s1423.DFF_40.Q_reg" ; "s1423.DFF_41.Q_reg" ; "s1423.DFF_42.Q_reg" ; "s1423.DFF_43.Q_reg"
      ; "s1423.DFF_44.Q_reg" ; "s1423.DFF_45.Q_reg" ; "s1423.DFF_46.Q_reg" ; "s1423.DFF_47.Q_reg"
      ; "s1423.DFF_48.Q_reg" ; "s1423.DFF_49.Q_reg" ; "s1423.DFF_50.Q_reg" ; "s1423.DFF_51.Q_reg"
      ; "s1423.DFF_52.Q_reg" ; "s1423.DFF_53.Q_reg" ; "s1423.DFF_54.Q_reg" ; "s1423.DFF_55.Q_reg"
      ; "s1423.DFF_56.Q_reg" ; "s1423.DFF_57.Q_reg" ; "s1423.DFF_58.Q_reg" ; "s1423.DFF_59.Q_reg"
      ; "s1423.DFF_60.Q_reg" ; "s1423.DFF_61.Q_reg" ; "s1423.DFF_62.Q_reg" ; "s1423.DFF_63.Q_reg"
      ; "s1423.DFF_64.Q_reg" ; "s1423.DFF_65.Q_reg" ; "s1423.DFF_66.Q_reg" ; "s1423.DFF_67.Q_reg"
      ; "s1423.DFF_68.Q_reg" ; "s1423.DFF_69.Q_reg" ; "s1423.DFF_70.Q_reg" ; "s1423.DFF_71.Q_reg"
      ; "s1423.DFF_72.Q_reg" ; "s1423.DFF_73.Q_reg" ; }
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
      C { "all_inputs"=0NNNNNNNNNNNNNNNNNNNNNN; "all_outputs"=XXXXXXX; }
      V { "_pi"=#######################; "_po"=#######; }
   }
   "allclock_capture" {
      W "_allclock_capture_WFT_";
      C { "all_inputs"=0NNNNNNNNNNNNNNNNNNNNNN; "all_outputs"=XXXXXXX; }
      V { "_pi"=#######################; "_po"=#######; }
   }
   "allclock_launch" {
      W "_allclock_launch_WFT_";
      C { "all_inputs"=0NNNNNNNNNNNNNNNNNNNNNN; "all_outputs"=XXXXXXX; }
      V { "_pi"=#######################; "_po"=#######; }
   }
   "allclock_launch_capture" {
      W "_allclock_launch_capture_WFT_";
      C { "all_inputs"=0NNNNNNNNNNNNNNNNNNNNNN; "all_outputs"=XXXXXXX; }
      V { "_pi"=#######################; "_po"=#######; }
   }
   "load_unload" {
      W "_default_WFT_";
      C { "all_inputs"=0NNNNNNNNNNNNNNNNNNNNNN; "all_outputs"=XXXXXXX; }
      "Internal_scan_pre_shift": V { "test_se"=1; }
      Shift {          W "_default_WFT_";
         V { "_clk"=P; "_si"=##; "_so"=##; }
      }
   }
}
MacroDefs {
   "test_setup" {
      W "_default_WFT_";
      C { "all_inputs"=NNNNNNNNNNNNNNNNNNNNNNN; "all_outputs"=XXXXXXX; }
      V { "CK"=0; }
      V { }
   }
}
Pattern "_pattern_" {
   W "_multiclock_capture_WFT_";
   "precondition all Signals": C { "_pi"=00000000000000000000000; "_po"=XXXXXXX; }
   Macro "test_setup";
   Ann {* chain_test *}
   "pattern 0": Call "load_unload" { 
      "test_si1"=0011001100110011001100110011001100110; "test_si2"=0011001100110011001100110011001100110; }
   Call "multiclock_capture" { 
      "_pi"=01111100110100011000001; "_po"=LHHHLLL; }
   "pattern 1": Call "load_unload" { 
      "test_so1"=LLHHLLHHLLHHLLHHLLHHLLHHLLHHLLHHLLHHL; "test_so2"=LLHHLLHHLLHHLLHHLLHHLLHHLLHHLLHHLLHHL; 
      "test_si1"=1000011101101111100101010001100000101; "test_si2"=0111001001011011101001111000100101101; }
   Call "multiclock_capture" { 
      "_pi"=P1111110011010001110000; "_po"=HLHHLHL; }
   "pattern 2": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLHHHHHLLLLLLLLLLLLLLLLLLLH; "test_so2"=LLLHHHLLLLHHLHHLLLLLLLHHHLLLLLLLLLLLL; 
      "test_si1"=1100110101101000111000001011110001000; "test_si2"=0101110110011010100111001101011011101; }
   Call "multiclock_capture" { 
      "_pi"=P1100010111000011101100; "_po"=LLLLLHL; }
   "pattern 3": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL; "test_so2"=LLLHHHLLLLLLLHHHLLLLLLLLLLLLLLLLLLLLL; 
      "test_si1"=0101100101100110000010111111010011011; "test_si2"=0000001000011000111010100110100001101; }
   Call "multiclock_capture" { 
      "_pi"=P0001100001000110100110; "_po"=HHLHLLL; }
   "pattern 4": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHH; "test_so2"=LLLHHHLLLLHLLHLHHLLLLLHLLLLLLLLLLLLLL; 
      "test_si1"=0111000101111011110111010110000100101; "test_si2"=1010110100011100000001110001010001100; }
   Call "multiclock_capture" { 
      "_pi"=P1111011010000000000110; "_po"=HLHLHLH; }
   "pattern 5": Call "load_unload" { 
      "test_so1"=LHHHHLLHLHHHHLHHHHLLHHLLLHHLHHLHLLHLH; "test_so2"=HHLLLLHLHHLHHHLLLLLLLHHHLLLHLHLLHHHLL; 
      "test_si1"=1110001011110111101110101111101001010; "test_si2"=0110101000111000000011100010100011000; }
   Call "multiclock_capture" { 
      "_pi"=P0111101001000000010010; "_po"=HHHLLHL; }
   "pattern 6": Call "load_unload" { 
      "test_so1"=LLHLHLHLHHHHLHHHHLHLHLHHLLLLLHHLHLHHH; "test_so2"=LLHHHHLLLLHHHLLLLLLHLLHLLLHHLLLLHHLLH; 
      "test_si1"=0000011001011000101111110001100010111; "test_si2"=0100110101011101110011111001010100111; }
   Call "multiclock_capture" { 
      "_pi"=P1100010010000011001000; "_po"=HLLLLLL; }
   "pattern 7": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHH; "test_so2"=LLLHHHLLLLLLLLHHLLLLLLLHHLLLLLLLLLLLL; 
      "test_si1"=0000110010110001011111100011000101110; "test_si2"=1001101010111011100111110010101001110; }
   Call "multiclock_capture" { 
      "_pi"=P1110001001000001110000; "_po"=HHLLHLH; }
   "pattern 8": Call "load_unload" { 
      "test_so1"=LLLLHHLLHLHHLLLHLHHHHHHHLLHHLLLHLHLHL; "test_so2"=HLHHHHHLHLHHLLHHHLLLLLHHLLHHLLHLHHHHL; 
      "test_si1"=1101101011001101001101101110111011110; "test_si2"=1000110001011010111011011000000001010; }
   Call "multiclock_capture" { 
      "_pi"=P1000101010000011111100; "_po"=HLLLHHH; }
   "pattern 9": Call "load_unload" { 
      "test_so1"=HHHLLLHLHHLLHHLHLLHLLHHHHHHLHLHLHHLHL; "test_so2"=LLHHHHLLLLLHHLHLHHHLHHLHHLLLLLLLLHLHL; 
      "test_si1"=0111001101010100110110111011101111010; "test_si2"=0011000101101011101101100100000101011; }
   Call "multiclock_capture" { 
      "_pi"=P1110001000100000111110; "_po"=HHHLLLL; }
   "pattern 10": Call "load_unload" { 
      "test_so1"=LHHHLHLLHLHLLHLLHHLHHLLLHLHHHLHLLLHHL; "test_so2"=LLHHHHLHLLHLLLHHHLLLLLHLLHLLHLLHLHLHH; 
      "test_si1"=0001010100011110011111011111101110111; "test_si2"=1101101111111010101111110100011000000; }
   Call "multiclock_capture" { 
      "_pi"=P0000101010110011001110; "_po"=HHLLHLH; }
   "pattern 11": Call "load_unload" { 
      "test_so1"=LLLHLHLHLLLHLLLLLHHHHHLLHHHHHLHHHLHHH; "test_so2"=LHLHHHHHHLHHHLHLHLHHHHHHLHLLHHHLLLLLL; 
      "test_si1"=1110100110001011001100010111101101100; "test_si2"=0000111011011000101011010100100000110; }
   Call "multiclock_capture" { 
      "_pi"=P0111110111111010100010; "_po"=LLLLLHL; }
   "pattern 12": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL; "test_so2"=LLLHHHLLLLHHLHLHLLLLLLHHLLLLLLLLLLLLL; 
      "test_si1"=1101001100010110011000101111011011000; "test_si2"=0001100110110001010110111000000101101; }
   Call "multiclock_capture" { 
      "_pi"=P0011111011111101000100; "_po"=HHLLLHL; }
   "pattern 13": Call "load_unload" { 
      "test_so1"=HHLHLLHHLLLHLHHLLHHLLLHHHHHHLHHLHHLLL; "test_so2"=LHLLLLHHHHHHLLLHLHLHHLHHHLLLHLLHLHHLH; 
      "test_si1"=1100101100110110000111101100001100111; "test_si2"=0000010010011110110010011100110011010; }
   Call "multiclock_capture" { 
      "_pi"=P0111001101101110111100; "_po"=LLLLLHL; }
   "pattern 14": Call "load_unload" { 
      "test_so1"=HHLHLHLLLHHLLHHLLLLLHHLHHHLLHHHHLLLHH; "test_so2"=HHLHHHLHHLLHHHHLHHLLHLLHHHLLHHLLHHLHL; 
      "test_si1"=0101010111011011111101110000101001101; "test_si2"=1011010000010000010010010100110100011; }
   Call "multiclock_capture" { 
      "_pi"=P0100001000010100001110; "_po"=HLHLHLH; }
   "pattern 15": Call "load_unload" { 
      "test_so1"=LHLHLLLLHLHLHLHHHHHHLHLLLLLLHLHLLHHLH; "test_so2"=LLLHHHLLLLLHLLLLLHLLHLLHLHLLHHLHLLHLH; 
      "test_si1"=0110100000000000001001001001100011001; "test_si2"=1101100100001101010000110111111010000; }
   Call "multiclock_capture" { 
      "_pi"=P0101100110101001010010; "_po"=LHLHHLH; }
   "pattern 16": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHH; "test_so2"=LLLHHHLLLLHLHLHLLHLLLLHLHLLLLLLLLLLLL; 
      "test_si1"=1101000000000000010010010011000110010; "test_si2"=1011001000011010100001101111110100000; }
   Call "multiclock_capture" { 
      "_pi"=P0010100011010100101000; "_po"=HHHHHHH; }
   "pattern 17": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHL; "test_so2"=LLLHHHLLLLLHLHLLHLLLLLHLLLLLLLLLLLLLL; 
      "test_si1"=1010000000000000100100100110001100101; "test_si2"=0110000001110101000011011111101000001; }
   Call "multiclock_capture" { 
      "_pi"=P1011011001101010000100; "_po"=HHHLLHL; }
   "pattern 18": Call "load_unload" { 
      "test_so1"=LLHLHLLHLLLLLLLLLLLLLLLHLHHLHHHHLLLLL; "test_so2"=LHHLLHLLLHHHHHLHLLLHLLLHHLLLLLHLLLLLL; 
      "test_si1"=0100000000000001001001001100011001010; "test_si2"=1100010001100101101011111111000000011; }
   Call "multiclock_capture" { 
      "_pi"=P0100101110110101010010; "_po"=LLLLHLH; }
   "pattern 19": Call "load_unload" { 
      "test_so1"=HLLLHLLHLLLHLLLHLLLHHLHHHHLLLLHLLHLLL; "test_so2"=LHHHHHLLLLHLLHLHHLHLHHHHHHHHLLLLLLLHH; 
      "test_si1"=1000000000000001010010011000110010100; "test_si2"=1001010011010001000010111110110000110; }
   Call "multiclock_capture" { 
      "_pi"=P0010011110011010111000; "_po"=LLLLHHH; }
   "pattern 20": Call "load_unload" { 
      "test_so1"=HLLLLLLHLLLLLLLHLHLLHHHLHLLLHHLLHLLLL; "test_so2"=LLLLHHLLHHLHLLLHLLLLHLHHHHHLHHLLHLHHL; 
      "test_si1"=1100001110110011010110010001010101011; "test_si2"=1001100010011101101111000001010011011; }
   Call "multiclock_capture" { 
      "_pi"=P0110101101101110001100; "_po"=LHLLHHH; }
   "pattern 21": Call "load_unload" { 
      "test_so1"=HHLLLLHHHLHHLLLLLHLHHLLLLLLHLHLHHLHHH; "test_so2"=LLHHHHLLHLLHHHLHHLHHHHLLLLLHHHLLHHLHH; 
      "test_si1"=0100101000010101001110011100000101001; "test_si2"=1010100101100000100001000001111010100; }
   Call "multiclock_capture" { 
      "_pi"=P1101111010101001001000; "_po"=HHHLHLH; }
   "pattern 22": Call "load_unload" { 
      "test_so1"=HLLHLLHLLLLHLHLHLLHLHLLLHHLLHHLHHLHLH; "test_so2"=LHLLHLHLHHHLLLLLHLLLLHLLLLHLLHHLHLHLL; 
      "test_si1"=1001010000100001111100110000001010010; "test_si2"=0101001011000001000010000011110101000; }
   Call "multiclock_capture" { 
      "_pi"=P1110111111100000110000; "_po"=LHLLLHL; }
   "pattern 23": Call "load_unload" { 
      "test_so1"=HLLHLLLLLHLHLLLHHHHHLLLLLLLLLLHLHHHLL; "test_so2"=LHHLLHHLHHLLLLLHLLLLLLLLLHLLLHLHHHLHL; 
      "test_si1"=1110101111100101101011011000100100010; "test_si2"=0001110010111111101011111011111000111; }
   Call "multiclock_capture" { 
      "_pi"=P1000111000001001001100; "_po"=HLLLLHL; }
   "pattern 24": Call "load_unload" { 
      "test_so1"=HHHLHLHHHHHLLLLLLLHLHHLLHLLLHLLHLHHHL; "test_so2"=HLLLLLLLHHLLLLHLLLLLLLLLHLLLLHHLHLHHH; 
      "test_si1"=1101011111000110010010111001001101101; "test_si2"=0011100101011111100001110111110001011; }
   Call "multiclock_capture" { 
      "_pi"=01100011100100100110010; "_po"=LHHLLHL; }
   "pattern 25": Call "load_unload" { 
      "test_so1"=HHLHLHHHHHLLLHHLLHLLHLHHHLLHLLHHLHHLH; "test_so2"=LLHHHLLHLHLHHHHHHLLLLHHHLHHHHHLLLHLHH; 
      "test_si1"=0110110011111011111111001010100011000; "test_si2"=1100111110010010110111010010110001001; }
   Call "multiclock_capture" { 
      "_pi"=P1001101000110001011100; "_po"=HLLLHLH; }
   "pattern 26": Call "load_unload" { 
      "test_so1"=LHLLLHLLHHHHHHLLLHHLHHLHHLHHLHHHLLHLH; "test_so2"=LLLHHHHHLLLHLLHLHHLHHHLHLLHLHHLLHHLLH; 
      "test_si1"=1101100001110101111110010101000110000; "test_si2"=1001011100110101101011100111100010010; }
   Call "multiclock_capture" { 
      "_pi"=P1100111100011000111010; "_po"=LLLLHHH; }
   "pattern 27": Call "load_unload" { 
      "test_so1"=HHLHHLLHHHHHLHLHHHHHHHHLLHLHLLLHHHHLL; "test_so2"=LLLLLLHHLHHHLHLHHLHLHHHLLHHHHLLLHLLHL; 
      "test_si1"=1011000011111101111100101010001100000; "test_si2"=0010111001001011011101011110000100101; }
   Call "multiclock_capture" { 
      "_pi"=P1110011010001100011100; "_po"=HLHLLHL; }
   "pattern 28": Call "load_unload" { 
      "test_so1"=HLHHHLLLHHHHHHHLLHHLLLHHHLHLHHHHLLLLH; "test_so2"=LLLHHHHLLHLLHLHHLHHHLHLHHHHLLLLHLLHLH; 
      "test_si1"=0110000111001011111001010100011000000; "test_si2"=0101110010010110111010011110001001011; }
   Call "multiclock_capture" { 
      "_pi"=P1111001001000110001010; "_po"=HLLLLLL; }
   "pattern 29": Call "load_unload" { 
      "test_so1"=LHHLLLLHHHLLHLHHHHHLLHLLLHLLLHHLLHHLL; "test_so2"=LHHHHHLHLLLHLHHLHHHLHLLHHHHLLLHLLHLHH; 
      "test_si1"=0001100111001110011101100010101100000; "test_si2"=0100010110100101101011101001101000111; }
   Call "multiclock_capture" { 
      "_pi"=P1100101001101111100010; "_po"=HLLLLLL; }
   "pattern 30": Call "load_unload" { 
      "test_so1"=LLHLLLHLHLLHHHHLLHHLLHLHLLHHLHHHLLLLL; "test_so2"=LHLHHHLHHLHLLHLHHLHLHHHLHLLHHLHLLLHHH; 
      "test_si1"=0011001110001100111011000011101000000; "test_si2"=1000101101011111110101010011110001110; }
   Call "multiclock_capture" { 
      "_pi"=P0110011001110111110100; "_po"=HHLLHLH; }
   "pattern 31": Call "load_unload" { 
      "test_so1"=LHHHHLHHHLLLLLLLLHLHHHLHLHLLLHHLLLLLL; "test_so2"=LLLHLHHHLHLHLHHHHLLLLLLHLHLLLHLLLHHHL; 
      "test_si1"=0111111011111111001011101000011100001; "test_si2"=0101011100010000010000011110011011011; }
   Call "multiclock_capture" { 
      "_pi"=P1111101011010100001100; "_po"=HLLLLLL; }
   "pattern 32": Call "load_unload" { 
      "test_so1"=LHHHHLLLHHHHHHHHHLHLHHLHHLLLLHHHLLLLH; "test_so2"=LLLHHHHLLLLHLLLLLHLLLLLHHHHLLHHLHHHLH; 
      "test_si1"=1110010001111001001010110010010100010; "test_si2"=1110001110001111011010110101001111101; }
   Call "multiclock_capture" { 
      "_pi"=P0011011110000101100000; "_po"=LLHLHHH; }
   "pattern 33": Call "load_unload" { 
      "test_so1"=LLHLHLLLHHHLHLLHLLLHHLLLLLHLLLLHLHHLL; "test_so2"=LLHLLLHHLHLLLHHHLLLLLLHHLHLHHLHHHLLLL; 
      "test_si1"=1101000100110100001000000110000100100; "test_si2"=1000001010110001001111000011100110100; }
   Call "multiclock_capture" { 
      "_pi"=P1101000000111101000110; "_po"=HHLHHHH; }
   "pattern 34": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLLHLLLLLLLLLLLLLLLLLLLLLLL; "test_so2"=LLLHHHLLLLHLHLHLHHLLLLHHHLLLLLLLLLLLL; 
      "test_si1"=0101110100010110111101111010111110001; "test_si2"=0101111101101011000110100111101010100; }
   Call "multiclock_capture" { 
      "_pi"=P1101111001100100101110; "_po"=HLLLLLL; }
   "pattern 35": Call "load_unload" { 
      "test_so1"=LHLHHHLHLLLHLHHLHHHHLHHLHLHLHHHHHLLLH; "test_so2"=LLLHHHHLLHHLLLHHLLLHHLHLLHHHHLHLHLHLL; 
      "test_si1"=1011101000101101111011110101111100011; "test_si2"=1001011011010101101011001111000101000; }
   Call "multiclock_capture" { 
      "_pi"=P1111111010110010000110; "_po"=HLLLHHH; }
   "pattern 36": Call "load_unload" { 
      "test_so1"=HLHHHLHHLHLHHHLHHHHLHHLLLHLHHHHHLLLHH; "test_so2"=LLLLHHLHHHLHLHLHHLHLHHLLHHHHLLLHHHLLL; 
      "test_si1"=0110110110010000101010000001010100111; "test_si2"=0111100000000011100000110111010010110; }
   Call "multiclock_capture" { 
      "_pi"=P1011011111110010110000; "_po"=LHHLLLL; }
   "pattern 37": Call "load_unload" { 
      "test_so1"=LHHLHHLHHLLHLLLLLLHLHLLHLLLHLHLHLLLHH; "test_so2"=LHHLLLLLLHLLLLHHHLLLLLHHLHHHHHLLHLHHL; 
      "test_si1"=1101101100110011010100010010101001111; "test_si2"=1111010000010101101011101110100001100; }
   Call "multiclock_capture" { 
      "_pi"=P0101101111111011011100; "_po"=LLHLHHH; }
   "pattern 38": Call "load_unload" { 
      "test_so1"=HHLHHHLLLHHHLLHHLHLHLHHLLLHLHLHLLHLHH; "test_so2"=LHLHHHLLLLLHLHLHHLHLHHHLHHHLHLLLHHHLL; 
      "test_si1"=1011011001110001001000100101010011110; "test_si2"=1111000000001110000011011101001011001; }
   Call "multiclock_capture" { 
      "_pi"=P1010111111110001101010; "_po"=LHHLHHH; }
   "pattern 39": Call "load_unload" { 
      "test_so1"=HLHHLLLLHHHHLLLHLLHLLLLHLHLHLHLLHHLLL; "test_so2"=LHLLLLLLLHLLLHHLLLLLLLLHHHLHHLHLHHLHH; 
      "test_si1"=0111010100101011001100100000001011100; "test_si2"=1001000110101011111100010011101110100; }
   Call "multiclock_capture" { 
      "_pi"=P0001111000010000000110; "_po"=HHLLHLH; }
   "pattern 40": Call "load_unload" { 
      "test_so1"=LHHHLLLLLHLHHLHHLLHHLLLHLLLLLLHLHHHLL; "test_so2"=HHLLLLHHHHHLHLHHHHHHLLLHLHLLLLHHHHLLL; 
      "test_si1"=1111001110010000000100110010111011001; "test_si2"=0100101011000101001010001110100101111; }
   Call "multiclock_capture" { 
      "_pi"=P1100011111100111010000; "_po"=LHLLLHL; }
   "pattern 41": Call "load_unload" { 
      "test_so1"=LLHHHHLLHLLHLLLLLLLLLLHLLLHLHLLHLLHHH; "test_so2"=LHHLHLHLHHLLLHLHLLHLHLLLHHHHLLLHHHHHL; 
      "test_si1"=1110011100100000001001100101110110011; "test_si2"=1000100110010001101011011101001011111; }
   Call "multiclock_capture" { 
      "_pi"=P0110001111110011001000; "_po"=LHLLHHH; }
   "pattern 42": Call "load_unload" { 
      "test_so1"=LLHLHLLLLLHLLLLLLLLHLHHHLHLHHLLHHHHHH; "test_so2"=LLHHHHLHHLLHHLLHHLHHLLLHHHLHHLHLHLLLL; 
      "test_si1"=1101011110000110001110101001000000110; "test_si2"=0110101010000111111111010011101111000; }
   Call "multiclock_capture" { 
      "_pi"=P0111100100010110000110; "_po"=LHHHLHL; }
   "pattern 43": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL; "test_so2"=LLLHHHLLLLHHHLLHHLLLLLLHLLLLLLLLLLLLL; 
      "test_si1"=1010111100001100011101010010000001100; "test_si2"=1111100100011111100100010101011110001; }
   Call "multiclock_capture" { 
      "_pi"=00011111010001011010011; "_po"=HHHLHHH; }
   "pattern 44": Call "load_unload" { 
      "test_so1"=HLHLHHHHLLLLHHLLLHHHLHLHLLHLLLLLLHHLL; "test_so2"=HHHHHLLHLLLHHHHHHLLHLLLHLHLHLHHHHLLLH; 
      "test_si1"=0100011111011100100111000111101011001; "test_si2"=1011111110010000100111100111000000100; }
   Call "multiclock_capture" { 
      "_pi"=P1101011010101010001010; "_po"=HLHLHLH; }
   "pattern 45": Call "load_unload" { 
      "test_so1"=LHLLLHHHHHLHHHLLHLLHHHLHLHHHHLHLHHLLH; "test_so2"=LLLLLLHHHHLHLLLLHLLHHHHLLHHHLLLLHLHLL; 
      "test_si1"=1001011001111011010011100111100010011; "test_si2"=0010111010001110001101100111110001111; }
   Call "multiclock_capture" { 
      "_pi"=P0010001110111010110010; "_po"=LLHLLHL; }
   "pattern 46": Call "load_unload" { 
      "test_so1"=HLLHHHHLLHHHHLHHLLHHHHLHHLLLLHLLHLLHH; "test_so2"=LLLHHHHLHLLLHHHLLLHHLHHLLHHHHHLLHHHHH; 
      "test_si1"=0010110011111000000111011111111011011; "test_si2"=0111010100001100101011001111100011111; }
   Call "multiclock_capture" { 
      "_pi"=P0001001111001101011100; "_po"=LLHLLLL; }
   "pattern 47": Call "load_unload" { 
      "test_so1"=LHHLHLLLHHHLHLLLLLLHLLHLHHHHHHHLHHLHH; "test_so2"=LHLHHHHLLLLLHHLLHLHLHHLLHHHHHLLLHLLLH; 
      "test_si1"=0101100111100001001110111111001001111; "test_si2"=1110101000111001110110011111000111110; }
   Call "multiclock_capture" { 
      "_pi"=P1100101011111110111010; "_po"=HHHLHLH; }
   "pattern 48": Call "load_unload" { 
      "test_so1"=HLHLLLLHHHHLLLLLLLHLHLHLHHHHHHHLLHHHH; "test_so2"=HHHHHHHLLLHHLLLHHLLLLLLHHHHHHLLHHHHHL; 
      "test_si1"=1011001111010001111101111110010011110; "test_si2"=1101000001110011101100111110001111100; }
   Call "multiclock_capture" { 
      "_pi"=P1000011001110111001100; "_po"=HHLLHHH; }
   "pattern 49": Call "load_unload" { 
      "test_so1"=HLHHLHLLHLHLLLLLLHHHLHLLHHHLLHLLHHHHL; "test_so2"=LHHHLLLLLHHHLLHHHLHHLLHHHHHLHLHHHHHLL; 
      "test_si1"=0110011110110000011011111100100111001; "test_si2"=1010110011100111011000111100011011001; }
   Call "multiclock_capture" { 
      "_pi"=P1110001000111011110010; "_po"=HLHLHLH; }
   "pattern 50": Call "load_unload" { 
      "test_so1"=LHHLHHHHHLHHLLLLLHLHHHHLHHLHLHLLLLHLH; "test_so2"=LLLHHHLLHLHLLHHHLHHLLLHHHHLLLHHLHHLLH; 
      "test_si1"=1101011010100111101010011011100011110; "test_si2"=0001010001100001001001010001000010101; }
   Call "multiclock_capture" { 
      "_pi"=P1011101111100010011110; "_po"=LLLLLHL; }
   "pattern 51": Call "load_unload" { 
      "test_so1"=HHLHLLLLLHLHLLLLLLHLHHHLHLHHHLLLHHHLL; "test_so2"=LHLHHHLLHLHLLLLHLLLLLLLLHLLLLLHHHHLLH; 
      "test_si1"=1011010010010001001001010101101011001; "test_si2"=0010100101101101101000001011110101000; }
   Call "multiclock_capture" { 
      "_pi"=00001010000110110111001; "_po"=HLHHLHL; }
   "pattern 52": Call "load_unload" { 
      "test_so1"=HLHHLHLLHLLHLLLHLLHLLHLHLHLHHLHLHHLLH; "test_so2"=LLHLHLLHLHHLHHLHHLHLLLLLHLHHHHLHLHLLL; 
      "test_si1"=1111010011110100001111001001111101011; "test_si2"=1000101101110100101010111110010011111; }
   Call "multiclock_capture" { 
      "_pi"=00100001011100100111110; "_po"=HLLLHHH; }
   "pattern 53": Call "load_unload" { 
      "test_so1"=HHHHLHLLHHHHLHLLLLHHHHLLHLLHHHHHLHLHH; "test_so2"=HLLLHLHHLHHHLHLLHLHLHLHHHHHLLHLLHHHHH; 
      "test_si1"=1110000111100100011110010011110010010; "test_si2"=0011111011111001001101111100100011100; }
   Call "multiclock_capture" { 
      "_pi"=P1010001101110010011110; "_po"=LLHLLHL; }
   "pattern 54": Call "load_unload" { 
      "test_so1"=HHHLLLLHHHHLLHLLLHHHHLLLLLHHHHLLHHHLL; "test_so2"=HLLHHHHLHLHHHLLHLLHHLHHHHHLLHLLLHHHLL; 
      "test_si1"=1011010000100101000010001010011011011; "test_si2"=0111000011111010100010100001101111101; }
   Call "multiclock_capture" { 
      "_pi"=P1000111000111011000100; "_po"=HHHLLHL; }
   "pattern 55": Call "load_unload" { 
      "test_so1"=HLHHLLLLLHLHLLLLLLLLHHHHHLHLLHHLHHLHH; "test_so2"=LHLHLLLLHHHHHLHLHLLLHLHLLLHLLLHHHLLLH; 
      "test_si1"=0111000110011100010001110110001010110; "test_si2"=1010010001011010111111101010100111100; }
   Call "multiclock_capture" { 
      "_pi"=P1000111011111010000000; "_po"=HLHLHLH; }
   "pattern 56": Call "load_unload" { 
      "test_so1"=LHHHHLHLLLHHLLLLLLHHLHLLLHHLHHHLHLHHL; "test_so2"=LLLLLHLLLHLHLLHLHLLLLLHHHLLLLLHHHHHLL; 
      "test_si1"=1110001100110100010011101100010101100; "test_si2"=0100110010100101111111010101001011000; }
   Call "multiclock_capture" { 
      "_pi"=P0100011101011101010000; "_po"=LLLLLHL; }
   "pattern 57": Call "load_unload" { 
      "test_so1"=HHHLHLHHLLHHLHLLLLHHHHLHHHLLLLLHLHHLL; "test_so2"=LHLLLLLLHHHLLHLHHHHHHHLHLHLHLLHLHHLLL; 
      "test_si1"=1100011001110001100111010011101011000; "test_si2"=1000000101101011111110101010011110001; }
   Call "multiclock_capture" { 
      "_pi"=P0010001110111110111000; "_po"=LLLLHHH; }
   "pattern 58": Call "load_unload" { 
      "test_so1"=LLLLHLLLHHHLLLLLLLLLLLHLLHLLLHLHLLHLL; "test_so2"=HLHHHHLHLLHLLLHHHLLLLLHLHLHLHHHHHLLHL; 
      "test_si1"=1000110011100011001110110001010110000; "test_si2"=0010011011010101101011000011101100011; }
   Call "multiclock_capture" { 
      "_pi"=P1001001111011111001100; "_po"=LLHLLHL; }
   "pattern 59": Call "load_unload" { 
      "test_so1"=LLLHLLLLHHLLLLHHLLHLHLLLLLLHLLLHHLLLL; "test_so2"=LLHHHHLHHLLHLHLHHLHLHHLLLHLLLLHHHLHLL; 
      "test_si1"=0101111110101010010111010010110111101; "test_si2"=0000010100011101101011001010001001101; }
   Call "multiclock_capture" { 
      "_pi"=P0101011111001110001110; "_po"=LLLLLLL; }
   "pattern 60": Call "load_unload" { 
      "test_so1"=HLHLLLLLLHLLHLHLLHLLLLHLLLHLHLLHHHHHH; "test_so2"=HHLLLLHLHHLHHHLHHLHLHHLLHLHLLLHLHLLLH; 
      "test_si1"=1011111101010100100010100101101111010; "test_si2"=0000001000111001101010010100010011000; }
   Call "multiclock_capture" { 
      "_pi"=P1010101010100111000010; "_po"=HHLLLHL; }
   "pattern 61": Call "load_unload" { 
      "test_so1"=LLLLLLLLHLHHLLLLLHHHHLLHLHHLLHHLLLHHL; "test_so2"=LLLHHHHLLLHHHLLHHLHLHHLHLHLLHHLLHHLHH; 
      "test_si1"=0010000111110111101010011001101001000; "test_si2"=0010110101101111100001110010101111101; }
   Call "multiclock_capture" { 
      "_pi"=P0000001000011101111110; "_po"=HLHLLLL; }
   "pattern 62": Call "load_unload" { 
      "test_so1"=LLHLHLLHHHHHHLLLLLLHHLLLHLHLLHHLLHLLH; "test_so2"=HLLHHHLHLLHLHHHHHLLLLHHHLLHLHLHHHHHLH; 
      "test_si1"=0001110110101100000011100001100101100; "test_si2"=0100001111000001110111001111010110110; }
   Call "multiclock_capture" { 
      "_pi"=P1101010101000000000000; "_po"=LHLHLLL; }
   "pattern 63": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLHHLLLLLLLLLLLLLLLLLLLLLLL; "test_so2"=LLLHHHLLLLHLHLLLLHHLLLLLLLLLLLLLLLLLL; 
      "test_si1"=0110010011110010010000010001111100100; "test_si2"=1010111010010101101011010100100100001; }
   Call "multiclock_capture" { 
      "_pi"=P0011111111101110011010; "_po"=LLHLHLH; }
   "pattern 64": Call "load_unload" { 
      "test_so1"=HLHLHHLLHHHHLLHLHLHHLHHLLLLHHLHHLLHLL; "test_so2"=LLLLLLLHHHLHLHLHHLHLHHLHLHLLHLLHHLLLH; 
      "test_si1"=1100100111100001100010100011111001000; "test_si2"=0101110100110101101011101001011000000; }
   Call "multiclock_capture" { 
      "_pi"=P1001111111110111011000; "_po"=LLLLLHL; }
   "pattern 65": Call "load_unload" { 
      "test_so1"=HHLLHLLHHHHLLLLHHLLLHLHHLLHHHHHLHLHLL; "test_so2"=LHHLLLHLLHHHLHLHHLHLHHHLHLLHLHHLHLLLL; 
      "test_si1"=1100110001100000110110010101000101100; "test_si2"=1011011101110000100001011000011001101; }
   Call "multiclock_capture" { 
      "_pi"=P1001101010110101100110; "_po"=HLHLHHH; }
   "pattern 66": Call "load_unload" { 
      "test_so1"=HHLLHLLLHHLHLLLLHHLHHHHLLHLHLLLHLHLLL; "test_so2"=LLLHHHHLHLHHLLLLHLLLLHLHHLLLLHHLHLLLH; 
      "test_si1"=0110111000100111001110000110100001100; "test_si2"=1100010011010001110101101011101011011; }
   Call "multiclock_capture" { 
      "_pi"=P0111001111100011011000; "_po"=LLLLHLH; }
   "pattern 67": Call "load_unload" { 
      "test_so1"=LHLLLLLLLHLLLHHHLLHLHHHHLHHHLHLLLHLLL; "test_so2"=LHLHHHLHLLLHLLLHHHLHLHHLHLHHHLHLHHHLH; 
      "test_si1"=1101110001000001011110001101000011001; "test_si2"=1000110110110001100011010111011010110; }
   Call "multiclock_capture" { 
      "_pi"=P1011101110110001101000; "_po"=LLLLHHH; }
   "pattern 68": Call "load_unload" { 
      "test_so1"=HHHLLHLLLHLLLLLHLHHLHLLHHHLHHHHHLLHHH; "test_so2"=LHHHHHHHHLHHLLLHHLLLHHLHLHHHLHHLHLHHL; 
      "test_si1"=0010111010010011100111100110111011001; "test_si2"=0010101111010101101001010111110010111; }
   Call "multiclock_capture" { 
      "_pi"=P0011101100110010010000; "_po"=LLHLLLL; }
   "pattern 69": Call "load_unload" { 
      "test_so1"=LHLLLHHLLLHHLLLLLLLLHHHHLHHLHLLHLLHHH; "test_so2"=LLHHHHHHHLLHHHLHHLHLHLLHLLLLLHLLHLHHH; 
      "test_si1"=0000001010001101011000011111000001111; "test_si2"=0100001010110010000100100101101100010; }
   Call "multiclock_capture" { 
      "_pi"=P0100100011010111010110; "_po"=HHLHLLL; }
   "pattern 70": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHH; "test_so2"=LLLHHHLLLLLLLLHHHLLHLLHHLLLLLLLLLLLLL; 
      "test_si1"=0000010100011010110000111110000011110; "test_si2"=1010100101110101100011001011011000100; }
   Call "multiclock_capture" { 
      "_pi"=P0010010001101011001010; "_po"=HLHHHLH; }
   "pattern 71": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHL; "test_so2"=LLLHHHLLLLLHHLHHLLLHLLHLLLLLLLLLLLLLL; 
      "test_si1"=0101010101001111110110101110110000001; "test_si2"=0101001111111101100011011100111000100; }
   Call "multiclock_capture" { 
      "_pi"=P1100011001111011111010; "_po"=HHLLLLL; }
   "pattern 72": Call "load_unload" { 
      "test_so1"=LHLHLLLLHLLLLLLLLHLHHLLHHHHLHHLLLLLLH; "test_so2"=LHLHLLHHHHHHLHLHHLLLLLLHHHLHLHHLLHLLL; 
      "test_si1"=1010101100111000001101010111101011001; "test_si2"=1011011111101011000110111001110001000; }
   Call "multiclock_capture" { 
      "_pi"=P1110001110111101101100; "_po"=LLHLHHH; }
   "pattern 73": Call "load_unload" { 
      "test_so1"=HLHLHHLLLHHLHLLLLLHHHLHLLHHHHLHLHHLHH; "test_so2"=LLLHHHHHHLHLLLHHLLLHHLHHHLLHHHLLLHLLL; 
      "test_si1"=0000100111010101001101100111101011010; "test_si2"=0101001011101010111000111001101011101; }
   Call "multiclock_capture" { 
      "_pi"=P1010011010000000111000; "_po"=HLLLLLL; }
   "pattern 74": Call "load_unload" { 
      "test_so1"=LHLHLLHLHLHLLHLHLLHLLHLHHLLLLHLHLLHHL; "test_so2"=HHHLLHHLHHHLLLHLHLLLLLHHHLHLLLHLHHHLH; 
      "test_si1"=0100110000000000101100000001011000001; "test_si2"=1000000011001001000100111001011110110; }
   Call "multiclock_capture" { 
      "_pi"=P0100011101110110010010; "_po"=LHLLHLH; }
   "pattern 75": Call "load_unload" { 
      "test_so1"=HLLHLLLLLLLLLLLLLLHLLHHHLLLHLLHLLHHHH; "test_so2"=LLLLLLLLHHLLHLLHLLLHLHHHHLLHHHHHHHLLL; 
      "test_si1"=1001100000000001011000000010110000110; "test_si2"=0000100110010010001001110010111101100; }
   Call "multiclock_capture" { 
      "_pi"=P0100001111110011001000; "_po"=LHLLLHL; }
   "pattern 76": Call "load_unload" { 
      "test_so1"=LLHLLLLLLLLLLLLLLHLHLLLHLLHLHLLLLLHLL; "test_so2"=LLLHHHLHHLLHHLHLLLHLHLHHLLHHLHHHLHHLH; 
      "test_si1"=0011000000000000110000000101100000101; "test_si2"=0001011100100100010000100101111011001; }
   Call "multiclock_capture" { 
      "_pi"=P1010001110000001100000; "_po"=LLLLLLL; }
   "pattern 77": Call "load_unload" { 
      "test_so1"=LLHHLLLHLLLLLLLLHHLLLHHHLHLHHLLLLLHHH; "test_so2"=LLLHHHHHLLHLLHLLLHLLLLHLLHLHHHHLHHLLH; 
      "test_si1"=0110000000000101100000001011000001110; "test_si2"=0010011001011000101001001011110010010; }
   Call "multiclock_capture" { 
      "_pi"=P0101001010100000110100; "_po"=HLHLLLL; }
   "pattern 78": Call "load_unload" { 
      "test_so1"=LHHLHLLHLLLLLHLHHHHHLHHHHLHHHHLLLHHHL; "test_so2"=LLLHHHLLHLLHHLLLHLHLLHLLHLHHHHLLHLLHL; 
      "test_si1"=1100000000000010000000010110000010100; "test_si2"=0100100010010001001110010111101100100; }
   Call "multiclock_capture" { 
      "_pi"=P0010101001110000011110; "_po"=HHLLLHL; }
   "pattern 79": Call "load_unload" { 
      "test_so1"=LLLLHLLLLLLLLLHLLHHHLLLLLHHLHHLLHLHLL; "test_so2"=LHLHHHLLHLLHHLLHLLHHHHLHLLLLLLHHHLHLH; 
      "test_si1"=1101111110101100010101011110110010101; "test_si2"=1001010000110100101101110100010000101; }
   Call "multiclock_capture" { 
      "_pi"=P1100001101110110010100; "_po"=LLLLHHH; }
   "pattern 80": Call "load_unload" { 
      "test_so1"=HHLHHLLLLHLLHHLLLHLHHLHLHHHLHHLLHLHHH; "test_so2"=LLLHHHLLLLHHHHLLHLHHHLHHLHLLLHLLLHLLH; 
      "test_si1"=1001111001001111100110001100010110001; "test_si2"=0100101101011111111001001011011001110; }
   Call "multiclock_capture" { 
      "_pi"=00100111110110100101100; "_po"=LHLLLHL; }
   "pattern 81": Call "load_unload" { 
      "test_so1"=HLLHHHHLLHLLHHHHHLLHHLLLHHLLLHLHHLLLH; "test_so2"=LHLLHLHHLHLHHHHHHHHLLHLLHLHHLHHLLHHHL; 
      "test_si1"=0011110010010001001100010111100100010; "test_si2"=1011001110111111110010010110110000111; }
   Call "multiclock_capture" { 
      "_pi"=P1010011110011010010110; "_po"=LHHLHLH; }
   "pattern 82": Call "load_unload" { 
      "test_so1"=LLHHHLLLLLHLLLLLLLHHLHHLLHHHHLLHLHHLL; "test_so2"=HLLLLLHHHHHHHHHHHHLLHLLHLHHHLHLLHHLLH; 
      "test_si1"=0100110100100000011111000111101011011; "test_si2"=1101100011000110100011001111010000100; }
   Call "multiclock_capture" { 
      "_pi"=P0000001100110001100010; "_po"=LLLLHLH; }
   "pattern 83": Call "load_unload" { 
      "test_so1"=HLLHLHLHLLHLLLLLLHHLHHLHHLLLLHLHLLHHH; "test_so2"=LHHHHHLLHLLLLHHLHLLLLLLLHHHHHHLLHLHLL; 
      "test_si1"=1100010111111010101001011101001011001; "test_si2"=1001010010010001110011010100101000100; }
   Call "multiclock_capture" { 
      "_pi"=P0101011011100110101010; "_po"=HLLLHHH; }
   "pattern 84": Call "load_unload" { 
      "test_so1"=HHLLLLLLHHHLHLHHLLHLHLHLHHLHLLHLHHLLH; "test_so2"=LHLLLLLHHHLHHLLHHHLHLLLHLHLLHLHLLHLLL; 
      "test_si1"=1010111111010101001011101001011011110; "test_si2"=1000110010000101101011100011100101111; }
   Call "multiclock_capture" { 
      "_pi"=P1010101010011100110100; "_po"=HLLLHHH; }
   "pattern 85": Call "load_unload" { 
      "test_so1"=LLLLLLLLHLHHLHLHLLLHHHHHHLLHLLHLHHHHL; "test_so2"=LLHHHHLLHLLLLHLHHLHLHHHLLHLLLLLHLLLLL; 
      "test_si1"=1111110001010001101011110111001011000; "test_si2"=0001000001110101010011000000010100110; }
   Call "multiclock_capture" { 
      "_pi"=P0100011110110010110100; "_po"=LLLLLHL; }
   "pattern 86": Call "load_unload" { 
      "test_so1"=HHHHHLLLHLHLLLLLLLHLHHLLLHHHHHLHLLHLL; "test_so2"=LLHHLLLLLHHHLHLHLLLLLLLLLLLLHHLHHHLLL; 
      "test_si1"=1111100010110000110111100110010110000; "test_si2"=0011100011101010100110000000101001101; }
   Call "multiclock_capture" { 
      "_pi"=P0110001111110011001110; "_po"=LHHLLHL; }
   "pattern 87": Call "load_unload" { 
      "test_so1"=HHHHHLLLHLHHLLLLLHLHHHHHLHHLLHLHHHHLL; "test_so2"=LLLHHHLLHLHLHLHLHLLHHLLLLLLHLLHLHHHLH; 
      "test_si1"=0000110100110000100110101011100111000; "test_si2"=0100010110110001100011000001010011101; }
   Call "multiclock_capture" { 
      "_pi"=P1101011000111001010110; "_po"=HLLLLLL; }
   "pattern 88": Call "load_unload" { 
      "test_so1"=LLLHLLLLLHHLLLLLHLLLHLLHHHLLLHLLLLHLL; "test_so2"=LHHLLLHHLHHHLLLHHLLLHHLLLLLHLHLLHLLLH; 
      "test_si1"=1110011000100010000010100000000101001; "test_si2"=1001111100111101101011000010011011100; }
   Call "multiclock_capture" { 
      "_pi"=P0010111010100010011110; "_po"=HLLLHHH; }
   "pattern 89": Call "load_unload" { 
      "test_so1"=HHHLLHHLLLHLLLHLLLLLHLHHLLLLLLLHHLHLH; "test_so2"=HLLLLLHHLHHHHHLHHLHLHHLLLLHLLHHLHHHLL; 
      "test_si1"=0011000000010001001110110111000001011; "test_si2"=0011101000011110001001000100100011111; }
   Call "multiclock_capture" { 
      "_pi"=P0001001111110011111110; "_po"=LHHLLLL; }
   "pattern 90": Call "load_unload" { 
      "test_so1"=LLHHLLLLLLLHLLLLLLHHHLHLLHHHLLLLHLHHH; "test_so2"=HLHHHHLLHLLHLHHLLLLLLLLLLHLHLLLLHHHHH; 
      "test_si1"=0110000000111010011101100110000010111; "test_si2"=0101000000011100010010001001000111110; }
   Call "multiclock_capture" { 
      "_pi"=P1110101011100111111110; "_po"=HHLLLLL; }
   "pattern 91": Call "load_unload" { 
      "test_so1"=LHHLLLLHLHHHLLLLLHHHLHLHLHHLLLLLHLHHH; "test_so2"=HHLHHHLLLLLHLHLLLLLLLLLLHLLHHLLHHHHHL; 
      "test_si1"=0011110000101101110000100011001110111; "test_si2"=1011100000011101110111010010011111010; }
   Call "multiclock_capture" { 
      "_pi"=P1011001111101101011010; "_po"=LHHLHLH; }
   "pattern 92": Call "load_unload" { 
      "test_so1"=LLHHHHLLLLHLHHLHHHLLLLHHLLHHLLHHHLHHH; "test_so2"=HHLHHHLLHLLHHHLHHHLHHHLHLLHLHHHHHHLHL; 
      "test_si1"=0111100001011011100001010110011101111; "test_si2"=0110100000010101101010100100110110100; }
   Call "multiclock_capture" { 
      "_pi"=P1101100111110110011000; "_po"=LHHHLLL; }
   "pattern 93": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHH; "test_so2"=LLLHHHLLLLHLHLLHHLHLHHLHHLLLLLLLLLLLL; 
      "test_si1"=0000110011101110001001011011110000111; "test_si2"=1110000001000000000000001001111001110; }
   Call "multiclock_capture" { 
      "_pi"=P1010101101100101011000; "_po"=LHHLHLH; }
   "pattern 94": Call "load_unload" { 
      "test_so1"=LHLHLLLLHHLHHHHLLLLHHLHLHLHHHLLLLLHHH; "test_so2"=LHHHHHLLLLLLHLLLLLLLLHLLHLHLLHHLHLLLL; 
      "test_si1"=0001100111011100010010110111100001110; "test_si2"=1100100010000001000010010011110011100; }
   Call "multiclock_capture" { 
      "_pi"=P1101010110110010011100; "_po"=LLLHHLH; }
   "pattern 95": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL; "test_so2"=LLLHHHLLLLHLLLLHLLLLHLLHHLLLLLLLLLLLL; 
      "test_si1"=0011001110111000100101101111000011100; "test_si2"=1000000100000000010000100111100111000; }
   Call "multiclock_capture" { 
      "_pi"=P1110101011011001011110; "_po"=HHLLHLH; }
   "pattern 96": Call "load_unload" { 
      "test_so1"=LHHHHHLLLHHHHLLLHLLLLHLHHHHHHHLLHHHLL; "test_so2"=LLLHHHLHLLLLLLLLLHLLLLHLLLLLLLLHHHLLL; 
      "test_si1"=1100101000001001001010100101010011001; "test_si2"=0111100010111100010111100110000001011; }
   Call "multiclock_capture" { 
      "_pi"=01001111011100111111111; "_po"=HHHLLHL; }
   "pattern 97": Call "load_unload" { 
      "test_so1"=HHLLHLHLLLLLHLLHLLHLHLHLLHLHLHLLHHLLH; "test_so2"=LHHHHLLLHLHHHHLLLHLHHHHLLHHLLLLLLHLHH; 
      "test_si1"=1001010000011100010101000111101011011; "test_si2"=1111000101111000101110111101000010111; }
   Call "multiclock_capture" { 
      "_pi"=P1100111100100011101110; "_po"=LHHLHHH; }
   "pattern 98": Call "load_unload" { 
      "test_so1"=HLLHLLLLLLHHLLLLLHLHHLHHLHHHHLHLHHLHH; "test_so2"=HHLHLLLHLHHHLLLLHLLLLLHHHHLHHLLLHHLLH; 
      "test_si1"=1010100011110001000011000100001111111; "test_si2"=1110110100001000011101110100100010011; }
   Call "multiclock_capture" { 
      "_pi"=P0001001000010011100000; "_po"=HLHLHHH; }
   "pattern 99": Call "load_unload" { 
      "test_so1"=HLLLLLLLHHHLLLLHLHHHHHLHLHLLHHHHHHHHH; "test_so2"=LHLHHHHLLLLLHLLLLHHHLHHHLHLLHLLLHLLHH; 
      "test_si1"=1010110110100000101101111111010100111; "test_si2"=1100101001100101101000101001010000001; }
   Call "multiclock_capture" { 
      "_pi"=P1110111111110111000000; "_po"=LHLLHHH; }
   "pattern 100": Call "load_unload" { 
      "test_so1"=LLLLLLLLLHLHLLLLLLHLLHHLHHHHLLLHLLHHH; "test_so2"=LHHHLHHLLHHLHHLHHLHLLHHLHLLHHHLLHLLHL; 
      "test_si1"=1010011100000100110000001001100010010; "test_si2"=1000110010111110001010010010110000101; }
   Call "multiclock_capture" { 
      "_pi"=P0111001000010101010100; "_po"=HLLLHHH; }
   "pattern 101": Call "load_unload" { 
      "test_so1"=HLHLHHHHLLLLLHLLHLHHLHHHHLHLLHLLHHHHL; "test_so2"=LHHHHHLHHLHHHHHLLLHLHLLHLLHLHHLLLLHLH; 
      "test_si1"=0100111000000101100000010011000101100; "test_si2"=0001010101111100001010100101101001011; }
   Call "multiclock_capture" { 
      "_pi"=P0011101000101010111010; "_po"=HLLLLLL; }
   "pattern 102": Call "load_unload" { 
      "test_so1"=LHLLHLLLLLLHLHLHHLLLLHHLLLHHLLLHLHHLL; "test_so2"=LHLHHHHLHLHHHHLLLLHLHLHLLHLHHLHLLHHLH; 
      "test_si1"=1001110000010000100000100110001011100; "test_si2"=0010011011101000001000001011010010110; }
   Call "multiclock_capture" { 
      "_pi"=P0001111000010101001100; "_po"=HLHLLHL; }
   "pattern 103": Call "load_unload" { 
      "test_so1"=HLHLLLLLLLHHLLLLHHHHLLLHLHHLHHHLHHHLL; "test_so2"=LLLLLHLHHHHLHLLLLLHLLLLLHLHHLHLLHHLLL; 
      "test_si1"=0011100000110010000001001111101011001; "test_si2"=0101000111110000010110010110100101101; }
   Call "multiclock_capture" { 
      "_pi"=P1100111000001010000010; "_po"=HHLLLLL; }
   "pattern 104": Call "load_unload" { 
      "test_so1"=LLHHHLLHLHHHLLLLLLLLHLHHLLLLLHLHLLHLH; "test_so2"=LHHHLLLHHHHHHLLLLHLHHHLHLHHHLLLHLHHLH; 
      "test_si1"=0111000001110100000010010111101011010; "test_si2"=1001101111100000100100101101001011010; }
   Call "multiclock_capture" { 
      "_pi"=P0110011100000101000100; "_po"=LLLLHLH; }
   "pattern 105": Call "load_unload" { 
      "test_so1"=HLHHHLLLLHHHLHLLLHHHHLLLHLLLLHLHLLHLL; "test_so2"=LLHHLHHHHHHLLLLLHLLHLLHLHHLHHLHLHHLHL; 
      "test_si1"=0001110010110001001111000110011011001; "test_si2"=0000001100110100011010011010000010010; }
   Call "multiclock_capture" { 
      "_pi"=00111010000001100010110; "_po"=HLLHLLL; }
   "pattern 106": Call "load_unload" { 
      "test_so1"=LLLHHHLLHLHHLLLHLLHHHHLLLHHLLHHLHHLLH; "test_so2"=LLLLLLHHLLHHLHLLLHHLHLLHHLHLLLLLHLLHL; 
      "test_si1"=1100010100111011000101110111101100010; "test_si2"=0000001100011101100111110100010000010; }
   Call "multiclock_capture" { 
      "_pi"=00111110110010000101111; "_po"=LHLHLHL; }
   "pattern 107": Call "load_unload" { 
      "test_so1"=HHLLLHLHLLHHHLHHLLLHLHHHLHHHHLHHLLLHL; "test_so2"=LLLLLLHHLLLHHHLHHLLHHHHHLHLLLHLLLLLHL; 
      "test_si1"=1111011000101111100000001000010111101; "test_si2"=0011101001001110011100101000110101111; }
   Call "multiclock_capture" { 
      "_pi"=01111100101010110110011; "_po"=LHHHLHL; }
   "pattern 108": Call "load_unload" { 
      "test_so1"=HHHHLHHLLLHLHHHHHLLLLLLLHLLLLHLHHHHLH; "test_so2"=LLHHHLHLLHLLHHHLLHHHLLHLHLLLHHLHLHHHH; 
      "test_si1"=1110110001010011000000000000100111111; "test_si2"=0110000010011100111001010001101000110; }
   Call "multiclock_capture" { 
      "_pi"=P1111111010111011001100; "_po"=HHHLLHL; }
   "pattern 109": Call "load_unload" { 
      "test_so1"=LLLLLLLLHLHHLLLLLHHHLHHHLLLHLHLHHHHHH; "test_so2"=LHLLLLLHLHLHHHLLHHHLHLLHLLHLLLHLLHLLH; 
      "test_si1"=0100100111001010010111100111101011010; "test_si2"=1011101010011001000011000110001010110; }
   Call "multiclock_capture" { 
      "_pi"=P0111111011100101100010; "_po"=HHHLHLH; }
   "pattern 110": Call "load_unload" { 
      "test_so1"=LHLLHLLHHHLLHLHLLHLHHHHHLHHHHLHLHHLHL; "test_so2"=HLLLLLLHHHLHLLLHLLLLLLLLLHHLHLHLHLHHL; 
      "test_si1"=1101111110000011001001011110101011011; "test_si2"=1101011010011110101010011000000010100; }
   Call "multiclock_capture" { 
      "_pi"=P0011111011110110010000; "_po"=HLLLHHH; }
   "pattern 111": Call "load_unload" { 
      "test_so1"=HHLHHLLLLLLHLLHHLLHLHLHLHHHHLHLHLLHHH; "test_so2"=LLHLLLLHLHLHHHHLHLHLHHLHHLLLLLLLHHLLL; 
      "test_si1"=1011111100010001110010110101110010110; "test_si2"=1001000100011101010100110000000101001; }
   Call "multiclock_capture" { 
      "_pi"=P0001111001010011001000; "_po"=HHLLHHH; }
   "pattern 112": Call "load_unload" { 
      "test_so1"=HLHHHLLLLLHHLLLLLHLLHLLLLHLHHHLLHLLHL; "test_so2"=HHHLLLHLHHLHHHLHLHLHLLHHLLLLHLLHHHLHH; 
      "test_si1"=0111111000101100100101111011100101100; "test_si2"=0000101000111010101001000100001010011; }
   Call "multiclock_capture" { 
      "_pi"=P1000110100111101100000; "_po"=LHLHLLL; }
   "pattern 113": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLHHLLHLLLLLLLLLLLLLLLLLLLL; "test_so2"=LLLHHHLLLLLLLHHLHLLLLLHHHLLLLLLLLLLLL; 
      "test_si1"=1110110110010100011101011110001001011; "test_si2"=1100100110010000101001101101001100010; }
   Call "multiclock_capture" { 
      "_pi"=P1010111110010101101110; "_po"=LHLLHHH; }
   "pattern 114": Call "load_unload" { 
      "test_so1"=LLLLLHLHLLHHLHLLLHHLLHLLHHHLHHHLHLHHH; "test_so2"=LHHLLLLHHHLHLLLLHLLLLLHLHHLHHLHHHLLHH; 
      "test_si1"=1101101100101100111010111100010010110; "test_si2"=1000111100100101101011001111101001001; }
   Call "multiclock_capture" { 
      "_pi"=P1101011011111010100110; "_po"=HLLLHHH; }
   "pattern 115": Call "load_unload" { 
      "test_so1"=LLHLLHLLLLHLHHLLHHLHHLHLHHLLLLLLHLHHL; "test_so2"=LLHLLLHLHHHLLHLHHLHLHHLLHHHHHLHLHHLLL; 
      "test_si1"=1101111111001111101000100110101100110; "test_si2"=1110111111010101101011001111101100101; }
   Call "multiclock_capture" { 
      "_pi"=P1100011010001000101000; "_po"=HLHLHHH; }
   "pattern 116": Call "load_unload" { 
      "test_so1"=LLHLLLLLHHLLHHHHHLLHLLHHLHHHLHHHLLHHL; "test_so2"=LHLLHHHHHHLHLHLHHLHLHHLLHHHHHLHHLHLLL; 
      "test_si1"=0101100110000100000101111000101011011; "test_si2"=1111010111111001010111010000100100010; }
   Call "multiclock_capture" { 
      "_pi"=P0000101010101101011010; "_po"=HLHLHLH; }
   "pattern 117": Call "load_unload" { 
      "test_so1"=LHLHHLHLLLLHLHLLLLLHLHLLHLLHLHLHLLHHH; "test_so2"=LHHHHHLHHLHHHLLHLHLHHHLHLLLLHLLHLLLHL; 
      "test_si1"=1011001100001000001011110001010001111; "test_si2"=1100101111110111011110100001000000100; }
   Call "multiclock_capture" { 
      "_pi"=P1000010101010110001000; "_po"=LHLHHHH; }
   "pattern 118": Call "load_unload" { 
      "test_so1"=LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLHH; "test_so2"=LLLHHHLLLLLLHLLHHHHHHHHLHLLLLLLLLLLLL; 
      "test_si1"=1000101110000110001010111100101010100; "test_si2"=0100101001110000110001101111001101011; }
   Call "multiclock_capture" { 
      "_pi"=P0110111101011110001010; "_po"=LHLLLHL; }
   "pattern 119": Call "load_unload" { 
      "test_so1"=LLLHLHLLHLLLLLLLLLLHHLHLHHLHLHHLHLHLL; "test_so2"=LHHHLHHLLHHHHLLLHHLLHLHLHHHHHLHHHHLHL; 
      "test_si1"=0001011100001100010101111001010101000; "test_si2"=1010100011100010010100011110011010111; }
   Call "multiclock_capture" { 
      "_pi"=P1011011110101111010100; "_po"=LHHLHLH; }
   "pattern 120": Call "load_unload" { 
      "test_so1"=LHLHHHHHLLLLLLLLLHLLLHHLHLLHLLLHLHLLL; "test_so2"=LHHHLHLHHHHLHLHLLHLHLHLHHHHLHHHLHLHHH; 
      "test_si1"=1100001110001110110110101100100011010; "test_si2"=1010000001000001010010010001111001100; }
   Call "multiclock_capture" { 
      "_pi"=P1111011000100010000100; "_po"=HHHLHHH; }
   "pattern 121": Call "load_unload" { 
      "test_so1"=LLLLHHLLLLLLLLLLLHLLHLLHHHLHLHLLHHLHL; "test_so2"=LHLLLHLLHHLLHLLHLHLLHHLHLLHLLHHLLHHLH; 
      "test_si1"=1000011100011101101101011001000110100; "test_si2"=0110000010000100011000100011110011001; }
   Call "multiclock_capture" { 
      "_pi"=P0111101100010001010010; "_po"=LHHLLHL; }
   "pattern 122": Call "load_unload" { 
      "test_so1"=LLLLHLLLLLHHHHLHHLHLHLHLHLLHHHLHHLHLL; "test_so2"=LHLHHHLHLLLLHHLLLHHLLHHLLHLLLHLLHHLHL; 
      "test_si1"=0000111000110111011010110010001011000; "test_si2"=1101010100011111110101000111100010011; }
   Call "multiclock_capture" { 
      "_pi"=P0011111110011000111000; "_po"=LLLLHLH; }
   "pattern 123": Call "load_unload" { 
      "test_so1"=LLLLHLLLLHHHLHHHLHHLHLLLLLHLHHLHLLHLL; "test_so2"=HHLLLLHLLHLHHHHHHHLHLHLLLHHHHLLLHLHLH; 
      "test_si1"=1111000111100000001000110111101011010; "test_si2"=0101111110001111110011100010000000100; }
   Call "multiclock_capture" { 
      "_pi"=P0011001100110001110010; "_po"=LLLLLHL; }
   "pattern 124": Call "load_unload" { 
      "test_so1"=HHHHHLLHHHHLLLLLLLLHLLHLHLLLLHLHLLHLL; "test_so2"=LLHHHHHHLLHHLHHLLLLLLLLLLLLLLLHLLLHLL; 
      "test_si1"=0000111001010110001100101010101111011; "test_si2"=0101111010011111001110101001001001011; }
   Call "multiclock_capture" { 
      "_pi"=P1011011001101101000010; "_po"=HLLLLLL; }
   "pattern 125": Call "load_unload" { 
      "test_so1"=LLLLHHHLLHLHLHHLLLHHLLHHHLHLHLHLLLHHH; "test_so2"=LLHLLLLHLHLHLHHHLLHHHLHLHLLHLLHLLHLHH; 
      "test_si1"=0001110010100010011001010101011111111; "test_si2"=1011110100001110011101010010011010110; }
   Call "multiclock_capture" { 
      "_pi"=P0101101000110110100000; "_po"=HLHLHLH; }
   "pattern 126": Call "load_unload" { 
      "test_so1"=LLLHHHLLHLHLLLHLLHHLLHLLLHLHLHHHHHHHH; "test_so2"=LHLHHHHLHLLLHHHLLHHHLHLHLLHLLHHLHLHHL; 
      "test_si1"=1010100110010001111111101001101101000; "test_si2"=0110011101010011100111010011110011101; }
   Call "multiclock_capture" { 
      "_pi"=P1100001001110111011100; "_po"=HLHLLHL; }
   "pattern 127": Call "load_unload" { 
      "test_so1"=HLLLLLHLLLHLLLLHHHHLHHLHHLHLLHHHHLHLL; "test_so2"=LHHHHHHHLLLHLLHHHLLHHHLHLLHHHHLLHHHLH; 
      "test_si1"=0010000111010110110010001001011011010; "test_si2"=1001111110100111000111110000110000011; }
   Call "multiclock_capture" { 
      "_pi"=P0100011110001001011110; "_po"=LLLLHLH; }
   "end 127 unload": Call "load_unload" { 
      "test_so1"=LLHLLLLHHHLHLHHLHHLLHLLHHLLHLHHLHHLLL; "test_so2"=LLLLLLHHHHHLLHHHLLLHHHHHLLLLHHLLHLLHH; }
}

// Patterns reference 388 V statements, generating 5032 test cycles
