`define CLAMP(value,min,max) ((value<min)?min:(value>max?max:value))
`define CLAMP_DOWN(value,min) ((value<min)?min:value)
`define CLAMP_UP(value,max) (value>max?max:value)

module ball_move  (
		 input clk,
		 input rst,
		 input wire [3:0] direction,
		 input move,
		 output wire [12:0] x_out,
		 output wire [12:0] y_out
	);
   parameter move_speed=1;
	
	reg [12:0] x;
	reg [12:0] y;
	
	assign x_out = x;
	assign y_out = y;
	
	always @(posedge clk) begin
		if (rst) begin
			x <= 320*4;
			y <= 240*4;
		end
		else
		if (move)
			case(direction)
			4'd0    : begin x<=`CLAMP_UP(x+0*move_speed,630*4); y<=`CLAMP_DOWN(y-4*move_speed,10*4); end
			4'd1    : begin x<=`CLAMP_UP(x+1*move_speed,630*4); y<=`CLAMP_DOWN(y-3*move_speed,10*4); end
			4'd2    : begin x<=`CLAMP_UP(x+2*move_speed,630*4); y<=`CLAMP_DOWN(y-2*move_speed,10*4); end
			4'd3    : begin x<=`CLAMP_UP(x+3*move_speed,630*4); y<=`CLAMP_DOWN(y-1*move_speed,10*4); end
			4'd4    : begin x<=`CLAMP_UP(x+4*move_speed,630*4); y<=`CLAMP_UP(y+0*move_speed,470*4); end
			4'd5    : begin x<=`CLAMP_UP(x+3*move_speed,630*4); y<=`CLAMP_UP(y+1*move_speed,470*4); end
			4'd6    : begin x<=`CLAMP_UP(x+2*move_speed,630*4); y<=`CLAMP_UP(y+2*move_speed,470*4); end
			4'd7    : begin x<=`CLAMP_UP(x+1*move_speed,630*4); y<=`CLAMP_UP(y+3*move_speed,470*4); end
			4'd8    : begin x<=`CLAMP_UP(x+0*move_speed,630*4); y<=`CLAMP_UP(y+4*move_speed,470*4); end
			4'd9    : begin x<=`CLAMP_DOWN(x-1*move_speed,10*4); y<=`CLAMP_UP(y+3*move_speed,470*4); end
			4'd10   : begin x<=`CLAMP_DOWN(x-2*move_speed,10*4); y<=`CLAMP_UP(y+2*move_speed,470*4); end
			4'd11   : begin x<=`CLAMP_DOWN(x-3*move_speed,10*4); y<=`CLAMP_UP(y+1*move_speed,470*4); end
			4'd12   : begin x<=`CLAMP_DOWN(x-4*move_speed,10*4); y<=`CLAMP_UP(y+0*move_speed,470*4); end
			4'd13   : begin x<=`CLAMP_DOWN(x-3*move_speed,10*4); y<=`CLAMP_DOWN(y-1*move_speed, 10*4); end
			4'd14   : begin x<=`CLAMP_DOWN(x-2*move_speed,10*4); y<=`CLAMP_DOWN(y-2*move_speed, 10*4); end
			4'd15   : begin x<=`CLAMP_DOWN(x-1*move_speed,10*4); y<=`CLAMP_DOWN(y-3*move_speed, 10*4); end
			endcase
		else begin
			x <= x;
			y <= y;		
		end
	end
    
endmodule    
