`timescale 1ns / 1ps

module KeyboardSim(
    input CLK100MHZ,   //ϵͳʱ���ź�
    input PS2_CLK,    //���Լ��̵�ʱ���ź�
    input PS2_DATA,  //���Լ��̵Ĵ�������λ
    input BTNC,      //Reset
   // output reg breakcode,
    output wire ready,
    output reg [31:0]keymemout,
    input [31:0]kbdatain,
    input dwrclk,
    input reset,
    input [31:0]kbaddr,
    input we
   // output wire [7:0] ascii
    );
reg breakcode;
    reg CLK50MHZ;
wire [7:0] asciicode;
reg [31:0]tail, head;//����������
reg [31:0] kbdata[31:0];
wire [31:0] keycodeout;
kbcode2ascii kbcodeascii(.asciicode(asciicode),.kbcode(keycodeout[7:0]));

//reg breakcode;//��¼�Ƿ���������
KeyBoardReceiver kbdr(.ready(ready),.keycodeout(keycodeout),.clk(CLK50MHZ),.kb_clk(PS2_CLK),.kb_data(PS2_DATA));
integer i;integer idx;

always@(negedge ready or posedge reset)begin
    if(reset)begin
        tail <= 0;
        for(i = 0; i < 32; i = i + 1)begin
            kbdata[i] <= 0;
        end
    end
    else begin
            if(((tail +  1) & 5'h1f) == head)begin
                tail <= tail;
            end
            else begin
                kbdata[(tail + 1)& 5'h1f] <= {24'h0, keycodeout[7:0]};
                tail <= (tail + 1)& 5'h1f;
            end
    end
end

always@(posedge CLK100MHZ)begin//����ڶ��always�����渳ֵ���ܻ�������
    CLK50MHZ <= ~CLK50MHZ;
end


reg [31:0] intmp; 
reg [31:0] outtmp; 


always @(posedge dwrclk) begin
 if(kbaddr == 32'h003ffff0)begin
    outtmp <= head;
 end
 else if(kbaddr == 32'h003fffe0)begin
    outtmp <= tail;
 end
 else begin
    idx = (kbaddr - 32'h0030000) >> 2;
    outtmp <= kbdata[(idx + 1) & 5'h1f];
 end

end
always @(negedge dwrclk) begin
 if (we) begin
    if(kbaddr == 32'h003ffff0)begin
        head <= intmp;
    end
 end
end

always @(*)
begin
 if (~we) begin 
    keymemout = outtmp;
 end
 else begin 

 intmp = kbdatain;

 end
end
endmodule