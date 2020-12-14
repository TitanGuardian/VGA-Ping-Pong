`define CLAMP(value,min,max) ((value<min)?min:(value>max?max:value))
`define CLAMP_DOWN(value,min) ((value<min)?min:value)
`define CLAMP_UP(value,max) (value>max?max:value)

module ball_direction  (
		 input clk,
		 input rst,
		 input wire [12:0] size,
		 input wire [12:0] x,
		 input wire [12:0] y,
		 input wire [12:0] paddle_size,
		 input wire [12:0] paddle_width,
		 input wire [12:0] y_p1,
		 input wire [12:0] y_p2,
		 input wire [12:0] x_p1,
		 input wire [12:0] x_p2,
		 input wire [12:0] move_speed,
		 output wire [3:0] direction_out,
		 output reg goal_p1,
		 output reg goal_p2,
		 output wire [4:0] cool
	);
	
	reg [4:0] cnt;
	reg [4:0] cooldown;
	reg [4:0] cooldown_paddle;
	reg [3:0] direction;
	reg [3:0] r_direction;
	reg [3:0] p1_ref_direction;
	reg [3:0] p2_ref_direction;
	reg [2:0] p1_cluster_num;
	reg [2:0] p2_cluster_num;
	
	wire [12:0] diff_p1;
	wire [12:0] diff_p2;
	wire [12:0] paddle_step;
	wire [12:0] paddle_half;
	
	assign diff_p1 = y+paddle_size-y_p1;
	assign diff_p2 = y+paddle_size-y_p2;
	assign cool = cooldown_paddle;
	assign paddle_step = (2*paddle_size)/7;
	assign paddle_half = paddle_size;
	
	assign direction_out = direction;
	
	always @(posedge clk) begin
		if (cnt==29) cnt<=0;
		else cnt <= cnt+4'd1;
		if (rst) begin
			goal_p1 <= 0;
			goal_p2 <= 0;
			direction <= (cnt==0||cnt==16)?4:(cnt==8||cnt==24?12:cnt);
			cooldown <= 4'd0;
			cooldown_paddle <= 4'd0;
		end
		else if ((y==(size)||y==(13'd1920-size))&&cooldown==4'd0) begin
			direction<=r_direction;
			cooldown <= 4'd15;
			if (cooldown_paddle!=0) cooldown_paddle <= cooldown_paddle - 1;
			if (cooldown_paddle==0) begin goal_p1<=0; goal_p2<=0; end
			end
		else if (x<=x_p1+paddle_width+2*size+move_speed&&cooldown_paddle==4'd0) begin
			if (direction==p1_ref_direction) goal_p1 <= 1;
			if (cooldown!=0) cooldown <= cooldown - 1;
			direction<=p1_ref_direction;
			cooldown_paddle <= 4'd15;
		end
		else if (x>=x_p2-paddle_width-size-move_speed&&cooldown_paddle==4'd0) begin
			if (direction==p2_ref_direction) goal_p2 <= 1;
			if (cooldown!=0) cooldown <= cooldown - 1;
			direction<=p2_ref_direction;
			cooldown_paddle <= 4'd15;
		end
		else begin
			direction<=direction;
			if (cooldown_paddle==0) begin goal_p1<=0; goal_p2<=0; end
 			if (cooldown!=0) cooldown <= cooldown - 1;
			if (cooldown_paddle!=0) cooldown_paddle <= cooldown_paddle - 1;
		end
	end
	

	always @* begin
		case(direction)
		4'd0    : begin r_direction = 4'd8; end
		4'd1    : begin r_direction = 4'd7; end
		4'd2    : begin r_direction = 4'd6; end
		4'd3    : begin r_direction = 4'd5; end
		4'd4    : begin r_direction = 4'd4; end
		4'd5    : begin r_direction = 4'd3; end
		4'd6    : begin r_direction = 4'd2; end
		4'd7    : begin r_direction = 4'd1; end
		4'd8    : begin r_direction = 4'd0; end
		4'd9    : begin r_direction = 4'd15; end
		4'd10   : begin r_direction = 4'd14; end
		4'd11   : begin r_direction = 4'd13; end
		4'd12   : begin r_direction = 4'd12; end
		4'd13   : begin r_direction = 4'd11; end
		4'd14   : begin r_direction = 4'd10; end
		4'd15   : begin r_direction = 4'd9; end
		endcase	
	end
   
	always @* begin
		p1_cluster_num = 3'd7;
		if (y >= y_p1-paddle_size) begin
			if (diff_p1 < paddle_step) 
				p1_cluster_num = 0;
			else if (diff_p1 < 2*paddle_step) 
				p1_cluster_num = 1;
			else if (diff_p1 < 3 * paddle_step) 
				p1_cluster_num = 2;
			else if (diff_p1 < 4 * paddle_step+4) 
				p1_cluster_num = 3;
			else if (diff_p1 < 5 * paddle_step + 4) 
				p1_cluster_num = 4;
			else if (diff_p1 < 6 * paddle_step + 4) 
				p1_cluster_num = 5;
			else if (diff_p1 < 7 * paddle_step + 4) 
				p1_cluster_num = 6;
		end
	end

	always @* begin
		p2_cluster_num = 3'd7;
		if (y >= y_p2-paddle_size) begin
			if (diff_p2 < paddle_step)
				p2_cluster_num = 0;
			else if (diff_p2 < 2*paddle_step)
				p2_cluster_num = 1;
			else if (diff_p2 < 3 * paddle_step)
				p2_cluster_num = 2;
			else if (diff_p2 < 4 * paddle_step+4)
				p2_cluster_num = 3;
			else if (diff_p2 < 5 * paddle_step + 4)
				p2_cluster_num = 4;
			else if (diff_p2 < 6 * paddle_step + 4)
				p2_cluster_num = 5;
			else if (diff_p2 < 7 * paddle_step + 4) 
				p2_cluster_num = 6;
		end
	end
	
	
	always @* begin
		p1_ref_direction = direction;
		case(p1_cluster_num)
		3'd0:
			case(direction)
			4'd9    : begin p1_ref_direction = 4'd4; end
			4'd10   : begin p1_ref_direction = 4'd3; end
			4'd11   : begin p1_ref_direction = 4'd2; end
			4'd12   : begin p1_ref_direction = 4'd1; end
			4'd13   : begin p1_ref_direction = 4'd1; end
			4'd14   : begin p1_ref_direction = 4'd1; end
			4'd15   : begin p1_ref_direction = 4'd1; end
			endcase	
		3'd1:
			case(direction)
			4'd9    : begin p1_ref_direction = 4'd5; end
			4'd10   : begin p1_ref_direction = 4'd4; end
			4'd11   : begin p1_ref_direction = 4'd3; end
			4'd12   : begin p1_ref_direction = 4'd2; end
			4'd13   : begin p1_ref_direction = 4'd1; end
			4'd14   : begin p1_ref_direction = 4'd1; end
			4'd15   : begin p1_ref_direction = 4'd1; end
			endcase	
		3'd2:
			case(direction)
			4'd9    : begin p1_ref_direction = 4'd6; end
			4'd10   : begin p1_ref_direction = 4'd5; end
			4'd11   : begin p1_ref_direction = 4'd4; end
			4'd12   : begin p1_ref_direction = 4'd3; end
			4'd13   : begin p1_ref_direction = 4'd2; end
			4'd14   : begin p1_ref_direction = 4'd1; end
			4'd15   : begin p1_ref_direction = 4'd1; end
			endcase	
		3'd3:
			case(direction)
			4'd9    : begin p1_ref_direction = 4'd7; end
			4'd10   : begin p1_ref_direction = 4'd6; end
			4'd11   : begin p1_ref_direction = 4'd5; end
			4'd12   : begin p1_ref_direction = 4'd4; end
			4'd13   : begin p1_ref_direction = 4'd3; end
			4'd14   : begin p1_ref_direction = 4'd2; end
			4'd15   : begin p1_ref_direction = 4'd1; end
			endcase	
		3'd4:
			case(direction)
			4'd9    : begin p1_ref_direction = 4'd7; end
			4'd10   : begin p1_ref_direction = 4'd7; end
			4'd11   : begin p1_ref_direction = 4'd6; end
			4'd12   : begin p1_ref_direction = 4'd5; end
			4'd13   : begin p1_ref_direction = 4'd4; end
			4'd14   : begin p1_ref_direction = 4'd3; end
			4'd15   : begin p1_ref_direction = 4'd2; end
			endcase	
		3'd5:
			case(direction)
			4'd9    : begin p1_ref_direction = 4'd7; end
			4'd10   : begin p1_ref_direction = 4'd7; end
			4'd11   : begin p1_ref_direction = 4'd7; end
			4'd12   : begin p1_ref_direction = 4'd6; end
			4'd13   : begin p1_ref_direction = 4'd5; end
			4'd14   : begin p1_ref_direction = 4'd4; end
			4'd15   : begin p1_ref_direction = 4'd3; end
			endcase	
		3'd6:
			case(direction)
			4'd9    : begin p1_ref_direction = 4'd7; end
			4'd10   : begin p1_ref_direction = 4'd7; end
			4'd11   : begin p1_ref_direction = 4'd7; end
			4'd12   : begin p1_ref_direction = 4'd7; end
			4'd13   : begin p1_ref_direction = 4'd6; end
			4'd14   : begin p1_ref_direction = 4'd5; end
			4'd15   : begin p1_ref_direction = 4'd4; end
			endcase	
		endcase
	end
	
	always @* begin
		p2_ref_direction = direction;
		case(p2_cluster_num)
		3'd0:
			case(direction)
			4'd1   : begin p2_ref_direction = 4'd15; end
			4'd2   : begin p2_ref_direction = 4'd15; end
			4'd3   : begin p2_ref_direction = 4'd15; end
			4'd4   : begin p2_ref_direction = 4'd15; end
			4'd5   : begin p2_ref_direction = 4'd14; end
			4'd6   : begin p2_ref_direction = 4'd13; end
			4'd7   : begin p2_ref_direction = 4'd12; end
			endcase	
		3'd1:
			case(direction)
			4'd1   : begin p2_ref_direction = 4'd15; end
			4'd2   : begin p2_ref_direction = 4'd15; end
			4'd3   : begin p2_ref_direction = 4'd15; end
			4'd4   : begin p2_ref_direction = 4'd14; end
			4'd5   : begin p2_ref_direction = 4'd13; end
			4'd6   : begin p2_ref_direction = 4'd12; end
			4'd7   : begin p2_ref_direction = 4'd11; end
			endcase	
		3'd2:
			case(direction)
			4'd1   : begin p2_ref_direction = 4'd15; end
			4'd2   : begin p2_ref_direction = 4'd15; end
			4'd3   : begin p2_ref_direction = 4'd14; end
			4'd4   : begin p2_ref_direction = 4'd13; end
			4'd5   : begin p2_ref_direction = 4'd12; end
			4'd6   : begin p2_ref_direction = 4'd11; end
			4'd7   : begin p2_ref_direction = 4'd10; end
			endcase	
		3'd3:
			case(direction)
			4'd1   : begin p2_ref_direction = 4'd15; end
			4'd2   : begin p2_ref_direction = 4'd14; end
			4'd3   : begin p2_ref_direction = 4'd13; end
			4'd4   : begin p2_ref_direction = 4'd12; end
			4'd5   : begin p2_ref_direction = 4'd11; end
			4'd6   : begin p2_ref_direction = 4'd10; end
			4'd7   : begin p2_ref_direction = 4'd9 ; end
			endcase	
		3'd4:
			case(direction)
			4'd1   : begin p2_ref_direction = 4'd14; end
			4'd2   : begin p2_ref_direction = 4'd13; end
			4'd3   : begin p2_ref_direction = 4'd12; end
			4'd4   : begin p2_ref_direction = 4'd11; end
			4'd5   : begin p2_ref_direction = 4'd10; end
			4'd6   : begin p2_ref_direction = 4'd9; end
			4'd7   : begin p2_ref_direction = 4'd9; end
			endcase	
		3'd5:
			case(direction)
			4'd1   : begin p2_ref_direction = 4'd13; end
			4'd2   : begin p2_ref_direction = 4'd12; end
			4'd3   : begin p2_ref_direction = 4'd11; end
			4'd4   : begin p2_ref_direction = 4'd10; end
			4'd5   : begin p2_ref_direction = 4'd9; end
			4'd6   : begin p2_ref_direction = 4'd9; end
			4'd7   : begin p2_ref_direction = 4'd9; end
			endcase
		3'd6:
			case(direction)
			4'd1   : begin p2_ref_direction = 4'd12; end
			4'd2   : begin p2_ref_direction = 4'd11; end
			4'd3   : begin p2_ref_direction = 4'd10; end
			4'd4   : begin p2_ref_direction = 4'd9; end
			4'd5   : begin p2_ref_direction = 4'd9; end
			4'd6   : begin p2_ref_direction = 4'd9; end
			4'd7   : begin p2_ref_direction = 4'd9; end
			endcase
		endcase
	end
	
	
endmodule    
