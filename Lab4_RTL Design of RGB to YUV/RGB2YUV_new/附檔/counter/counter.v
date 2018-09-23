
module counter(
  input                clk,
  input                rst_n,

  input                dec_en,

  output         [3:0] cnt_out);

  // Flip-flops
  reg            [3:0] cnt_q, cnt_d;

  // Output
  assign cnt_out = cnt_q;

  always@*
  begin
    cnt_d = (dec_en) ? cnt_q - 4'd1 : cnt_q + 4'd1;
  end

  always@(posedge clk, negedge rst_n)
  begin
    if(~rst_n)
      cnt_q <= 4'd0;
    else
      cnt_q <= cnt_d;
  end
endmodule
