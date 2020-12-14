`define CLAMP(value,min,max) ((value<min)?min:(value>max?max:value))
`define CLAMP_DOWN(value,min) ((value<min)?min:value)
`define CLAMP_UP(value,max) (value>max?max:value)

module paddle_move  (
		 input clk,
		 input rst,
		 input move_up,
		 input move_down,
		 input wire [12:0] size,
		 input wire [12:0] init_x,
		 input wire [12:0] init_y,
		 output wire [12:0] x_out,
		 output wire [12:0] y_out
	);
   wire [12:0] move_speed= 13'd12;
	
	reg [12:0] x;
	reg [12:0] y;
	
	assign x_out = x;
	assign y_out = y;
	
	always @(posedge clk) begin
		if (rst) begin
			x <= init_x;
			y <= init_y;
		end
		else
		if (move_up)
			y <= `CLAMP_DOWN(y-move_speed,size);
		else if (move_down)
			y <= `CLAMP_UP(y+move_speed,13'd1920-size);
		else begin
			y <= y;		
		end
	end
    
endmodule    
