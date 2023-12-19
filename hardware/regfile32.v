`timescale 1ns / 1ps

module regfile32(
input reset,
input [31:0] a0,
	output wire [31:0] busa,   //�Ĵ���ra�������
	output wire [31:0] busb,   //�Ĵ���rb�������
	input clk,
	input [4:0] ra,           //���Ĵ������ra
	input [4:0] rb,          //���Ĵ������rb
	input [4:0] rw,          //д�Ĵ������rw
	input [31:0] busw,       //д�����ݶ˿�
	input we	             //дʹ�ܶˣ�Ϊ1ʱ����д��
	);
  (* ram_style="registers" *) reg [31:0] regfiles[31:0];      //�ۺ�ʱʹ�üĴ���ʵ�ּĴ�����
  	initial
	begin
		regfiles[0]=32'b0;
	end
	assign busa=regfiles[ra]; ////���˿�ra
	assign busb=regfiles[rb];
	integer i;
	always@(posedge clk or posedge reset)
	begin
	   if(reset) begin
	       for(i = 0; i <= 31; i = i + 1)
	       begin 
	           regfiles[i] <= 0;
	       end
	   end
	   else if(we==1'b1) regfiles[rw] <= (rw==5'b00000)? 32'b0:busw; //д�˿�
	end
	
endmodule
