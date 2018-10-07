



`timescale 1ns/1ps

module testbench;

`define INIT_VALUE  (16'b1101_0110_1010_0101)

reg [15:0] in_w = 0;
reg [15:0] out_w = 0;
reg [15:0] out_wire = 0, layer_1 = 0;
reg clk = 0, enable = 0, load = 0;
integer cnt = 0;

always @(*) layer_1[0] = ~(in_w[0] | in_w[1]);
always @(*) layer_1[1] = ~(in_w[2] | in_w[3]);
always @(*) layer_1[2] = ~(in_w[4] | in_w[5]);
always @(*) layer_1[3] = ~(in_w[6] | in_w[7]);
always @(*) layer_1[4] = ~(in_w[8] | in_w[9]);
always @(*) layer_1[5] = ~(in_w[10] | in_w[11]);
always @(*) layer_1[6] = in_w[12] | in_w[13];
always @(*) layer_1[7] = in_w[14] | in_w[15];

always @(*) out_wire[15] = ~out_wire[14];
always @(*) out_wire[14] = out_wire[13] & layer_1[7];
always @(*) out_wire[13] = ~(layer_1[6] & layer_1[7]);
always @(*) out_wire[12] = out_wire[13] | ~layer_1[6];
always @(*) out_wire[11] = ~layer_1[6];
always @(*) out_wire[10] = ~layer_1[5];
always @(*) out_wire[9] = out_wire[10] & out_wire[8];
always @(*) out_wire[8] = ~layer_1[4];
always @(*) out_wire[7] = out_wire[8] | layer_1[4];
always @(*) out_wire[6] = out_wire[7] & out_wire[5];
always @(*) out_wire[5] = layer_1[3] | out_wire[4];
always @(*) out_wire[4] = ~( layer_1[3] | layer_1[2] );
always @(*) out_wire[3] = ~( out_wire[4] | (~layer_1[3]) );
always @(*) out_wire[2] = (~out_wire[3]) & out_wire[1];
always @(*) out_wire[1] = (~layer_1[1]) | ~( (~layer_1[1]) & out_wire[0] );
always @(*) out_wire[0] = ~layer_1[0];


initial begin
	forever begin
  		#10;
      	clk = ~clk;
    end
end

always @(posedge clk)
begin
    if (enable == 1) begin
        in_w <= out_wire;
    end
    if (load == 1) begin
        in_w <= `INIT_VALUE;
    end
end

always @(posedge clk)
begin
    out_w <= out_wire;
end


/* Testbench */
initial begin
    load = 0;
    enable = 0;
    #30;
    
    @(posedge clk);
    load = 1;
    @(posedge clk);
    load = 0;
    $display("\nLoad--------------------------------------\n");
    $display("Load 0x%X (0b%16b)", in_w, in_w);
  
    #30;
    
    @(posedge clk);
    enable = 1;
    $display("\nStart-------------------------------------\n");
    repeat(15) begin
        @(posedge clk);
       $display("#%0d", cnt);
        $display("Input:  0b%16b >>", in_w);
        $display("Output: 0b%16b\n", out_wire);
      cnt = cnt + 1;
    end
    enable = 0;
    $display("Stop-------------------------------------");
  	$finish;
end



endmodule