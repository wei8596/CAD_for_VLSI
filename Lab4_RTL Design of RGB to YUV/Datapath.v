`timescale 1ns/1ps
`define bits 9

module Datapath(inportR, inportG, inportB, control, clk, rst_n, outportY, outportU, outportV, done);
 input [`bits-1:0]inportR, inportG, inportB;
 input [21:0]control;
 input clk, rst_n, done;
 output [`bits-1:0] outportY, outportU, outportV;

 wire	[`bits-1:0] M1_OUT, M2_OUT, M3_OUT, M4_OUT, M5_OUT, M6_OUT, M7_OUT;
 wire	[`bits-1:0] M8_OUT, M9_OUT, Fadd, Fmul, R1, R2, R3, R4, R5, R6, data;

 Register r1( .D(M4_OUT), .reset(rst_n), .clk(clk), .load(control[21:21]), .Q(R1));
 Register r2( .D(M5_OUT), .reset(rst_n), .clk(clk), .load(control[20:20]), .Q(R2));
 Register r3( .D(M6_OUT), .reset(rst_n), .clk(clk), .load(control[19:19]), .Q(R3));
 Register r4( .D(M7_OUT), .reset(rst_n), .clk(clk), .load(control[18:18]), .Q(R4));
 Register r5( .D(M8_OUT), .reset(rst_n), .clk(clk), .load(control[17:17]), .Q(R5));
 Register r6( .D(M9_OUT), .reset(rst_n), .clk(clk), .load(control[16:16]), .Q(R6));
 MUX3	M1( .A(R3), .B(R2), .C(R1), .S(control[12:11]), .Y(M1_OUT) );
 MUX4	M2( .A(9'b010000000), .B(R5), .C(R4), .D(R1), .S(control[10:9]), .Y(M2_OUT) );
 MUX4	M3( .A(R6), .B(R3), .C(R2), .D(R5), .S(control[8:7]), .Y(M3_OUT) );
 MUX2	M4( .A(inportR), .B(Fadd), .S(control[6:6]), .Y(M4_OUT) );
 MUX3	M5( .A(inportG), .B(Fmul), .C(Fadd), .S(control[5:4]), .Y(M5_OUT) );
 MUX2	M6( .A(inportB), .B(Fadd), .S(control[3:3]), .Y(M6_OUT) );
 MUX2	M7( .A(Fmul), .B(Fadd), .S(control[2:2]), .Y(M7_OUT) );
 MUX2	M8( .A(Fmul), .B(Fadd), .S(control[1:1]), .Y(M8_OUT) );
 MUX2	M9( .A(Fmul), .B(Fadd), .S(control[0:0]), .Y(M9_OUT) );
 Mul FU1( .A(M1_OUT), .B(data), .Mul(Fmul) );
 Add FU2( .A(M2_OUT), .B(M3_OUT), .Add(Fadd) );
 ROM FU3( .clk(clk), .addr(control[15:13]), .data(data) );

 Register r7(R2, rst_n, clk, done, outportY);
 Register r9(R1, rst_n, clk, done, outportU);
 Register r8(R3, rst_n, clk, done, outportV);
endmodule
