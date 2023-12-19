`timescale 1ns / 1ps

module SingleCycleCPU(
 	input 	      clock,
	input 	      reset,
	output [31:0] InstrMemaddr,      //ָ��洢����ַ
	input  [31:0] InstrMemdataout,   //ָ������
	output        InstrMemclk,       // ָ��洢����ȡʱ�ӣ�Ϊ��ʵ���첽��ȡ�����ö�ȡʱ�Ӻ�д��ʱ�ӷ���
	output [31:0] DataMemaddr,       //���ݴ洢����ַ
	input  [31:0] DataMemdataout,   //���ݴ洢���������
	output [31:0] DataMemdatain,    //���ݴ洢��д������
	output 	      DataMemrdclk,     //���ݴ洢����ȡʱ�ӣ�Ϊ��ʵ���첽��ȡ�����ö�ȡʱ�Ӻ�д��ʱ�ӷ���
	output	      DataMemwrclk,      //���ݴ洢��д��ʱ��
	output [2:0]  DataMemop,         //���ݶ�д�ֽ��������ź�
	output        DataMemwe,         //���ݴ洢��д��ʹ���ź�
	output reg [31:0] dbgdata            //debug�����źţ����16λָ��洢����ַ��Ч��ַ
);
reg [31:0] PC;
reg [31:0] nxtPC;
wire done;
wire [31:0] instr;assign instr = InstrMemdataout;

assign done = (reset == 1'b1 ? 0 : (instr == 32'hdead10cc) ? 1 : 0);
always @(posedge clock or posedge reset) begin//��ȷ��
        if (reset) PC <= 32'h00000000;
        else begin
			if (!done) PC <= nxtPC;
		end
    end
assign InstrMemaddr = nxtPC;
assign InstrMemclk = clock; assign DataMemrdclk = clock; assign DataMemwrclk = ~clock;

always @(negedge clock) begin
		dbgdata <= PC;
	end

wire [6:0]opcode;wire [4:0]rd;wire[2:0]funct3;wire [4:0]rs1;wire[4:0]rs2;wire[6:0]funct7;
InstrParse instrparse(.instr(InstrMemdataout),.opcode(opcode),.rd(rd),.funct3(funct3),.rs1(rs1),.rs2(rs2),.funct7(funct7));

wire [2:0]ExtOp;wire RegWr; wire ALUASrc; wire [1:0]ALUBSrc; wire[3:0]ALUctr;wire[2:0]Branch;wire MemtoReg;wire MemWr;wire [2:0]MemOp;
    Control cpucontrol(
    .ban(done | reset),
    .opcode(opcode),.funct3(funct3),.funct7(funct7),.ExtOp(ExtOp)
    ,.RegWr(RegWr),.ALUASrc(ALUASrc),.ALUBSrc(ALUBSrc),.ALUctr(ALUctr),.Branch(Branch),.MemtoReg(MemtoReg),.MemWr(MemWr),.MemOp(MemOp));

wire [31:0] imm;
    InstrToImm cpuimm(.imm(imm),.instr(InstrMemdataout),.ExtOp(ExtOp));
    
   wire [31:0] busa; wire[31:0] busb; wire [31:0] busw; 
 regfile32 myregfile(.reset(reset),.busa(busa),.busb(busb),.clk(clock),.ra(rs1),.rb(rs2),.rw(rd),.we(RegWr),.busw(busw));   

wire [31:0] result;wire zero;
    wire [31:0] dataa;wire [31:0]datab;
    assign dataa = (ALUASrc == 1'b1)? dbgdata : busa;
    assign datab = (ALUBSrc == 2'b00) ? busb : ((ALUBSrc == 2'b01) ? 32'h00000004 : imm);
    ALU32 cpualu(.result(result),.zero(zero),.dataa(dataa),.datab(datab),.aluctr(ALUctr));

wire [31:0] dataout;
assign DataMemaddr = result;
assign DataMemdatain = busb;
assign DataMemwe = (~reset & ~done & MemWr);
assign DataMemop = MemOp;
assign dataout = DataMemdataout;
assign busw = (MemtoReg == 1) ? dataout : result;

wire NxtASrc; wire NxtBSrc;wire[31:0] nPC;
BranchControl mycpubranch(.NxtASrc(NxtASrc),.NxtBSrc(NxtBSrc),.zero(zero),.Branch(Branch),.result0(result[0]));
    nextPC cpunextPC(.nxtPC(nPC),.BusA(busa),.curPC(PC),.Imm(imm),.NxtASrc(NxtASrc),.NxtBSrc(NxtBSrc),.reset(reset | done));
    
always@(*)begin
    nxtPC = nPC;
end
endmodule
