`timescale 1ns / 1ps

module ROM(clk, addr, data);
 input		clk;
 input [2:0] addr;
 output reg[8:0] data;

 always @(*)
 begin
	 case(addr)
		 3'b000: data <= 9'b001001100;
		 3'b001: data <= 9'b010010110;
		 3'b010: data <= 9'b111010101;
		 3'b011: data <= 9'b110101100;
		 3'b100: data <= 9'b010000000;
		 3'b101: data <= 9'b110010101;
		 3'b110: data <= 9'b111101100;
		 3'b111: data <= 9'b000011101;
	 endcase
 end

endmodule
