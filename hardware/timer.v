`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/14 11:28:46
// Design Name: 
// Module Name: timer
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

module timer(
input CLK100MHZ,
output [63:0] now,
input we,
input reset
    );
    
    reg [6:0] cnt;
    reg usclk;
    always@(posedge CLK100MHZ)begin
        if(cnt == 49)begin
            cnt <= 0;
            usclk <= ~usclk;
        end
        else begin
            cnt <= cnt + 1;
            usclk <= usclk;
        end
    end
    
reg [63:0] us;
assign now = us;
always@(posedge usclk or posedge we)begin
    if(we)begin
        us <= 0;
    end
    else begin
        us <= us + 1;
    end
end
    

endmodule
