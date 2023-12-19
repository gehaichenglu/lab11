`timescale 1ns / 1ps

    module BranchControl(
    output reg Branchsel, PCsel,
    output flushIF, flushID,
    input zero, result0,
    input [2:0] Branch
   );
    assign flushIF = PCsel;
    assign flushID = PCsel;
    always @ (*) begin
        case (Branch)
        
            3'b000: begin Branchsel = 1'b0; PCsel = 1'b0; end //����תָ��
            3'b001: begin Branchsel = 1'b0; PCsel = 1'b1; end //jal: ��������תPCĿ��
            3'b010: begin Branchsel = 1'b1; PCsel = 1'b1; end //jalr: ��������ת�Ĵ���Ŀ��
            3'b100: begin Branchsel = 1'b0; PCsel = (zero===1'bx)?1'b1:zero; end //beq: ������֧������ �޸Ĺ�
            3'b101: begin Branchsel = 1'b0; PCsel = (zero===1'bx)?1'b1:~zero; end //bne: ������֧�������� �޸Ĺ�
            3'b110: begin Branchsel = 1'b0; PCsel = (result0===1'bx)?1'b1:result0; end //blt, bltu: ������֧��С��
            3'b111: begin Branchsel = 1'b0; PCsel = (result0===1'bx)?1'b1:(zero | ~result0); end //bge, bgeu: ������֧�����ڵ���
            default: begin Branchsel = 1'b0; PCsel = 1'b0; end
            
        endcase
    end
endmodule
