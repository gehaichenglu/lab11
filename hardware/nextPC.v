`timescale 1ns / 1ps

module nextPC(
input reset,
    output [31:0] nxtPC,     //��һ��ȡָ���ַ��32λ��ȡ��16λ
    input [31:0] BusA,       //BusA
    input [31:0] curPC,
    input [31:0] Imm,   //PCֵ��������
    input NxtASrc, NxtBSrc   //ѡ���źţ��ɷ�֧���Ʋ�������
    );
    wire [31:0] NxtA, NxtB;
    assign NxtA = NxtASrc ? BusA&32'hfffffffe:curPC;//�޸Ĺ�
    assign NxtB = NxtBSrc ? Imm&32'hfffffffe:32'd4;//�޸Ĺ�
    assign nxtPC=(reset) ? curPC : (NxtA+NxtB);
endmodule
