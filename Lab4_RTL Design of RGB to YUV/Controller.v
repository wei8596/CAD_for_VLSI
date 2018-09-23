`timescale 1ns/1ps
`define bits 9

`define	S0 4'b0000
`define	S1 4'b0001
`define	S2 4'b0010
`define	S3 4'b0011
`define	S4 4'b0100
`define	S5 4'b0101
`define	S6 4'b0110
`define	S7 4'b0111
`define	S8 4'b1000
`define	S9 4'b1001
`define	S10 4'b1010
`define	S11 4'b1011

module Controller(start, rst_n, clk, done, control);
input	start, rst_n, clk;
output reg	done;
output reg	[21:0] control;

reg	[3:0] Current_State, Next_State;

always @(posedge clk or negedge rst_n)begin
	if(!rst_n)
		Current_State <= `S0;
	else
		Current_State <= Next_State;
end

always @(Current_State or start)
begin
	case (Current_State)
	`S0:
	begin
		control = 22'b1_1_1_0_0_0_000_00_00_00_0_00_0_0_0_0;//control = 22'br1_r2_r3_r4_r5_r6_ROM_M1_M2_M3_M4_M5_M6_M7_M8_M9;
		done = 1'b0;
		if(~start)
			Next_State = `S0;
		else
			Next_State = `S1;
	end

	`S1:
	begin
		control = 22'b0_0_0_1_0_0_000_10_00_00_0_00_0_0_0_0;
		done = 1'b0;
		Next_State = `S2;
	end

	`S2:
	begin
		control = 22'b0_0_0_0_1_0_001_01_00_00_0_00_0_0_0_0;
		done = 1'b0;
		Next_State = `S3;
	end

	`S3:
	begin
		control = 22'b0_0_0_1_1_0_010_10_10_11_0_00_0_1_0_0;
		done = 1'b0;
		Next_State = `S4;
	end

	`S4:
	begin
		control = 22'b0_0_0_0_0_1_011_01_00_00_0_00_0_0_0_0;
		done = 1'b0;
		Next_State = `S5;
	end

	`S5:
	begin
		control = 22'b0_0_0_0_1_1_100_00_01_00_0_00_0_0_0_1;
		done = 1'b0;
		Next_State = `S6;
	end

	`S6:
	begin
		control = 22'b1_0_0_0_1_0_100_10_00_11_1_00_0_0_0_0;
		done = 1'b0;
		Next_State = `S7;
	end

	`S7:
	begin
		control = 22'b1_1_0_0_0_0_101_01_11_00_1_01_0_0_0_0;
		done = 1'b0;
		Next_State = `S8;
	end
	
	`S8:
	begin
		control = 22'b0_1_0_0_1_0_110_00_01_10_0_01_0_0_1_0;
		done = 1'b0;
		Next_State = `S9;
	end
	
	`S9:
	begin
		control = 22'b0_1_1_0_0_0_111_00_00_10_0_01_1_0_0_0;
		done = 1'b0;
		Next_State = `S10;
	end
	
	`S10:
	begin
		control = 22'b0_1_0_0_0_0_000_00_10_10_0_10_0_0_0_0;
		done = 1'b0;
		Next_State = `S11;
	end
	
	`S11:
	begin
		control = 22'b0_0_1_0_0_0_000_00_01_01_0_00_1_0_0_0;
		done = 1'b1;
		Next_State = `S0;
	end
	
	default:
	begin
		control = 22'b0_0_1_0_0_0_000_00_01_01_0_00_1_0_0_0;
		done = 1'b1;
		Next_State = `S0;
	end
	endcase
end

endmodule
