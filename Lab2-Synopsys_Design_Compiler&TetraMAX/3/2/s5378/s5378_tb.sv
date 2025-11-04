`timescale 1ns/1ps
module s5378_tb;

// Inputs
reg CK      , n3065gat, n3066gat, n3067gat, n3068gat, n3069gat, n3070gat,
    n3071gat, n3072gat, n3073gat, n3074gat, n3075gat, n3076gat, n3077gat,
    n3078gat, n3079gat, n3080gat, n3081gat, n3082gat, n3083gat, n3084gat,
    n3085gat, n3086gat, n3087gat, n3088gat, n3089gat, n3090gat, n3091gat,
    n3092gat, n3093gat, n3094gat, n3095gat, n3097gat, n3098gat, n3099gat,
    n3100gat, test_si , test_se ;
logic [34:0] pi;
assign {
    n3065gat, n3066gat, n3067gat, n3068gat, n3069gat, n3070gat, n3071gat,
    n3072gat, n3073gat, n3074gat, n3075gat, n3076gat, n3077gat, n3078gat,
    n3079gat, n3080gat, n3081gat, n3082gat, n3083gat, n3084gat, n3085gat,
    n3086gat, n3087gat, n3088gat, n3089gat, n3090gat, n3091gat, n3092gat,
    n3093gat, n3094gat, n3095gat, n3097gat, n3098gat, n3099gat, n3100gat
    } = pi;

// Outputs
wire n3104gat, n3105gat, n3106gat, n3107gat, n3108gat, n3109gat, n3110gat,
     n3111gat, n3112gat, n3113gat, n3114gat, n3115gat, n3116gat, n3117gat,
     n3118gat, n3119gat, n3120gat, n3121gat, n3122gat, n3123gat, n3124gat,
     n3125gat, n3126gat, n3127gat, n3128gat, n3129gat, n3130gat, n3131gat,
     n3132gat, n3133gat, n3134gat, n3135gat, n3136gat, n3137gat, n3138gat,
     n3139gat, n3140gat, n3141gat, n3142gat, n3143gat, n3144gat, n3145gat,
     n3146gat, n3147gat, n3148gat, n3149gat, n3150gat, n3151gat, n3152gat,
     test_so ;

wire [48:0] po = {
    n3104gat, n3105gat, n3106gat, n3107gat, n3108gat, n3109gat, n3110gat,
    n3111gat, n3112gat, n3113gat, n3114gat, n3115gat, n3116gat, n3117gat,
    n3118gat, n3119gat, n3120gat, n3121gat, n3122gat, n3123gat, n3124gat,
    n3125gat, n3126gat, n3127gat, n3128gat, n3129gat, n3130gat, n3131gat,
    n3132gat, n3133gat, n3134gat, n3135gat, n3136gat, n3137gat, n3138gat,
    n3139gat, n3140gat, n3141gat, n3142gat, n3143gat, n3144gat, n3145gat,
    n3146gat, n3147gat, n3148gat, n3149gat, n3150gat, n3151gat, n3152gat
};

// DUT
s5378 DUT (         .CK(CK), .n3065gat(n3065gat), .n3066gat(n3066gat), .n3067gat(n3067gat), .n3068gat(n3068gat), .n3069gat(n3069gat), .n3070gat(n3070gat), 
        .n3071gat(n3071gat), .n3072gat(n3072gat), .n3073gat(n3073gat), .n3074gat(n3074gat), .n3075gat(n3075gat), .n3076gat(n3076gat), .n3077gat(n3077gat), 
        .n3078gat(n3078gat), .n3079gat(n3079gat), .n3080gat(n3080gat), .n3081gat(n3081gat), .n3082gat(n3082gat), .n3083gat(n3083gat), .n3084gat(n3084gat), 
        .n3085gat(n3085gat), .n3086gat(n3086gat), .n3087gat(n3087gat), .n3088gat(n3088gat), .n3089gat(n3089gat), .n3090gat(n3090gat), .n3091gat(n3091gat), 
        .n3092gat(n3092gat), .n3093gat(n3093gat), .n3094gat(n3094gat), .n3095gat(n3095gat), .n3097gat(n3097gat), .n3098gat(n3098gat), .n3099gat(n3099gat), 
        .n3100gat(n3100gat), .n3104gat(n3104gat), .n3105gat(n3105gat), .n3106gat(n3106gat), .n3107gat(n3107gat), .n3108gat(n3108gat), .n3109gat(n3109gat), 
        .n3110gat(n3110gat), .n3111gat(n3111gat), .n3112gat(n3112gat), .n3113gat(n3113gat), .n3114gat(n3114gat), .n3115gat(n3115gat), .n3116gat(n3116gat), 
        .n3117gat(n3117gat), .n3118gat(n3118gat), .n3119gat(n3119gat), .n3120gat(n3120gat), .n3121gat(n3121gat), .n3122gat(n3122gat), .n3123gat(n3123gat), 
        .n3124gat(n3124gat), .n3125gat(n3125gat), .n3126gat(n3126gat), .n3127gat(n3127gat), .n3128gat(n3128gat), .n3129gat(n3129gat), .n3130gat(n3130gat), 
        .n3131gat(n3131gat), .n3132gat(n3132gat), .n3133gat(n3133gat), .n3134gat(n3134gat), .n3135gat(n3135gat), .n3136gat(n3136gat), .n3137gat(n3137gat), 
        .n3138gat(n3138gat), .n3139gat(n3139gat), .n3140gat(n3140gat), .n3141gat(n3141gat), .n3142gat(n3142gat), .n3143gat(n3143gat), .n3144gat(n3144gat), 
        .n3145gat(n3145gat), .n3146gat(n3146gat), .n3147gat(n3147gat), .n3148gat(n3148gat), .n3149gat(n3149gat), .n3150gat(n3150gat), .n3151gat(n3151gat), 
        .n3152gat(n3152gat),   .test_si(test_si),   .test_so(test_so),   .test_se(test_se)
        );


// Files
localparam test_set = "my_s5378.vec";
localparam so_log = "so.log";
localparam po_log = "po.log";
integer vec_fh, so_fh, po_fh;

// To count faults
integer faults = 0;
localparam total_patterns = 285;

// DUT inputs
reg         test_ck    [total_patterns-1:0];
reg         test_si_io [total_patterns-1:0];
reg         test_se_io [total_patterns-1:0];
reg [34:0]  test_pi    [total_patterns-1:0];
reg [178:0] test_si_vec[total_patterns-1:0];

// Expected and actual DUT outputs
reg [48:0]  act_po    [total_patterns-1:0];
reg [48:0]  exp_po    [total_patterns-1:0];
reg [178:0] act_so_vec[total_patterns-1:0];
reg [178:0] exp_so    [total_patterns-1:0];

// To count scan chain cycles
integer cycle;

// To count patterns
integer pattern, bit_idx;

task scan_clock;
    CK = 1'b0;
    #45ns;
    CK = 1'b1;
    #10ns;
    CK = 1'b0;
    #45ns;
endtask

initial begin
    vec_fh = $fopen(test_set, "r");
    so_fh = $fopen(so_log, "w");
    po_fh = $fopen(po_log, "w");

    pattern = 0;
    while (!$feof(vec_fh)) begin
        $fscanf(vec_fh,"%b %b %b %b %b %b %b\n", test_ck[pattern], test_si_io[pattern], test_se_io[pattern], test_pi[pattern], test_si_vec[pattern], exp_po[pattern], exp_so[pattern]);
        pattern = pattern + 1;
    end
    
    // Apply tests
    for(pattern = 0; pattern<total_patterns; pattern = pattern + 1) begin
        // apply PI
        test_se = 1'b0;
        pi = test_pi[pattern];
        
        // scan chain loading
        cycle = 178;
        test_se = 1'b1;
        repeat(179) begin
            test_si = test_si_vec[pattern][cycle];
            cycle--;
            act_so_vec[pattern][178:0] = {act_so_vec[pattern][177:0], test_so};
            scan_clock();
        end
        #200ns;
        // PO capture
        act_po[pattern] = po;
        
        // parallel capture
        test_si = test_si_io[pattern];
        test_se = test_se_io[pattern];
        if(test_ck[pattern]) scan_clock();
        #200ns;
    end

    for ( pattern = 0; pattern<total_patterns ; pattern = pattern+1) begin
        // write logs
        $fwrite(po_fh, "%b\n", act_po[pattern]);
        $fwrite(so_fh, "%b\n", act_so_vec[pattern]);
        
        // count wrong results
        if((act_so_vec[pattern] != exp_so[pattern]) || (act_po[pattern] != exp_po[pattern])) faults = faults + 1;

        // display for PO
        $write("[pattern %3d] PO: ", pattern+1);
        if(act_po[pattern] != exp_po[pattern]) begin
            $write("error in bits: ");
            for (bit_idx = 0; bit_idx<49; bit_idx++) begin
                if(act_po[pattern][bit_idx] != exp_po[pattern][bit_idx]) $write("%2d ", bit_idx);
            end
            $write("\n");
        end
        else $display("correct");
            $display("actual: %b", act_po[pattern]);
            $display("expect: %b", exp_po[pattern]);

        // display for SO
        $write("[pattern %3d] SO: ", pattern+1);
        if(act_so_vec[pattern] != exp_so[pattern]) begin
            $write("error in bits: ");
            for (bit_idx = 0; bit_idx<179; bit_idx++) begin
                if(act_so_vec[pattern][bit_idx] != exp_so[pattern][bit_idx]) $write("%2d ", bit_idx);
            end
            $write("\n");
        end
        else $display("correct");        
            $display("actual: %b", act_so_vec[pattern]);
            $display("expect: %b", exp_so[pattern]);
    end
    $display("Total faults detected: %d", faults);
    $display("Pattern success: %d%%", (total_patterns - faults) * 100 / total_patterns);

    $fclose(vec_fh);
    $fclose(so_fh);
    $fclose(po_fh);
    $finish;
end

/*
// my test
// reg [178:0] scan_in = 179'b01010111001100100011011110000001110110101001010010111000011100111010110001010100001100001101111000100100000101001101000100111101001101101000111011000001010011100001111111111001110; 
// reg [178:0] scan_in = 179'b10111111001000001111110110001000010101010101011111101100000010001111000100001000011000111111000000010001010011000010001100101100101101011100111010100010001010011010011110000111011; 
reg [178:0] scan_in = 179'b00111111000000110110010110110001100100110001101101110001111111101001000101011001101101011001011011000100000000010111110011000000001010100110101000011011011110100100111000011101001; 
int t_idx;
reg [178:0] scan_out = 179'd0;
initial begin
    // apply PI
    test_se = 1'b0;
    // pi = 35'b10110110110001100010111010001001101;
    // pi = 35'b10011010100011010010001101110000111;
    pi = 35'b10101011001010111010101101001010110;

    // scan chain loading
    t_idx = 178;
    test_se = 1'b1;
    repeat(179) begin
        test_si = scan_in[t_idx];
        t_idx--;
        scan_clock();
    end
    #200ns;
    // PO capture
    $display("po: %b", po);

    // parallel capture
    test_se = 1'b0;
    scan_clock();
    #200ns;

    // scan chain unload
    test_se = 1'b1;
    repeat(179) begin
        scan_out[178:0] = {scan_out[177:0], test_so};
        scan_clock();
    end
    $display("so: %b", scan_out);
    $finish;
end
*/
endmodule