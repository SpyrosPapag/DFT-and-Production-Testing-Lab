module s5378_tb;

// Inputs
reg CK      , n3065gat, n3066gat, n3067gat, n3068gat, n3069gat, n3070gat,
    n3071gat, n3072gat, n3073gat, n3074gat, n3075gat, n3076gat, n3077gat,
    n3078gat, n3079gat, n3080gat, n3081gat, n3082gat, n3083gat, n3084gat,
    n3085gat, n3086gat, n3087gat, n3088gat, n3089gat, n3090gat, n3091gat,
    n3092gat, n3093gat, n3094gat, n3095gat, n3097gat, n3098gat, n3099gat,
    n3100gat, test_si , test_se ;

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
s5378 DUT (CK, n3065gat, n3066gat, n3067gat, n3068gat, n3069gat, n3070gat, 
        n3071gat, n3072gat, n3073gat, n3074gat, n3075gat, n3076gat, n3077gat, 
        n3078gat, n3079gat, n3080gat, n3081gat, n3082gat, n3083gat, n3084gat, 
        n3085gat, n3086gat, n3087gat, n3088gat, n3089gat, n3090gat, n3091gat, 
        n3092gat, n3093gat, n3094gat, n3095gat, n3097gat, n3098gat, n3099gat, 
        n3100gat, n3104gat, n3105gat, n3106gat, n3107gat, n3108gat, n3109gat, 
        n3110gat, n3111gat, n3112gat, n3113gat, n3114gat, n3115gat, n3116gat, 
        n3117gat, n3118gat, n3119gat, n3120gat, n3121gat, n3122gat, n3123gat, 
        n3124gat, n3125gat, n3126gat, n3127gat, n3128gat, n3129gat, n3130gat, 
        n3131gat, n3132gat, n3133gat, n3134gat, n3135gat, n3136gat, n3137gat, 
        n3138gat, n3139gat, n3140gat, n3141gat, n3142gat, n3143gat, n3144gat, 
        n3145gat, n3146gat, n3147gat, n3148gat, n3149gat, n3150gat, n3151gat, 
        n3152gat, test_si, test_so, test_se
        );

// Clock
localparam period = 2800;
always #(0.5*period) CK = ~CK;

// Files
localparam test_set = "my_s5378.vec";
localparam so_log = "so.log";
localparam po_log = "po.log";
integer vec_fh, so_fh, po_fh;

localparam log = "all.log";
integer log_fh;

// To count faults
integer faults = 0;
localparam total_patterns = 284;

// DUT inputs
reg [34:0]  test_pi[total_patterns-1:0];
reg [178:0] test_si_vec[total_patterns-1:0];

// Expected and actual DUT outputs
reg [49:0] act_po[total_patterns-1:0];
reg [48:0] exp_po[total_patterns-1:0];
reg [178:0] act_so_vec[total_patterns-1:0];
reg [178:0] exp_so[total_patterns-1:0];

// To count scan chain cycles
integer cycle;

// To count patterns
integer pattern = 0;

initial begin
    CK = 1'b0;
    vec_fh = $fopen(test_set, "r");
    so_fh = $fopen(so_log, "w");
    po_fh = $fopen(po_log, "w");
    log_fh = $fopen(log, "w");

    while (!$feof(vec_fh)) begin
        $fscanf(vec_fh,"%b %b %b %b\n", test_pi[pattern], test_si_vec[pattern], exp_po[pattern], exp_so[pattern]);
        $fwrite(log_fh,"%b %b %b %b\n", test_pi[pattern], test_si_vec[pattern], exp_po[pattern], exp_so[pattern]);
        pattern = pattern + 1;
    end

    // Precondition DUT
    {n3065gat, n3066gat, n3067gat, n3068gat, n3069gat, n3070gat,
    n3071gat, n3072gat, n3073gat, n3074gat, n3075gat, n3076gat, n3077gat,
    n3078gat, n3079gat, n3080gat, n3081gat, n3082gat, n3083gat, n3084gat,
    n3085gat, n3086gat, n3087gat, n3088gat, n3089gat, n3090gat, n3091gat,
    n3092gat, n3093gat, n3094gat, n3095gat, n3097gat, n3098gat, n3099gat,
    n3100gat} = 35'd0;
    
    // Apply tests
    for(pattern = 0; pattern<total_patterns; pattern = pattern + 1) begin
        // scan chain loading
        test_se = 1'b1;
        act_so_vec[pattern] = 179'd0;
        for (cycle = 0; cycle < 179; cycle = cycle + 1) begin
            // prepare si value at clock negedge
            @(negedge CK)
            test_si = test_si_vec[pattern][cycle];
            // get pervious so while loading next state
            @(posedge CK)
            act_so_vec[pattern] = {act_so_vec[pattern], test_so};
        end
        $fwrite(so_fh, "%b\n", act_so_vec[pattern]);
        test_se = 1'b0;
        
        // set PI values
        {n3065gat, n3066gat, n3067gat, n3068gat, n3069gat, n3070gat,
        n3071gat, n3072gat, n3073gat, n3074gat, n3075gat, n3076gat, n3077gat,
        n3078gat, n3079gat, n3080gat, n3081gat, n3082gat, n3083gat, n3084gat,
        n3085gat, n3086gat, n3087gat, n3088gat, n3089gat, n3090gat, n3091gat,
        n3092gat, n3093gat, n3094gat, n3095gat, n3097gat, n3098gat, n3099gat,
        n3100gat} = test_pi[pattern];

        // parallel capture
        @(posedge CK)
        act_po[pattern] = po;
        $fwrite(po_fh, "%b\n", act_po[pattern]);
        $display("act_so_vec: %b", act_so_vec[pattern]);
        $display("exp_so    : %b", exp_so[pattern]);
        $display("po    : %b", act_po[pattern]);
        $display("exp_po: %b", exp_po[pattern]);
    end

    for ( pattern = 0; pattern<total_patterns ; pattern = pattern+1) begin
        if((act_so_vec[pattern] != exp_so[pattern]) || (act_po[pattern] != exp_po[pattern])) begin
            $write("fault detected for pattern %d. ", pattern);
            if(act_so_vec[pattern] != exp_so[pattern])
                $write("Wrong so. ");
            if(act_po[pattern] != exp_po[pattern])
                $write("Wrong po.");
            $write("\n");
            faults = faults + 1;
        end
    end
    $display("Total faults detected: %d", faults);
    $display("Pattern success: %d%%", (total_patterns - faults) * 100.0 / total_patterns);

    $fclose(vec_fh);
    $fclose(so_fh);
    $fclose(po_fh);
    $fclose(log_fh);
    $finish;
end    
endmodule