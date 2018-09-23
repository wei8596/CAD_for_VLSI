//------------------------------------------------
// FILE: top.v
// AUTHOR: YiLi Lin
// EMAIL: yllin@smims.com
// $Id$
// ABSTRATE: Top module for this project.
//           SMIMS Engine Version: 2.0
// FUNCTION: 1)
//
// MODIFICATION HISTORY:
// $Log$
//       2007/10/15   Version 1.0
//------------------------------------------------

//`include "ezIF.v"
//`include "Example.v"

module  top(
   input   SDK_CLK,
   input   SDK_RSTN,

   input   [7:0]   SDK_CH,
      
   output   SDK_RD,
   input   [15:0]   SDK_DI,
   input   SDK_AlmostEmpty,
   input   SDK_Empty,
   
   output   SDK_WR,
   output   [15:0]   SDK_DO,
   input   SDK_AlmostFull,
   input   SDK_Full,
   
   output  [7:0]   LED
);
   
   wire   Start,Finish;
  
   wire   in_wren;
   wire   [15:0]   in_addr;
   wire   [15:0]   out_addr;
   wire   [15:0]   RdData;
   wire   [15:0]   RdAddr;
	 wire   [15:0]   WrAddr;
   wire   [15:0]   WrData;
   wire   WrEn;
 

   ezIF   interface_unit(
   
   .SDK_CLK(SDK_CLK),
   .SDK_RSTN(SDK_RSTN),
   .SDK_CH(SDK_CH),

   .SDK_RD(SDK_RD),
   .SDK_DI(SDK_DI), 
   .SDK_AlmostEmpty(SDK_AlmostEmpty),
   .SDK_Empty(SDK_Empty),
   .in_wren_o(in_wren),
   .in_addr_o(in_addr),
   
   .SDK_WR(SDK_WR),
   .SDK_AlmostFull(SDK_AlmostFull),
   .out_addr_o(out_addr),
   
   
   .Exec(Start),
   .Finish(Finish),
   .SendCnt('d0),
   .AsIncome(1'b1)
   );
   
   Example   user_unit(
      .clk(SDK_CLK),
      .rst_n(SDK_RSTN),
      .Start(Start),
      .Finish(Finish),
      
      .RdAddr(out_addr[1:0]),
      .RdData(SDK_DO),
      
      .WrAddr(in_addr[1:0]),
      .WrEn(in_wren),
      .WrData(SDK_DI)
      
   );
     
   assign   LED = 8'b11111111;
   
endmodule