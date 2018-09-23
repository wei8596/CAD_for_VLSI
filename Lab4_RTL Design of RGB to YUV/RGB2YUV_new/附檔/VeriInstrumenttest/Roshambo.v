//------------------------------------------------
// FILE: Roshambo.v
// AUTHOR: Yen-Te, Shih
// $Id$
// ABSTRACT:	Rock Paper Scissors
// KEYWORDS:  Rochambeau, Roshambo, Rock Paper Scissors.
// MODIFICATION HISTORY:
// $Log$
//	Yen-Te, Shih	03/06/09	origial
//  Yen-Te, Shih & Lora Chang  	03/10/09	modify v1.0
// DEVICE:
//  DIP Switch : rst
//  Push Button : Chan
//  8x8 Matrix LED : R, C
// (c) copyright 2004-2011 SMIMS Technology Corp. All rights reserved
//------------------------------------------------
// Device
// DIP or Button : rst
// Button : chan
// 8x8 Matrix LED : R, C
//------------------------------------------------
module Roshambo(clk, rst, chan, R, C);
    input clk;
    input rst;
    input chan;
    output [7:0] R, C;
    
    reg    [7:0] R, C;
    reg    [1:0] what, i; // "what" variable is the "i" readed when "ch" = 1.
    reg    [2:0] cnt; // counter 0 ~ 7
	
	// ---------------
   // Clock Generator
   // ---------------
   parameter ms = 18; // Clock rate 48M/2^ms 
   reg [ms-1:0]   div_cnt;
   wire           myClk;
   always @(posedge clk)
         div_cnt <= div_cnt + 1;	
   assign myClk = div_cnt[ms-1];
   
	always@(posedge myClk)
	 
	  if(rst) begin
				R    <= 8'h80;
				cnt  <= 3'd0;	
				C    <= 8'd0;
				i    <= 2'd0;
				what <= 2'd0;
	  	end
	  else begin
				R    <= {R[6:0], R[7]}; // Rotate R left one bit.
				cnt  <= (cnt == 3'd7) ? 3'd0 : (cnt + 3'd1);		
				i    <= chan ? i : ( (i == 2'd2) ? 2'd0 : i + 2'd1 );
				what <= chan ? i : what;
				
				if(what == 2'b00)
					case(cnt)
							3'd0: C <= 8'b10000001;
							3'd1: C <= 8'b01000010; 
							3'd2: C <= 8'b01101100;
							3'd3: C <= 8'b01101100;
							3'd4: C <= 8'b01111000;
							3'd5: C <= 8'b00111100;
							3'd6: C <= 8'b00111100;
							3'd7: C <= 8'b00111100;
						default: C <= 8'b00000000;
					endcase
				else if(what == 2'b01)
					case(cnt)
							3'd0: C <= 8'b00000000; 
							3'd1: C <= 8'b00000000;
							3'd2: C <= 8'b01111110;
							3'd3: C <= 8'b11111111;
							3'd4: C <= 8'b11111111;
							3'd5: C <= 8'b11111111;
							3'd6: C <= 8'b01111110;
							3'd7: C <= 8'b00111100;
						default: C <= 8'b00000000;
					endcase
				else
					case(cnt)
					    3'd0: C <= 8'b00001000;
							3'd1: C <= 8'b01001001;
							3'd2: C <= 8'b00101010; 
							3'd3: C <= 8'b10111100;
							3'd4: C <= 8'b10111101;
							3'd5: C <= 8'b01111110;
							3'd6: C <= 8'b01111110;
							3'd7: C <= 8'b01111100;
						default: C <= 8'b00000000;
					endcase				
	  	end
		
endmodule
