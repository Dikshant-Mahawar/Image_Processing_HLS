module image(
    input clk,              // Clock input
    input reset,            // Reset input
    input start             // Start signal for processing
);

// Declare internal signals
wire [7:0] r, g, b;         // Red, Green, Blue inputs from BRAM
wire [7:0] gray;            // Grayscale output from the filter
reg [7:0] gray_final;       // Captured grayscale value after processing
reg [8:0] addr;             // Address counter for BRAM access
reg ena, wea;               // Enable and write enable signals for BRAM
wire done, ready, idle;     // Control signals from the grayscale filter

// Instantiate Block RAM for Red channel

blk_mem_gen_0 b_r (
  .clka(clk),    // input wire clka
  .ena(ena),      // input wire ena
  .wea(wea),      // input wire [0 : 0] wea
  .addra(addr),  // input wire [5 : 0] addra
  .dina(8'b0),    // input wire [7 : 0] dina
  .douta(r)  // output wire [7 : 0] douta
);

// Instantiate Block RAM for Green channel
blk_mem_gen_1 b_g (
  .clka(clk),    // input wire clka
  .ena(ena),      // input wire ena
  .wea(wea),      // input wire [0 : 0] wea
  .addra(addr),  // input wire [5 : 0] addra
  .dina(8'b0),    // input wire [7 : 0] dina
  .douta(g)  // output wire [7 : 0] douta
);

// Instantiate Block RAM for Blue channel
blk_mem_gen_2 b_b (
  .clka(clk),    // input wire clka
  .ena(ena),      // input wire ena
  .wea(wea),      // input wire [0 : 0] wea
  .addra(addr),  // input wire [5 : 0] addra
  .dina(8'b0),    // input wire [7 : 0] dina
  .douta(b)  // output wire [7 : 0] douta
);

// Instantiate the grayscale filter module
grayscale_filter_0 filter (
  .ap_clk(clk),        // input wire ap_clk
  .ap_rst(reset),        // input wire ap_rst
  .ap_start(start),    // input wire ap_start
  .ap_done(done),      // output wire ap_done
  .ap_idle(idle),      // output wire ap_idle
  .ap_ready(ready),    // output wire ap_ready
  .ap_return(gray),  // output wire [7 : 0] ap_return
  .red(r),              // input wire [31 : 0] red
  .green(g),          // input wire [31 : 0] green
  .blue(b)            // input wire [31 : 0] blue
);

// Instantiate Integrated Logic Analyzer (ILA) for debugging
ila_0 ila (
    .clk(clk), 
    .probe0(r),         
    .probe1(g),         
    .probe2(b),         
    .probe3(gray),    
    .probe4(gray_final),  
    .probe5(done),   
    .probe6(reset),     
    .probe7(addr),
    .probe8(ready),
    .probe9(start),
    .probe10(ena)   
);

// Main processing logic
always @(posedge clk) begin
    if (reset) begin
        ena <= 1;
        wea <= 0;
        addr <= 0;
        gray_final <= 8'b0;
    end 
    else begin
        // Enable reading RGB values when 'ready' is asserted
        if (ready) begin
            ena <= 1;
        end else begin
            ena <= 0;
        end

        // Display grayscale value if 'done' is asserted, otherwise display 0
        if (done) begin
            gray_final <= gray;
        end else begin
            gray_final <= 8'b0;
        end

        // Increment address when 'ready' is asserted
        if (ready) begin
            addr <= addr + 1'b1;
            
            // Reset address after processing a full block
            if (addr == 9'b100000000) begin
                addr <= 0;      
            end 
        end
    end
end

endmodule