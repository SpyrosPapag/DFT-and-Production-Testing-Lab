// Verilog pattern output written by  TetraMAX (TM)  B-2008.09-SP2-i081128_181834 
// Date: Wed Jul  6 12:07:03 2011
// Module tested: c7552

//     Uncollapsed Stuck Fault Summary Report
// -----------------------------------------------
// fault class                     code   #faults
// ------------------------------  ----  ---------
// Detected                         DT       4552
// Possibly detected                PT          0
// Undetectable                     UD          0
// ATPG untestable                  AU          0
// Not detected                     ND       2336
// -----------------------------------------------
// total faults                              6888
// test coverage                            66.09%
// -----------------------------------------------
// 
//            Pattern Summary Report
// -----------------------------------------------
// #internal patterns                          10
//     #basic_scan patterns                    10
// -----------------------------------------------
// 
// There are no rule fails
// There are no clocks
// There are no constraint ports
// There are no equivalent pins
// There are no net connections

`timescale 1 ns / 1 ns

//
// --- NOTE: Remove the comment to define 'tmax_iddq' to activate processing of IDDQ events
//     Or use '+define+tmax_iddq' on the verilog compile line
//
//`define tmax_iddq

module AAA_tmax_testbench_1_16 ;
   parameter NAMELENGTH = 200; // max length of names reported in fails
   integer nofails, bit, pattern, lastpattern;
   integer error_banner; // flag for tracking displayed error banner
   integer loads;        // number of load_unloads for current pattern
   integer patm1;        // pattern - 1
   integer patp1;        // pattern + lastpattern
   integer prev_pat;     // previous pattern number
   integer report_interval; // report pattern progress every Nth pattern
   integer verbose;      // message verbosity level
   parameter NINPUTS = 207, NOUTPUTS = 108;
   wire [0:NOUTPUTS-1] PO; reg [0:NOUTPUTS-1] ALLPOS, XPCT, MASK;
   reg [0:NINPUTS-1] PI, ALLPIS;
   reg [0:8*(NAMELENGTH-1)] POnames [0:NOUTPUTS-1];
   event IDDQ;

   wire N1;
   wire N5;
   wire N9;
   wire N12;
   wire N15;
   wire N18;
   wire N23;
   wire N26;
   wire N29;
   wire N32;
   wire N35;
   wire N38;
   wire N41;
   wire N44;
   wire N47;
   wire N50;
   wire N53;
   wire N54;
   wire N55;
   wire N56;
   wire N57;
   wire N58;
   wire N59;
   wire N60;
   wire N61;
   wire N62;
   wire N63;
   wire N64;
   wire N65;
   wire N66;
   wire N69;
   wire N70;
   wire N73;
   wire N74;
   wire N75;
   wire N76;
   wire N77;
   wire N78;
   wire N79;
   wire N80;
   wire N81;
   wire N82;
   wire N83;
   wire N84;
   wire N85;
   wire N86;
   wire N87;
   wire N88;
   wire N89;
   wire N94;
   wire N97;
   wire N100;
   wire N103;
   wire N106;
   wire N109;
   wire N110;
   wire N111;
   wire N112;
   wire N113;
   wire N114;
   wire N115;
   wire N118;
   wire N121;
   wire N124;
   wire N127;
   wire N130;
   wire N133;
   wire N134;
   wire N135;
   wire N138;
   wire N141;
   wire N144;
   wire N147;
   wire N150;
   wire N151;
   wire N152;
   wire N153;
   wire N154;
   wire N155;
   wire N156;
   wire N157;
   wire N158;
   wire N159;
   wire N160;
   wire N161;
   wire N162;
   wire N163;
   wire N164;
   wire N165;
   wire N166;
   wire N167;
   wire N168;
   wire N169;
   wire N170;
   wire N171;
   wire N172;
   wire N173;
   wire N174;
   wire N175;
   wire N176;
   wire N177;
   wire N178;
   wire N179;
   wire N180;
   wire N181;
   wire N182;
   wire N183;
   wire N184;
   wire N185;
   wire N186;
   wire N187;
   wire N188;
   wire N189;
   wire N190;
   wire N191;
   wire N192;
   wire N193;
   wire N194;
   wire N195;
   wire N196;
   wire N197;
   wire N198;
   wire N199;
   wire N200;
   wire N201;
   wire N202;
   wire N203;
   wire N204;
   wire N205;
   wire N206;
   wire N207;
   wire N208;
   wire N209;
   wire N210;
   wire N211;
   wire N212;
   wire N213;
   wire N214;
   wire N215;
   wire N216;
   wire N217;
   wire N218;
   wire N219;
   wire N220;
   wire N221;
   wire N222;
   wire N223;
   wire N224;
   wire N225;
   wire N226;
   wire N227;
   wire N228;
   wire N229;
   wire N230;
   wire N231;
   wire N232;
   wire N233;
   wire N234;
   wire N235;
   wire N236;
   wire N237;
   wire N238;
   wire N239;
   wire N240;
   wire N242;
   wire N245;
   wire N248;
   wire N251;
   wire N254;
   wire N257;
   wire N260;
   wire N263;
   wire N267;
   wire N271;
   wire N274;
   wire N277;
   wire N280;
   wire N283;
   wire N286;
   wire N289;
   wire N293;
   wire N296;
   wire N299;
   wire N303;
   wire N307;
   wire N310;
   wire N313;
   wire N316;
   wire N319;
   wire N322;
   wire N325;
   wire N328;
   wire N331;
   wire N334;
   wire N337;
   wire N340;
   wire N343;
   wire N346;
   wire N349;
   wire N352;
   wire N355;
   wire N358;
   wire N361;
   wire N364;
   wire N367;
   wire N382;
   wire N241_I;
   wire N387;
   wire N388;
   wire N478;
   wire N482;
   wire N484;
   wire N486;
   wire N489;
   wire N492;
   wire N501;
   wire N505;
   wire N507;
   wire N509;
   wire N511;
   wire N513;
   wire N515;
   wire N517;
   wire N519;
   wire N535;
   wire N537;
   wire N539;
   wire N541;
   wire N543;
   wire N545;
   wire N547;
   wire N549;
   wire N551;
   wire N553;
   wire N556;
   wire N559;
   wire N561;
   wire N563;
   wire N565;
   wire N567;
   wire N569;
   wire N571;
   wire N573;
   wire N582;
   wire N643;
   wire N707;
   wire N813;
   wire N881;
   wire N882;
   wire N883;
   wire N884;
   wire N885;
   wire N889;
   wire N945;
   wire N1110;
   wire N1111;
   wire N1112;
   wire N1113;
   wire N1114;
   wire N1489;
   wire N1490;
   wire N1781;
   wire N10025;
   wire N10101;
   wire N10102;
   wire N10103;
   wire N10104;
   wire N10109;
   wire N10110;
   wire N10111;
   wire N10112;
   wire N10350;
   wire N10351;
   wire N10352;
   wire N10353;
   wire N10574;
   wire N10575;
   wire N10576;
   wire N10628;
   wire N10632;
   wire N10641;
   wire N10704;
   wire N10706;
   wire N10711;
   wire N10712;
   wire N10713;
   wire N10714;
   wire N10715;
   wire N10716;
   wire N10717;
   wire N10718;
   wire N10729;
   wire N10759;
   wire N10760;
   wire N10761;
   wire N10762;
   wire N10763;
   wire N10827;
   wire N10837;
   wire N10838;
   wire N10839;
   wire N10840;
   wire N10868;
   wire N10869;
   wire N10870;
   wire N10871;
   wire N10905;
   wire N10906;
   wire N10907;
   wire N10908;
   wire N11333;
   wire N11334;
   wire N11340;
   wire N11342;
   wire N241_O;

   // map PI[] vector to DUT inputs and bidis
   assign N1 = PI[0];
   assign N5 = PI[1];
   assign N9 = PI[2];
   assign N12 = PI[3];
   assign N15 = PI[4];
   assign N18 = PI[5];
   assign N23 = PI[6];
   assign N26 = PI[7];
   assign N29 = PI[8];
   assign N32 = PI[9];
   assign N35 = PI[10];
   assign N38 = PI[11];
   assign N41 = PI[12];
   assign N44 = PI[13];
   assign N47 = PI[14];
   assign N50 = PI[15];
   assign N53 = PI[16];
   assign N54 = PI[17];
   assign N55 = PI[18];
   assign N56 = PI[19];
   assign N57 = PI[20];
   assign N58 = PI[21];
   assign N59 = PI[22];
   assign N60 = PI[23];
   assign N61 = PI[24];
   assign N62 = PI[25];
   assign N63 = PI[26];
   assign N64 = PI[27];
   assign N65 = PI[28];
   assign N66 = PI[29];
   assign N69 = PI[30];
   assign N70 = PI[31];
   assign N73 = PI[32];
   assign N74 = PI[33];
   assign N75 = PI[34];
   assign N76 = PI[35];
   assign N77 = PI[36];
   assign N78 = PI[37];
   assign N79 = PI[38];
   assign N80 = PI[39];
   assign N81 = PI[40];
   assign N82 = PI[41];
   assign N83 = PI[42];
   assign N84 = PI[43];
   assign N85 = PI[44];
   assign N86 = PI[45];
   assign N87 = PI[46];
   assign N88 = PI[47];
   assign N89 = PI[48];
   assign N94 = PI[49];
   assign N97 = PI[50];
   assign N100 = PI[51];
   assign N103 = PI[52];
   assign N106 = PI[53];
   assign N109 = PI[54];
   assign N110 = PI[55];
   assign N111 = PI[56];
   assign N112 = PI[57];
   assign N113 = PI[58];
   assign N114 = PI[59];
   assign N115 = PI[60];
   assign N118 = PI[61];
   assign N121 = PI[62];
   assign N124 = PI[63];
   assign N127 = PI[64];
   assign N130 = PI[65];
   assign N133 = PI[66];
   assign N134 = PI[67];
   assign N135 = PI[68];
   assign N138 = PI[69];
   assign N141 = PI[70];
   assign N144 = PI[71];
   assign N147 = PI[72];
   assign N150 = PI[73];
   assign N151 = PI[74];
   assign N152 = PI[75];
   assign N153 = PI[76];
   assign N154 = PI[77];
   assign N155 = PI[78];
   assign N156 = PI[79];
   assign N157 = PI[80];
   assign N158 = PI[81];
   assign N159 = PI[82];
   assign N160 = PI[83];
   assign N161 = PI[84];
   assign N162 = PI[85];
   assign N163 = PI[86];
   assign N164 = PI[87];
   assign N165 = PI[88];
   assign N166 = PI[89];
   assign N167 = PI[90];
   assign N168 = PI[91];
   assign N169 = PI[92];
   assign N170 = PI[93];
   assign N171 = PI[94];
   assign N172 = PI[95];
   assign N173 = PI[96];
   assign N174 = PI[97];
   assign N175 = PI[98];
   assign N176 = PI[99];
   assign N177 = PI[100];
   assign N178 = PI[101];
   assign N179 = PI[102];
   assign N180 = PI[103];
   assign N181 = PI[104];
   assign N182 = PI[105];
   assign N183 = PI[106];
   assign N184 = PI[107];
   assign N185 = PI[108];
   assign N186 = PI[109];
   assign N187 = PI[110];
   assign N188 = PI[111];
   assign N189 = PI[112];
   assign N190 = PI[113];
   assign N191 = PI[114];
   assign N192 = PI[115];
   assign N193 = PI[116];
   assign N194 = PI[117];
   assign N195 = PI[118];
   assign N196 = PI[119];
   assign N197 = PI[120];
   assign N198 = PI[121];
   assign N199 = PI[122];
   assign N200 = PI[123];
   assign N201 = PI[124];
   assign N202 = PI[125];
   assign N203 = PI[126];
   assign N204 = PI[127];
   assign N205 = PI[128];
   assign N206 = PI[129];
   assign N207 = PI[130];
   assign N208 = PI[131];
   assign N209 = PI[132];
   assign N210 = PI[133];
   assign N211 = PI[134];
   assign N212 = PI[135];
   assign N213 = PI[136];
   assign N214 = PI[137];
   assign N215 = PI[138];
   assign N216 = PI[139];
   assign N217 = PI[140];
   assign N218 = PI[141];
   assign N219 = PI[142];
   assign N220 = PI[143];
   assign N221 = PI[144];
   assign N222 = PI[145];
   assign N223 = PI[146];
   assign N224 = PI[147];
   assign N225 = PI[148];
   assign N226 = PI[149];
   assign N227 = PI[150];
   assign N228 = PI[151];
   assign N229 = PI[152];
   assign N230 = PI[153];
   assign N231 = PI[154];
   assign N232 = PI[155];
   assign N233 = PI[156];
   assign N234 = PI[157];
   assign N235 = PI[158];
   assign N236 = PI[159];
   assign N237 = PI[160];
   assign N238 = PI[161];
   assign N239 = PI[162];
   assign N240 = PI[163];
   assign N242 = PI[164];
   assign N245 = PI[165];
   assign N248 = PI[166];
   assign N251 = PI[167];
   assign N254 = PI[168];
   assign N257 = PI[169];
   assign N260 = PI[170];
   assign N263 = PI[171];
   assign N267 = PI[172];
   assign N271 = PI[173];
   assign N274 = PI[174];
   assign N277 = PI[175];
   assign N280 = PI[176];
   assign N283 = PI[177];
   assign N286 = PI[178];
   assign N289 = PI[179];
   assign N293 = PI[180];
   assign N296 = PI[181];
   assign N299 = PI[182];
   assign N303 = PI[183];
   assign N307 = PI[184];
   assign N310 = PI[185];
   assign N313 = PI[186];
   assign N316 = PI[187];
   assign N319 = PI[188];
   assign N322 = PI[189];
   assign N325 = PI[190];
   assign N328 = PI[191];
   assign N331 = PI[192];
   assign N334 = PI[193];
   assign N337 = PI[194];
   assign N340 = PI[195];
   assign N343 = PI[196];
   assign N346 = PI[197];
   assign N349 = PI[198];
   assign N352 = PI[199];
   assign N355 = PI[200];
   assign N358 = PI[201];
   assign N361 = PI[202];
   assign N364 = PI[203];
   assign N367 = PI[204];
   assign N382 = PI[205];
   assign N241_I = PI[206];

   // map DUT outputs and bidis to PO[] vector
   assign
      PO[0] = N387 ,
      PO[1] = N388 ,
      PO[2] = N478 ,
      PO[3] = N482 ,
      PO[4] = N484 ,
      PO[5] = N486 ,
      PO[6] = N489 ,
      PO[7] = N492 ,
      PO[8] = N501 ,
      PO[9] = N505 ,
      PO[10] = N507 ,
      PO[11] = N509 ,
      PO[12] = N511 ,
      PO[13] = N513 ,
      PO[14] = N515 ,
      PO[15] = N517 ,
      PO[16] = N519 ,
      PO[17] = N535 ,
      PO[18] = N537 ,
      PO[19] = N539 ,
      PO[20] = N541 ,
      PO[21] = N543 ,
      PO[22] = N545 ,
      PO[23] = N547 ,
      PO[24] = N549 ,
      PO[25] = N551 ,
      PO[26] = N553 ,
      PO[27] = N556 ,
      PO[28] = N559 ,
      PO[29] = N561 ,
      PO[30] = N563 ,
      PO[31] = N565 ;
   assign
      PO[32] = N567 ,
      PO[33] = N569 ,
      PO[34] = N571 ,
      PO[35] = N573 ,
      PO[36] = N582 ,
      PO[37] = N643 ,
      PO[38] = N707 ,
      PO[39] = N813 ,
      PO[40] = N881 ,
      PO[41] = N882 ,
      PO[42] = N883 ,
      PO[43] = N884 ,
      PO[44] = N885 ,
      PO[45] = N889 ,
      PO[46] = N945 ,
      PO[47] = N1110 ,
      PO[48] = N1111 ,
      PO[49] = N1112 ,
      PO[50] = N1113 ,
      PO[51] = N1114 ,
      PO[52] = N1489 ,
      PO[53] = N1490 ,
      PO[54] = N1781 ,
      PO[55] = N10025 ,
      PO[56] = N10101 ,
      PO[57] = N10102 ,
      PO[58] = N10103 ,
      PO[59] = N10104 ,
      PO[60] = N10109 ,
      PO[61] = N10110 ,
      PO[62] = N10111 ,
      PO[63] = N10112 ;
   assign
      PO[64] = N10350 ,
      PO[65] = N10351 ,
      PO[66] = N10352 ,
      PO[67] = N10353 ,
      PO[68] = N10574 ,
      PO[69] = N10575 ,
      PO[70] = N10576 ,
      PO[71] = N10628 ,
      PO[72] = N10632 ,
      PO[73] = N10641 ,
      PO[74] = N10704 ,
      PO[75] = N10706 ,
      PO[76] = N10711 ,
      PO[77] = N10712 ,
      PO[78] = N10713 ,
      PO[79] = N10714 ,
      PO[80] = N10715 ,
      PO[81] = N10716 ,
      PO[82] = N10717 ,
      PO[83] = N10718 ,
      PO[84] = N10729 ,
      PO[85] = N10759 ,
      PO[86] = N10760 ,
      PO[87] = N10761 ,
      PO[88] = N10762 ,
      PO[89] = N10763 ,
      PO[90] = N10827 ,
      PO[91] = N10837 ,
      PO[92] = N10838 ,
      PO[93] = N10839 ,
      PO[94] = N10840 ,
      PO[95] = N10868 ;
   assign
      PO[96] = N10869 ,
      PO[97] = N10870 ,
      PO[98] = N10871 ,
      PO[99] = N10905 ,
      PO[100] = N10906 ,
      PO[101] = N10907 ,
      PO[102] = N10908 ,
      PO[103] = N11333 ,
      PO[104] = N11334 ,
      PO[105] = N11340 ,
      PO[106] = N11342 ,
      PO[107] = N241_O ;

   // instantiate the design into the testbench
   c7552 dut (
      .N1(N1),
      .N5(N5),
      .N9(N9),
      .N12(N12),
      .N15(N15),
      .N18(N18),
      .N23(N23),
      .N26(N26),
      .N29(N29),
      .N32(N32),
      .N35(N35),
      .N38(N38),
      .N41(N41),
      .N44(N44),
      .N47(N47),
      .N50(N50),
      .N53(N53),
      .N54(N54),
      .N55(N55),
      .N56(N56),
      .N57(N57),
      .N58(N58),
      .N59(N59),
      .N60(N60),
      .N61(N61),
      .N62(N62),
      .N63(N63),
      .N64(N64),
      .N65(N65),
      .N66(N66),
      .N69(N69),
      .N70(N70),
      .N73(N73),
      .N74(N74),
      .N75(N75),
      .N76(N76),
      .N77(N77),
      .N78(N78),
      .N79(N79),
      .N80(N80),
      .N81(N81),
      .N82(N82),
      .N83(N83),
      .N84(N84),
      .N85(N85),
      .N86(N86),
      .N87(N87),
      .N88(N88),
      .N89(N89),
      .N94(N94),
      .N97(N97),
      .N100(N100),
      .N103(N103),
      .N106(N106),
      .N109(N109),
      .N110(N110),
      .N111(N111),
      .N112(N112),
      .N113(N113),
      .N114(N114),
      .N115(N115),
      .N118(N118),
      .N121(N121),
      .N124(N124),
      .N127(N127),
      .N130(N130),
      .N133(N133),
      .N134(N134),
      .N135(N135),
      .N138(N138),
      .N141(N141),
      .N144(N144),
      .N147(N147),
      .N150(N150),
      .N151(N151),
      .N152(N152),
      .N153(N153),
      .N154(N154),
      .N155(N155),
      .N156(N156),
      .N157(N157),
      .N158(N158),
      .N159(N159),
      .N160(N160),
      .N161(N161),
      .N162(N162),
      .N163(N163),
      .N164(N164),
      .N165(N165),
      .N166(N166),
      .N167(N167),
      .N168(N168),
      .N169(N169),
      .N170(N170),
      .N171(N171),
      .N172(N172),
      .N173(N173),
      .N174(N174),
      .N175(N175),
      .N176(N176),
      .N177(N177),
      .N178(N178),
      .N179(N179),
      .N180(N180),
      .N181(N181),
      .N182(N182),
      .N183(N183),
      .N184(N184),
      .N185(N185),
      .N186(N186),
      .N187(N187),
      .N188(N188),
      .N189(N189),
      .N190(N190),
      .N191(N191),
      .N192(N192),
      .N193(N193),
      .N194(N194),
      .N195(N195),
      .N196(N196),
      .N197(N197),
      .N198(N198),
      .N199(N199),
      .N200(N200),
      .N201(N201),
      .N202(N202),
      .N203(N203),
      .N204(N204),
      .N205(N205),
      .N206(N206),
      .N207(N207),
      .N208(N208),
      .N209(N209),
      .N210(N210),
      .N211(N211),
      .N212(N212),
      .N213(N213),
      .N214(N214),
      .N215(N215),
      .N216(N216),
      .N217(N217),
      .N218(N218),
      .N219(N219),
      .N220(N220),
      .N221(N221),
      .N222(N222),
      .N223(N223),
      .N224(N224),
      .N225(N225),
      .N226(N226),
      .N227(N227),
      .N228(N228),
      .N229(N229),
      .N230(N230),
      .N231(N231),
      .N232(N232),
      .N233(N233),
      .N234(N234),
      .N235(N235),
      .N236(N236),
      .N237(N237),
      .N238(N238),
      .N239(N239),
      .N240(N240),
      .N242(N242),
      .N245(N245),
      .N248(N248),
      .N251(N251),
      .N254(N254),
      .N257(N257),
      .N260(N260),
      .N263(N263),
      .N267(N267),
      .N271(N271),
      .N274(N274),
      .N277(N277),
      .N280(N280),
      .N283(N283),
      .N286(N286),
      .N289(N289),
      .N293(N293),
      .N296(N296),
      .N299(N299),
      .N303(N303),
      .N307(N307),
      .N310(N310),
      .N313(N313),
      .N316(N316),
      .N319(N319),
      .N322(N322),
      .N325(N325),
      .N328(N328),
      .N331(N331),
      .N334(N334),
      .N337(N337),
      .N340(N340),
      .N343(N343),
      .N346(N346),
      .N349(N349),
      .N352(N352),
      .N355(N355),
      .N358(N358),
      .N361(N361),
      .N364(N364),
      .N367(N367),
      .N382(N382),
      .N241_I(N241_I),
      .N387(N387),
      .N388(N388),
      .N478(N478),
      .N482(N482),
      .N484(N484),
      .N486(N486),
      .N489(N489),
      .N492(N492),
      .N501(N501),
      .N505(N505),
      .N507(N507),
      .N509(N509),
      .N511(N511),
      .N513(N513),
      .N515(N515),
      .N517(N517),
      .N519(N519),
      .N535(N535),
      .N537(N537),
      .N539(N539),
      .N541(N541),
      .N543(N543),
      .N545(N545),
      .N547(N547),
      .N549(N549),
      .N551(N551),
      .N553(N553),
      .N556(N556),
      .N559(N559),
      .N561(N561),
      .N563(N563),
      .N565(N565),
      .N567(N567),
      .N569(N569),
      .N571(N571),
      .N573(N573),
      .N582(N582),
      .N643(N643),
      .N707(N707),
      .N813(N813),
      .N881(N881),
      .N882(N882),
      .N883(N883),
      .N884(N884),
      .N885(N885),
      .N889(N889),
      .N945(N945),
      .N1110(N1110),
      .N1111(N1111),
      .N1112(N1112),
      .N1113(N1113),
      .N1114(N1114),
      .N1489(N1489),
      .N1490(N1490),
      .N1781(N1781),
      .N10025(N10025),
      .N10101(N10101),
      .N10102(N10102),
      .N10103(N10103),
      .N10104(N10104),
      .N10109(N10109),
      .N10110(N10110),
      .N10111(N10111),
      .N10112(N10112),
      .N10350(N10350),
      .N10351(N10351),
      .N10352(N10352),
      .N10353(N10353),
      .N10574(N10574),
      .N10575(N10575),
      .N10576(N10576),
      .N10628(N10628),
      .N10632(N10632),
      .N10641(N10641),
      .N10704(N10704),
      .N10706(N10706),
      .N10711(N10711),
      .N10712(N10712),
      .N10713(N10713),
      .N10714(N10714),
      .N10715(N10715),
      .N10716(N10716),
      .N10717(N10717),
      .N10718(N10718),
      .N10729(N10729),
      .N10759(N10759),
      .N10760(N10760),
      .N10761(N10761),
      .N10762(N10762),
      .N10763(N10763),
      .N10827(N10827),
      .N10837(N10837),
      .N10838(N10838),
      .N10839(N10839),
      .N10840(N10840),
      .N10868(N10868),
      .N10869(N10869),
      .N10870(N10870),
      .N10871(N10871),
      .N10905(N10905),
      .N10906(N10906),
      .N10907(N10907),
      .N10908(N10908),
      .N11333(N11333),
      .N11334(N11334),
      .N11340(N11340),
      .N11342(N11342),
      .N241_O(N241_O)   );


   integer errshown;
   event measurePO;
   always @ measurePO begin
      if (((XPCT&MASK) !== (ALLPOS&MASK)) || (XPCT !== (~(~XPCT)))) begin
         errshown = 0;
         for (bit = 0; bit < NOUTPUTS; bit=bit + 1) begin
            if (MASK[bit]==1'b1) begin
               if (XPCT[bit] !== ALLPOS[bit]) begin
                  if (errshown==0) $display("\n// *** ERROR during capture pattern %0d, T=%t", pattern, $time);
                  $display("  %0d %0s (exp=%b, got=%b)", pattern, POnames[bit], XPCT[bit], ALLPOS[bit]);
                  nofails = nofails + 1; errshown = 1;
               end
            end
         end
      end
   end

   event forcePI_default_WFT;
   always @ forcePI_default_WFT begin
      PI = ALLPIS;
   end
   event measurePO_default_WFT;
   always @ measurePO_default_WFT begin
      #40;
      ALLPOS = PO;
      #0; #0 -> measurePO;
      `ifdef tmax_iddq
         #0; ->IDDQ;
      `endif
   end

   always @ IDDQ begin
   `ifdef tmax_iddq
      $ssi_iddq("strobe_try");
      $ssi_iddq("status drivers leaky AAA_tmax_testbench_1_16.leaky");
   `endif
   end

   event capture;
   always @ capture begin
      ->forcePI_default_WFT;
      #100; ->measurePO_default_WFT;
   end


   initial begin

      //
      // --- establish a default time format for %t
      //
      $timeformat(-9,2," ns",18);

      //
      // --- default verbosity to 2 but also allow user override by
      //     using '+define+tmax_msg=N' on verilog compile line.
      //
      `ifdef tmax_msg
         verbose = `tmax_msg ;
      `else
         verbose = 2 ;
      `endif

      //
      // --- default pattern reporting interval to 5 but also allow user
      //     override by using '+define+tmax_rpt=N' on verilog compile line.
      //
      `ifdef tmax_rpt
         report_interval = `tmax_rpt ;
      `else
         report_interval = 5 ;
      `endif

      //
      // --- support generating Extened VCD output by using
      //     '+define+tmax_vcde' on verilog compile line.
      //
      `ifdef tmax_vcde
         // extended VCD, see IEEE Verilog P1364.1-1999 Draft 2
         if (verbose >= 2) $display("// %t : opening Extended VCD output file", $time);
         $dumpports( dut, "sim_vcde.out");
      `endif

      //
      // --- IDDQ PLI initialization
      //     User may activite by using '+define+tmax_iddq' on verilog compile line.
      //     Or by defining `tmax_iddq in this file.
      //
      `ifdef tmax_iddq
         if (verbose >= 3) $display("// %t : Initializing IDDQ PLI", $time);
         $ssi_iddq("dut AAA_tmax_testbench_1_16.dut");
         $ssi_iddq("verb on");
         $ssi_iddq("cycle 0");
         //
         // --- User may select one of the following two methods for fault seeding:
         //     #1 faults seeded by PLI (default)
         //     #2 faults supplied in a file
         //     Comment out the unused lines as needed (precede with '//').
         //     Replace the 'FAULTLIST_FILE' string with the actual file pathname.
         //
         $ssi_iddq("seed SA AAA_tmax_testbench_1_16.dut");   // no file, faults seeded by PLI
         //
         // $ssi_iddq("scope AAA_tmax_testbench_1_16.dut");   // set scope for faults from a file
         // $ssi_iddq("read_tmax FAULTLIST_FILE"); // read faults from a file
         //
      `endif

      POnames[0] = "N387";
      POnames[1] = "N388";
      POnames[2] = "N478";
      POnames[3] = "N482";
      POnames[4] = "N484";
      POnames[5] = "N486";
      POnames[6] = "N489";
      POnames[7] = "N492";
      POnames[8] = "N501";
      POnames[9] = "N505";
      POnames[10] = "N507";
      POnames[11] = "N509";
      POnames[12] = "N511";
      POnames[13] = "N513";
      POnames[14] = "N515";
      POnames[15] = "N517";
      POnames[16] = "N519";
      POnames[17] = "N535";
      POnames[18] = "N537";
      POnames[19] = "N539";
      POnames[20] = "N541";
      POnames[21] = "N543";
      POnames[22] = "N545";
      POnames[23] = "N547";
      POnames[24] = "N549";
      POnames[25] = "N551";
      POnames[26] = "N553";
      POnames[27] = "N556";
      POnames[28] = "N559";
      POnames[29] = "N561";
      POnames[30] = "N563";
      POnames[31] = "N565";
      POnames[32] = "N567";
      POnames[33] = "N569";
      POnames[34] = "N571";
      POnames[35] = "N573";
      POnames[36] = "N582";
      POnames[37] = "N643";
      POnames[38] = "N707";
      POnames[39] = "N813";
      POnames[40] = "N881";
      POnames[41] = "N882";
      POnames[42] = "N883";
      POnames[43] = "N884";
      POnames[44] = "N885";
      POnames[45] = "N889";
      POnames[46] = "N945";
      POnames[47] = "N1110";
      POnames[48] = "N1111";
      POnames[49] = "N1112";
      POnames[50] = "N1113";
      POnames[51] = "N1114";
      POnames[52] = "N1489";
      POnames[53] = "N1490";
      POnames[54] = "N1781";
      POnames[55] = "N10025";
      POnames[56] = "N10101";
      POnames[57] = "N10102";
      POnames[58] = "N10103";
      POnames[59] = "N10104";
      POnames[60] = "N10109";
      POnames[61] = "N10110";
      POnames[62] = "N10111";
      POnames[63] = "N10112";
      POnames[64] = "N10350";
      POnames[65] = "N10351";
      POnames[66] = "N10352";
      POnames[67] = "N10353";
      POnames[68] = "N10574";
      POnames[69] = "N10575";
      POnames[70] = "N10576";
      POnames[71] = "N10628";
      POnames[72] = "N10632";
      POnames[73] = "N10641";
      POnames[74] = "N10704";
      POnames[75] = "N10706";
      POnames[76] = "N10711";
      POnames[77] = "N10712";
      POnames[78] = "N10713";
      POnames[79] = "N10714";
      POnames[80] = "N10715";
      POnames[81] = "N10716";
      POnames[82] = "N10717";
      POnames[83] = "N10718";
      POnames[84] = "N10729";
      POnames[85] = "N10759";
      POnames[86] = "N10760";
      POnames[87] = "N10761";
      POnames[88] = "N10762";
      POnames[89] = "N10763";
      POnames[90] = "N10827";
      POnames[91] = "N10837";
      POnames[92] = "N10838";
      POnames[93] = "N10839";
      POnames[94] = "N10840";
      POnames[95] = "N10868";
      POnames[96] = "N10869";
      POnames[97] = "N10870";
      POnames[98] = "N10871";
      POnames[99] = "N10905";
      POnames[100] = "N10906";
      POnames[101] = "N10907";
      POnames[102] = "N10908";
      POnames[103] = "N11333";
      POnames[104] = "N11334";
      POnames[105] = "N11340";
      POnames[106] = "N11342";
      POnames[107] = "N241_O";
      nofails = 0; pattern = -1; lastpattern = 0;
      prev_pat = -2; error_banner = -2;
      /*** No test setup procedure ***/


      /*** Non-scan test ***/

      if (verbose >= 1) $display("// %t : Begin patterns, first pattern = 0", $time);
pattern = 0; // 0
ALLPIS = 207'b111100000000110100000110010111100011000010001010001010010011100001011010100011010001001000101111010100100101110010111100101010110110110000011011101001101011101000000100101111010110010101101100110111101100101;
XPCT = 108'b110101110011001010110110011011101100101111111101111111100000101101001110011011100110100101011111001100000011;
MASK = 108'b111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111;
#0 ->capture;
#200; // 200

pattern = 1; // 200
ALLPIS = 207'b111110000000011010000011001011110001100001000101000101001001110000101101010001101000100100010111101010010010111001011110010101011011011000001101110100110101110100000010010111101011001010110110011011110110010;
XPCT = 108'b111010111101100101011011001111110110000011111111011011010000010011101110010010101001101011000001001000100000;
MASK = 108'b111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111;
#0 ->capture;
#200; // 400

pattern = 2; // 400
ALLPIS = 207'b100011000000111001000111110010011011110010101000101000110111011001001100001011100101011010100100100001101100101110010011100000011011011100011101010011110001010010000101100100100011110000110111111010010111100;
XPCT = 108'b110100101001111000011011111110010111010001111101011011100110011101011111010010011111101010011111010011010100;
MASK = 108'b111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111;
#0 ->capture;
#200; // 600

pattern = 3; // 600
ALLPIS = 207'b001101100000101000100101101110101110111011011110011110001000001101111100100110100011100101111101000100010011100101110101011010111011011110010101000000010011000001000110011101000111101101110111001010100111011;
XPCT = 108'b001011100011110110111011100110100111100001111001110100010000010110000100110001000011100010011001011010101011;
MASK = 108'b111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111;
#0 ->capture;
#200; // 800

pattern = 4; // 800
ALLPIS = 207'b111010110000100000010100100000110100011111100101000101010111100111100100110000000000111010010001110110101100000000000110000111101011011111010001001001100010001000100111100001110101100011010111010010111111000;
XPCT = 108'b111100001010110001101011101010111111011011111111011011111111101100110101100111101100111101000000011000001110;
MASK = 108'b111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111;
#0 ->capture;
#200; // 1000

pattern = 5; // 1000
ALLPIS = 207'b111101011000010000001010010000011010001111110010100010101011110011110010011000000000011101001000111011010110000000000011000011110101101111101000100100110001000100010011110000111010110001101011101001011111100;
XPCT = 108'b111110001101011000110101110101011111111011111101111111100000111111001110100010101010101100011111010001001010;
MASK = 108'b111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111;
#0 ->capture;
#200; // 1200

pattern = 6; // 1200
ALLPIS = 207'b000010101100111100000011011111101110000101110011011011000110011000100011101111010001000110001011001001001110110010111101001011001100000111101111111011110011001010001101010111001011001101011001000011000011011;
XPCT = 108'b000010110101100110101100100011000011010001101010001010010110011011101111101011011001100010000111100001000011;
MASK = 108'b111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111;
#0 ->capture;
#200; // 1400

pattern = 7; // 1400
ALLPIS = 207'b000001010110011110000001101111110111000010111001101101100011001100010001110111101000100011000101100100100111011001011110100101100110000011110111111101111001100101000110101011100101100110101100100001100001101;
XPCT = 108'b001101011010110011010110010001100001100001111011111110001001100000011000000111100100110100000000111011110111;
MASK = 108'b111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111;
#0 ->capture;
#200; // 1600

pattern = 8; // 1600
ALLPIS = 207'b011100101011111011000110100000011000100011010110111100100010000111010010011000100101011001001101100110110110011110010011111000000101110001100000010111010111011010100111111010100100100110111010100111011100011;
XPCT = 108'b001111011010010011011101010011011100110111110001111110001111111010011111100111010010110110100001111110110101;
MASK = 108'b111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111;
#0 ->capture;
#200; // 1800

pattern = 9; // 1800
ALLPIS = 207'b001110010101111101100011010000001100010001101011011110010001000011101001001100010010101100100110110011011011001111001001111100000010111000110000001011101011101101010011111101010010010011011101010011101110001;
XPCT = 108'b001111100001001001101110101011101110011001111001011010011111101100001111001100010010111110011000100111111011;
MASK = 108'b111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111;
#0 ->capture;
#200; // 2000

      $display("// %t : Simulation of %0d patterns completed with %0d errors\n", $time, pattern+1, nofails);
      if (verbose >=2) $finish(2);
      /* else */ $finish(0);
   end
endmodule
