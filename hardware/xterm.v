`timescale 1ns / 1ps

module divider25MHZ(
    input CLK100MHZ,
    output reg CLK25MHZ,
    output reg CLK1HZ
);
  reg [31:0] counter;
  reg [31:0] cnt;  
  always@(posedge CLK100MHZ)begin
    if(counter == 1)begin
        CLK25MHZ <= ~CLK25MHZ;
        counter <= 0;
    end
    else counter <= counter + 1;
    if(cnt == 50000000 - 1)begin
        CLK1HZ <= ~CLK1HZ;
        cnt <= 0;
    end
    else cnt <= cnt + 1;
  end
endmodule

module xterm(
    input CLK100MHZ,   //ϵͳʱ���ź�
    input PS2_CLK,    //���Լ��̵�ʱ���ź�
    input PS2_DATA,  //���Լ��̵Ĵ�������λ
    input BTNC,      //Reset
    input reset,
    output [6:0]SEG,
    output [7:0]AN,     //��ʾɨ�����ASCII��
    //output [15:0] LED,   //��ʾ����״̬
    output [3:0] VGA_R,
    output [3:0] VGA_G,
    output [3:0] VGA_B,
    output  VGA_HS,
    output  VGA_VS
);
// Add your code here
//(* ram_style="block" *) reg [2:0]vgamem [640 * 480 - 1 : 0];
reg vga_ctrl;
wire vgawe;wire kbwe, dwrclk;
wire [31:0] ddatain;
wire [11:0] h_addr;
wire [11:0] v_addr;wire [31:0] daddr;wire dwe;
wire [5:0]vgapixout;wire CLK25MHZ;
wire [18:0] addra;
assign addra = v_addr * 640 + h_addr;
wire [18:0] addrb;
assign addrb = daddr[20:2];
assign vgawe = (daddr[31:20] == 12'h006 && dwe == 1'b1) | (daddr[31:20] == 12'h007 && dwe == 1'b1);
//vga_mem1 vgamemory(.clka(CLK25MHZ),.ena(1'b1),.wea(vgawe),.dina({ddatain[23:22], ddatain[15:14], ddatain[7:6]}),.douta(vgapixout),.addra(addra));
vga_dual_mem vgamemory(.clka(CLK25MHZ),.addra(addra),.wea(1'b0),.douta(vgapixout)
,.dina(6'b0),.clkb(~dwrclk),.web(vgawe),.dinb({ddatain[23:22],ddatain[15:14],ddatain[7:6]}),.addrb(addrb),.ena(1'b1),.enb(1'b1));
wire CLK1HZ;
//clk_wiz_0 myvgaclk(.clk_in1(CLK100MHZ),.reset(rst),.locked(locked),.clk_out1(CLK25MHZ));
divider25MHZ disdsad(.CLK100MHZ(CLK100MHZ),.CLK25MHZ(CLK25MHZ),.CLK1HZ(CLK1HZ));
reg [7:0] screen [29:0][79:0];
reg [7:0] cursor_x;reg [4:0] cursor_y;
reg [4:0]line;
//reg reset;
integer i, m, n;
wire ready;


wire[31:0] keymemout;


assign kbwe = (daddr[31:20] == 12'h003) ? dwe : 0;
KeyboardSim kbsim(.CLK100MHZ(CLK100MHZ),.PS2_CLK(PS2_CLK),.PS2_DATA(PS2_DATA),.BTNC(BTNC)
,.ready(ready)
,.keymemout(keymemout)
,.kbdatain(ddatain)
,.dwrclk(dwrclk)
,.reset(reset)
,.kbaddr(daddr)
,.we(kbwe)
);


wire [7:0] asciiin;

assign asciiin = (v_addr/16 == cursor_y && h_addr/8 == cursor_x) ? ((CLK1HZ == 1) ? screen[v_addr/16][h_addr/8] : 0) : screen[v_addr/16][h_addr/8];

wire [3:0] vgar;
wire [3:0] vgag;
wire [3:0] vgab;
assign VGA_R = (vga_ctrl == 0) ? vgar : {2{vgapixout[5:4]}};
assign VGA_G = (vga_ctrl == 0) ? vgag : {2{vgapixout[3:2]}};
assign VGA_B = (vga_ctrl == 0) ? vgab : {2{vgapixout[1:0]}};

VGASim VGASim_vv(.VGA_R(vgar),.VGA_B(vgab),.VGA_G(vgag),.VGA_HS(VGA_HS),.VGA_VS(VGA_VS),.BTNC(BTNC),.CLK25MHZ(CLK25MHZ),
.h_addr(h_addr),.v_addr(v_addr),.asciiin(asciiin)
,.vgactl(vga_ctrl));


wire [31:0] PC;
assign PC = pipelinecpu.PC;

    wire [31:0] iaddr,idataout;
wire iclk;
wire [31:0] ddataout;
wire drdclk;
wire [2:0]  dop;
wire [15:0] cpudbgdata;
   reg clk;reg [2:0]couter;
   always @(posedge CLK100MHZ)begin
    if(couter == 1)begin
        couter <= 0;
        clk <= ~clk;
    end
    else begin
        couter <= couter + 1;
        clk <= clk;
    end
   end
   reg [31:0] dataout;
//   SingleCycleCPU  mycpu(
//.clock(clk), .reset(reset), 
//				 .InstrMemaddr(iaddr), .InstrMemdataout(idataout), .InstrMemclk(iclk), 
//				 .DataMemaddr(daddr), .DataMemdataout(dataout), .DataMemdatain(ddatain), .DataMemrdclk(drdclk),
//				  .DataMemwrclk(dwrclk), .DataMemop(dop), .DataMemwe(dwe),  .dbgdata(cpudbgdata)); 

rv32ip pipelinecpu(.clock(clk),.reset(reset),.imemaddr(iaddr),.imemdataout(idataout),.imemclk(iclk),.dmemaddr(daddr)
,.dmemdataout(dataout),.dmemdatain(ddatain),.dmemrdclk(drdclk),.dmemwrclk(dwrclk),.dmemop(dop),.dmemwe(dwe),.dbgdata(cpudbgdata));

// instrucation memory
 InstrMem myinstrmem_top(.instr(idataout),.addr(iaddr),.InstrMemEn(1'b1),.clk(iclk)	);
//data memory	
DataMem mydatamem_top(.dataout(ddataout), .clk(dwrclk),  .we(datawe),  .MemOp(dop), .datain(ddatain),.addr(daddr[17:0])); 
   
wire [31:0] vgamemout;
assign datawe = (daddr[31:20] == 12'h001) ? dwe : 1'b0;    
assign vgamemout = screen[lin][col];
//assign dataout = (daddr[31:20]==12'h001)? ddataout : ((daddr[31:20] == 12'h003)? keymemout : ((daddr[31:20] == 12'h002) ? vgamemout : 32'b0));
wire [63:0] now;
always@(*)begin
    if(daddr[31:20] == 12'h001)begin
        dataout = ddataout;
    end
    else if(daddr[31:20] == 12'h003)begin
        dataout = keymemout;
    end
    else if(daddr[31:20] == 12'h002)begin
        dataout = vgamemout;
    end
    else if(daddr[31:20] == 12'h005)begin
        dataout = now[31:0];
    end
end



wire [6:0] lin, col;
assign lin = (daddr >> 7) & 7'h7f;
assign col = daddr & 7'h7f;

wire [19:0] vgalinecol;
assign vgalinecol = (daddr[19:0] >> 2);

integer j,k;


reg twe;
//assign twe = (daddr[31:20] == 12'h008 && dwe == 1'b1);
timer cputime(.CLK100MHZ(CLK100MHZ),.now(now),.we(twe),.reset(reset));


always@(negedge dwrclk or posedge reset)begin
if(reset)begin
    for(j = 0; j < 30; j = j + 1)begin
        for(k = 0; k < 80; k = k + 1)begin
            screen[j][k] <= 0;
        end
    end
    cursor_x<=0;
    cursor_y<=0;
end
else if(daddr[31:20] == 12'h002 && dwe == 1'b1)begin
        screen[lin][col] <= ddatain;
        if(ddatain == 32'h5f)begin
            cursor_x <= col;
            cursor_y <= lin;
        end
        else begin
            cursor_x <= cursor_x;
            cursor_y <= cursor_y;
        end
    end
else if(daddr[31:20] == 12'h004 && dwe == 1'b1) begin
    vga_ctrl <= ddatain;
end

else if(daddr[31:20] == 12'h008 && dwe == 1'b1)begin
    twe <= 1'b1;
end
else begin
    twe <= 1'b0;
    end
//else if(daddr[31:20] == 12'h005 && dwe == 1'b1)begin
  //  if(ddatain == 0)begin
  //      vgamem[vgalinecol] <= 0;
  //  end
  //  else begin
  //      vgamem[vgalinecol] <= {{ddatain[23]}, {ddatain[15]}, {ddatain[7]}};
  //  end
//end

end



 seg7decimal cpuseg(.seg(SEG),.an(AN),.clk(CLK100MHZ),.x(PC));

endmodule

