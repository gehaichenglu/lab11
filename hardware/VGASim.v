`timescale 1ns / 1ps

module VGASim(
    input CLK25MHZ,        //ϵͳʱ���ź�
    input  BTNC,           // ��λ�ź�
    output [3:0] VGA_R,    //��ɫ�ź�ֵ
    output [3:0] VGA_G,    //��ɫ�ź�ֵ
    output [3:0] VGA_B,     //��ɫ�ź�ֵ
    output  VGA_HS,         //��ͬ���ź�
    output  VGA_VS,          //֡ͬ���ź�
    output wire [11:0] h_addr,
    output wire [11:0] v_addr,
    input [7:0] asciiin,
    input vgactl
 );
wire [11:0] vga_data;
wire valid;
wire [11:0] H_addr;
wire [11:0] V_addr;
assign h_addr = H_addr;
assign v_addr = V_addr;
//wire CLK25MHZ;
//clk_wiz_0 myvgaclk(.clk_in1(CLK100MHZ),.reset(rst),.locked(locked),.clk_out1(CLK25MHZ));
//divider divider111(.CLK100MHZ(CLK100MHZ),.CLK25MHZ(CLK25MHZ));

VGACtrl vgactrl(.pix_x(H_addr),.pix_y(V_addr),.hsync(VGA_HS),.vsync(VGA_VS),.pix_valid(valid),.pix_clk(CLK25MHZ),.pix_rst(BTNC));
VGADraw vgadraw(.pix_data(vga_data),.pix_x(H_addr),.pix_y(V_addr),.pix_valid(valid),.pix_clk(CLK25MHZ),.asciiin(asciiin));

assign VGA_R=vga_data[11:8];
assign VGA_G=vga_data[7:4];
assign VGA_B=vga_data[3:0];
endmodule
