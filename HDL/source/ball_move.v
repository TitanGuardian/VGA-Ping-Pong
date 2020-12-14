`define CLAMP(value,min,max) ((value<min)?min:(value>max?max:value))
`define CLAMP_DOWN(value,min) ((value<min)?min:value)
`define CLAMP_UP(value,max) (value>max?max:value)
`define NORMALIZE(value,down,up,value_if_out) ((value>=down)&&(value<=up)?value:value_if_out)

module ball_move  (
		 input clk,
		 input rst,
		 input wire [12:0] size,
		 input wire [3:0] direction,
		 input move,
		 output wire [12:0] x_out,
		 output wire [12:0] y_out,
		 output wire [12:0] ms
	);
   parameter move_speed=7;
	
	reg [12:0] x;
	reg [12:0] y;
	assign ms = move_speed;
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
			4'd0    : begin x<=`NORMALIZE(x+0*move_speed,size,13'd2560-size,13'd2560-size); y<=`NORMALIZE(y-4*move_speed,size,13'd1920-size,size); end
			4'd1    : begin x<=`NORMALIZE(x+1*move_speed,size,13'd2560-size,13'd2560-size); y<=`NORMALIZE(y-3*move_speed,size,13'd1920-size,size); end
			4'd2    : begin x<=`NORMALIZE(x+2*move_speed,size,13'd2560-size,13'd2560-size); y<=`NORMALIZE(y-2*move_speed,size,13'd1920-size,size); end
			4'd3    : begin x<=`NORMALIZE(x+3*move_speed,size,13'd2560-size,13'd2560-size); y<=`NORMALIZE(y-1*move_speed,size,13'd1920-size,size); end
			4'd4    : begin x<=`NORMALIZE(x+4*move_speed,size,13'd2560-size,13'd2560-size); y<=`NORMALIZE(y+0*move_speed,size,13'd1920-size,13'd1920-size); end
			4'd5    : begin x<=`NORMALIZE(x+3*move_speed,size,13'd2560-size,13'd2560-size); y<=`NORMALIZE(y+1*move_speed,size,13'd1920-size,13'd1920-size); end
			4'd6    : begin x<=`NORMALIZE(x+2*move_speed,size,13'd2560-size,13'd2560-size); y<=`NORMALIZE(y+2*move_speed,size,13'd1920-size,13'd1920-size); end
			4'd7    : begin x<=`NORMALIZE(x+1*move_speed,size,13'd2560-size,13'd2560-size); y<=`NORMALIZE(y+3*move_speed,size,13'd1920-size,13'd1920-size); end
			4'd8    : begin x<=`NORMALIZE(x+0*move_speed,size,13'd2560-size,13'd2560-size); y<=`NORMALIZE(y+4*move_speed,size,13'd1920-size,13'd1920-size); end
			4'd9    : begin x<=`NORMALIZE(x-1*move_speed,size,13'd2560-size,size); y<=`NORMALIZE(y+3*move_speed,size,13'd1920-size,13'd1920-size); end
			4'd10   : begin x<=`NORMALIZE(x-2*move_speed,size,13'd2560-size,size); y<=`NORMALIZE(y+2*move_speed,size,13'd1920-size,13'd1920-size); end
			4'd11   : begin x<=`NORMALIZE(x-3*move_speed,size,13'd2560-size,size); y<=`NORMALIZE(y+1*move_speed,size,13'd1920-size,13'd1920-size); end
			4'd12   : begin x<=`NORMALIZE(x-4*move_speed,size,13'd2560-size,size); y<=`NORMALIZE(y+0*move_speed,size,13'd1920-size,13'd1920-size); end
			4'd13   : begin x<=`NORMALIZE(x-3*move_speed,size,13'd2560-size,size); y<=`NORMALIZE(y-1*move_speed,size,13'd1920-size,size); end
			4'd14   : begin x<=`NORMALIZE(x-2*move_speed,size,13'd2560-size,size); y<=`NORMALIZE(y-2*move_speed,size,13'd1920-size,size); end
			4'd15   : begin x<=`NORMALIZE(x-1*move_speed,size,13'd2560-size,size); y<=`NORMALIZE(y-3*move_speed,size,13'd1920-size,size); end
			endcase
		else begin
			x <= x;
			y <= y;		
		end
	end
    
endmodule    
