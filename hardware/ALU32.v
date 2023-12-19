`timescale 1ns / 1ps

module ALU32(
output  reg [31:0] result,       //32位运算结果
output  reg zero,             //结果为0标志位
input   [31:0] dataa,          //32位数据输入，送到ALU端口A   
input   [31:0] datab,          //32位数据输入，送到ALU端口B  
input   [3:0] aluctr        //4位ALU操作控制信号
); 
//add your code here
    reg SUBctr,SIGctr,ALctr,SFTctr; reg[2:0]OPctr;
    wire [31:0]f;wire[31:0] dout;
    wire OF,SF,ZF,CF,cout;
Adder32 my_adder(.f(f),.OF(OF),.SF(SF),.ZF(ZF),.CF(CF),.cout(cout),.x(dataa),.y(datab),.sub(SUBctr));

barrelsft32 my_barrel(.dout(dout),.din(dataa),.shamt(datab[4:0]),.LR(SFTctr),.AL(ALctr));
    
    always@(*)begin 
        
        case(aluctr)
            4'b0000: begin SUBctr = 0; OPctr = 3'b000; end 
            4'b0001: begin ALctr = 0; SFTctr = 1; OPctr = 3'b100; end
            4'b0010: begin SUBctr = 1;SIGctr=1;OPctr = 3'b110; end
            4'b0011: begin SUBctr = 1;SIGctr=0;OPctr=3'b110;end
            4'b0100: begin OPctr = 3'b011; end
            4'b0101: begin ALctr = 0; SFTctr = 0; OPctr = 3'b100; end
            4'b0110: begin OPctr = 3'b010; end
            4'b0111: begin OPctr = 3'b001; end
            4'b1000: begin SUBctr = 1; OPctr = 3'b000; end
            4'b1101: begin ALctr = 1; SFTctr = 0;OPctr = 3'b100; end
            4'b1111: begin OPctr = 3'b101; end
            default;
        endcase 
        
        case(OPctr)
            3'b000: begin result = f;end
            3'b001: begin result = dataa & datab; end
            3'b010: begin result = dataa | datab; end
            3'b011: begin result = dataa ^ datab; end
            3'b100: begin result = dout; end
            3'b101: begin result = datab; end
            3'b110: begin 
               result = {31'b0,(SIGctr == 1)? (OF ^ SF) : CF};
            end
            default;
        endcase
        zero = ZF;//(result == 0)? 1'b1:1'b0;
    end
endmodule