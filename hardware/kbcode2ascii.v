`timescale 1ns / 1ps

module kbcode2ascii(
      output[7:0] asciicode,
      input [7:0] kbcode
);
    reg [7:0] kb_mem[255:0];
    initial
    begin
     $readmemh("G:/vivado_workdict/lab5/scancode.txt", kb_mem, 0, 255);  //�޸�scancode.txt���·��
    end
    assign   asciicode = kb_mem[kbcode];
endmodule
