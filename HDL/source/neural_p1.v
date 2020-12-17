
module 
    neural_p1  
    (
		  input wire clk,
		  input wire clk_mul,
        input wire [3:0] direction,
        input wire [12:0] ball_x,
        input wire [12:0] ball_y,
        input wire [12:0] p1_y,
        input wire [12:0] p2_y,
        output reg up,
        output reg down,
		  output reg stay,
		  output test
    );
	 reg enable_mul;
	 reg signed [31:0] mem[0:74];
	 initial begin
	    $readmemh("init_var/nn1_hdl.txt",mem);
	 end
	 
	 wire signed [31:0] RND,Max;
	 
	 assign RND = (64);
	 
	 reg [15:0] counter;
	 
	 
    // input layer
    wire signed [31:0] i[0:4];
    assign i[0] = {1'b0,direction}*256/16-128; 
    assign i[1] = {1'b0,ball_x}*256/2560-128; 
    assign i[2] = {1'b0,ball_y}*256/1920-128; 
    assign i[3] = {1'b0,p1_y}*256/1920-128; 
    assign i[4] = {1'b0,p2_y}*256/1920-128; 
    
    //first hidden layer
    reg signed [31:0] n[0:7];
    
    //weights and bias
    reg signed [31:0] w[0:7],bias;
    
    //second last layer
    reg signed [31:0] l[0:2];
    
    initial counter=0;
    
	 always @(posedge clk) begin
		 if (counter==9) begin
				counter<=0;
				if (l[0]>=l[2]) begin
					up <= 1;
					stay <= 0;
					down <= 0;
				end
				else begin
					up <= 0;
					stay <= 0;
					down <= 1;
				end
		 end
		 else begin
				if (counter>=9) counter <= 0;
				else counter <= counter + 1;
		 end

	 end
	 
	 

	 
	always @(negedge clk) begin
		if (counter<8) begin
			n[counter] = (mem[counter*6+0]*i[0]+mem[counter*6+1]*i[1]+mem[counter*6+2]*i[2]
					+mem[counter*6+3]*i[3]+mem[counter*6+4]*i[4]+(mem[counter*6+5]<<<7))>>>7;
			if (n[counter]<0) n[counter]=0;
			else if (n[counter]>127) n[counter]=127;
		end
		else if (counter==8) begin
			l[0] = (mem[8*6+0]*n[0]
								+mem[8*6+1]*n[1]
								+mem[8*6+2]*n[2]
								+mem[8*6+3]*n[3]
								+mem[8*6+4]*n[4]
								+mem[8*6+5]*n[5]
								+mem[8*6+6]*n[6]
								+mem[8*6+7]*n[7]
								+(mem[8*6+8]<<<7))>>>7;
			if (l[0]<0) l[0]=0;
			else if (l[0]>127) l[0]=127;
			
			l[2] =         (mem[8*6+(2)*9+0]*n[0]
								+mem[8*6+(2)*9+1]*n[1]
								+mem[8*6+(2)*9+2]*n[2]
								+mem[8*6+(2)*9+3]*n[3]
								+mem[8*6+(2)*9+4]*n[4]
								+mem[8*6+(2)*9+5]*n[5]
								+mem[8*6+(2)*9+6]*n[6]
								+mem[8*6+(2)*9+7]*n[7]
								+(mem[8*6+(2)*9+8]<<<7))>>>7;
			if (l[2]<0) l[2]=0;
			else if (l[2]>127) l[2]=127;
		end
	end
	 
	assign test = (l[2]<l[0]);
	 
	 
endmodule
