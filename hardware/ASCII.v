`timescale 1ns / 1ps

module ASCII(
input clk,
input [7:0] addr,
output [127:0] outdata
    );

reg [127:0] myrom[255:0];

initial
begin
    $readmemh("G:/vivado_workdict/lab6/ASCout.txt", myrom, 0, 255);
end
assign outdata = myrom[addr];

endmodule
