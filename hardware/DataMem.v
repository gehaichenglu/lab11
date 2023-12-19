`timescale 1ns / 1ps

module DataMem(
   output reg [31:0] dataout,     
   input clk,                   
   input we,                   
   input [2:0] MemOp,        
   input [31:0] datain,        
   input [17:0] addr          
);
(* ram_style="block" *)  reg [31:0] ram [2**16-1:0]; 
initial begin
       $readmemh( "G:/vivado_workdict/lab11pipelineCPU/main_d.hex",ram);
end
//from mem32b
reg [31:0] intmp; 
reg [31:0] outtmp; 

reg [20:0]i;
always @(posedge clk) begin
 outtmp <= ram[addr[17:2]]; 

end
always @(negedge clk) begin
 if (we) ram[addr[17:2]] <= intmp; 
end

always @(*)
begin
 if (~we) begin 
 case ({MemOp,addr[1:0]})
 5'b01000: begin dataout = outtmp; end
 
 5'b10000: begin dataout = {24'h000000, outtmp[7:0]}; end
 5'b10001: begin dataout = {24'h000000, outtmp[15:8]}; end
 5'b10010: begin dataout = {24'h000000, outtmp[23:16]}; end
 5'b10011: begin dataout = {24'h000000, outtmp[31:24]}; end
 
 5'b10100: begin dataout = {16'h0000, outtmp[15:0]}; end
 5'b10110: begin dataout = {16'h0000, outtmp[31:16]}; end
 
 5'b00000: begin dataout = {{24{outtmp[7]}}, outtmp[7:0]}; end
 5'b00001: begin dataout = {{24{outtmp[15]}}, outtmp[15:8]}; end
 5'b00010: begin dataout = {{24{outtmp[23]}}, outtmp[23:16]}; end
 5'b00011: begin dataout = {{24{outtmp[31]}}, outtmp[31:24]}; end
 
 5'b00100: begin dataout = {{16{outtmp[15]}}, outtmp[15:0]}; end
 5'b00110: begin dataout = {{16{outtmp[31]}}, outtmp[31:16]}; end

 default:dataout = outtmp;
 endcase

 end
 else begin 
 case ({MemOp,addr[1:0]})
 5'b01000: begin intmp = datain; end
 
 5'b00000: begin intmp = {outtmp[31:8], datain[7:0]}; end
 5'b00001: begin intmp = {outtmp[31:16], datain[7:0],outtmp[7:0]}; end
 5'b00010: begin intmp = {outtmp[31:24], datain[7:0],outtmp[15:0]}; end
 5'b00011: begin intmp = {datain[7:0],outtmp[23:0]}; end
 
 5'b00100: begin intmp = {outtmp[31:16], datain[15:0]}; end
 5'b00110: begin intmp = {datain[15:0],outtmp[31:16]}; end
 default:intmp = datain;
 endcase
 end
end
//end

endmodule
