`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/28 10:37:21
// Design Name: 
// Module Name: SingleCycleCPU_top
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module pipelineCPU_top(
input CLK100MHZ,
input [15:0] a0,
input reset,
output [15:0] a0_out,
output [6:0] SEG,
output [7:0] AN
    );
    
    wire [31:0] iaddr,idataout;
wire iclk;
wire [31:0] daddr,ddataout,ddatain;
wire drdclk, dwrclk, dwe;
wire [2:0]  dop;
wire [31:0] cpudbgdata;
   wire clk;reg [2:0]couter;assign clk = CLK100MHZ;
   //always @(posedge CLK100MHZ)begin
     //clk <= CLK100MHZ;
   //end
   
   rv32ip  mycpu_top(
   .a0({16'h000000, a0}),
.clock(clk), .reset(reset), 
				 .imemaddr(iaddr), .imemdataout(idataout), .imemclk(iclk), 
				 .dmemaddr(daddr), .dmemdataout(ddataout), .dmemdatain(ddatain), .dmemrdclk(drdclk),
				  .dmemwrclk(dwrclk), .dmemop(dop), .dmemwe(dwe),  .dbgdata(cpudbgdata)); 
// instrucation memory
 InstrMem myinstrmem_top(.instr(idataout),.addr(iaddr),.InstrMemEn(1'b1),.clk(iclk)	);
//data memory	
DataMem mydatamem_top(.dataout(ddataout), .clk(dwrclk),  .we(dwe),  .MemOp(dop), .datain(ddatain),.addr(daddr[17:0])); 
    
    assign a0_out = mycpu_top.myregfile.regfiles[10][15:0];
    wire [31:0]a0out;
    assign a0out = mycpu_top.myregfile.regfiles[10];
    
    seg7decimal cpuseg(.seg(SEG),.an(AN),.clk(CLK100MHZ),.x(a0out));
endmodule
