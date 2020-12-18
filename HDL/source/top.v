
module top(
	input			clk_50,					// 50 MHz / 20 ns
	input       wire [3:0] sw,
   input       wire [3:0] key,
	
   output		wire [7:0] leds, 
	output		red, green, blue,		// VGA color outputs
	output		hsync, vsync			// VGA sync outputs
);

	wire	[9:0]	hpos, vpos;				// Current pixel position
	wire 			active;					// Active screen area flag
	wire			pixel_tick;				// Pulse coming from the VGA generator when the pixel position is stable (25 MHz)
	wire			frame_tick;				// Pulse coming from the VGA generator when entering into the blanking area (60 Hz)
	
	reg	[2:0]	pixel;					// Current pixel RGB color
	reg	[6:0]	count;					// Counter for pattern
	wire	[3:0]	pattern;					// Current pattern (0 - 15)

	// Reset pulse
	
	reg		counter_reset = 1'b0;
	reg		reset = 1'b0;
	
	vga vga_gen(
		.clk(clk_50),
		.reset(reset),
		.pixel_rgb(pixel),
		
		.hsync(hsync),
		.vsync(vsync),
		.red(red),
		.green(green),
		.blue(blue),
		.active(active),
		.ptick(pixel_tick),
		.xpos(hpos),
		.ypos(vpos),

		.ftick(frame_tick)
	);

	// Generate a reset pulse

	 always @ (posedge clk_50) begin
        if (~counter_reset) begin
            counter_reset <= 1'b1;
				reset <= 1'b1;
        end
        else
            reset <= 0;
    end
	 //gameout
	 wire goal_p1, goal_p2;
	 wire [4:0]reset_cd;
	 
	 

	 //nn
	 wire clk_nn;
	 reg [4:0] cnt_nn;
	 
	 assign clk_nn = frame_tick;//cnt_nn[4];
	 assign leds[7] = ~clk_nn;
	 always @ (posedge frame_tick) begin
	     cnt_nn = cnt_nn + 1;
	 end
	 
	 wire nn_p1_up;
	 wire nn_p1_down;
	 wire nn_p1_stay;
	 assign leds[4] = ~nn_p1_up;
	 assign leds[3] = ~nn_p1_stay;
	 assign leds[2] = ~nn_p1_down;
    // game_input
    wire game_rst = sw[3] || (goal_p1|goal_p2)&&(reset_cd<=1);
	 wire player1_move_up = nn_p1_up; //(!sw[1]&~key[3])||(sw[1]&&nn_p1_up);
	 wire player1_move_down = nn_p1_down;//(!sw[1]&~key[2])||(sw[1]&&nn_p1_down);
	 wire player2_move_up = ~key[1];
	 wire player2_move_down = ~key[0];


	 // ball
    wire signed [12:0] movespeed;
    wire signed [12:0] ball_x_extended;
    wire signed [12:0] ball_y_extended;
    wire signed [10:0] ball_x;
    wire signed [10:0] ball_y;
    wire signed [10:0] ball_start_h;
    wire signed [10:0] ball_end_h;
    wire signed [10:0] ball_start_w;
    wire signed [10:0] ball_end_w;
    	 
    wire [3:0] direction;
    assign ball_x = ball_x_extended[12:2];
    assign ball_y = ball_y_extended[12:2];
    
    localparam ball_size=5;
    
    rectangle #(.size_y(ball_size),.size_x(ball_size)) ball(
            .x(ball_x), 
            .y(ball_y), 
            .start_h(ball_start_h),
            .start_w(ball_start_w),
            .end_h(ball_end_h),
            .end_w(ball_end_w)
    );


	 
    ball_move ball_movement_block(
        .clk(frame_tick),
		  .rst(game_rst),
		  .size(ball_size*4),
        .direction(direction),
		  .move(1),
		  .x_out(ball_x_extended),
		  .y_out(ball_y_extended),
		  .ms(movespeed)
    );
	
	//paddle left

 
    wire signed [12:0] p1_x_extended;
    wire signed [12:0] p1_y_extended;
	 wire signed [12:0] p1_x_extended_init;
    wire signed [12:0] p1_y_extended_init;
    wire signed [10:0] p1_x;
    wire signed [10:0] p1_y;
    wire signed [10:0] p1_start_h;
    wire signed [10:0] p1_end_h;
    wire signed [10:0] p1_start_w;
    wire signed [10:0] p1_end_w;
    	 
    assign p1_x_extended_init = 13'd120;
	 assign p1_y_extended_init = 13'd960;
		 
    assign p1_x = p1_x_extended[12:2];
    assign p1_y = p1_y_extended[12:2];
    
    localparam paddle_width=4;
    localparam paddle_height=70;
	 
    rectangle #(.size_y(paddle_height),.size_x(paddle_width)) p1(
            .x(p1_x), 
            .y(p1_y), 
            .start_h(p1_start_h),
            .start_w(p1_start_w),
            .end_h(p1_end_h),
            .end_w(p1_end_w)
    );
	 
	 paddle_move p1_movement(
		  .clk(frame_tick),
		  .rst(game_rst),
		  .move_up(player1_move_up),
		  .move_down(player1_move_down),
		  .size(paddle_height*4),
		  .init_x(p1_x_extended_init),
		  .init_y(p1_y_extended_init),
		  .x_out(p1_x_extended),
		  .y_out(p1_y_extended)
	 );
	 
	 //paddle right

 
    wire signed [12:0] p2_x_extended;
    wire signed [12:0] p2_y_extended;
	 wire signed [12:0] p2_x_extended_init;
    wire signed [12:0] p2_y_extended_init;
    wire signed [10:0] p2_x;
    wire signed [10:0] p2_y;
    wire signed [10:0] p2_start_h;
    wire signed [10:0] p2_end_h;
    wire signed [10:0] p2_start_w;
    wire signed [10:0] p2_end_w;
    	 
    assign p2_x_extended_init = 13'd2436;
	 assign p2_y_extended_init = 13'd960;
		 
    assign p2_x = p2_x_extended[12:2];
    assign p2_y = p2_y_extended[12:2];
   
	 
    rectangle #(.size_y(paddle_height),.size_x(paddle_width)) p2(
            .x(p2_x), 
            .y(p2_y), 
            .start_h(p2_start_h),
            .start_w(p2_start_w),
            .end_h(p2_end_h),
            .end_w(p2_end_w)
    );
	 
	 paddle_move p2_movement(
		  .clk(frame_tick),
		  .rst(game_rst),
		  .move_up(player2_move_up),
		  .move_down(player2_move_down),
		  .size(paddle_height*4),
		  .init_x(p2_x_extended_init),
		  .init_y(p2_y_extended_init),
		  .x_out(p2_x_extended),
		  .y_out(p2_y_extended)
	 );
	 
	 
	 ball_direction ball_direction_block(
	     .clk(frame_tick),
		  .rst(game_rst),
		  .size(ball_size*4),
		  .x(ball_x_extended),
		  .y(ball_y_extended),
		  .paddle_size(paddle_height*4),
		  .paddle_width(paddle_width*4),
		  .y_p1(p1_y_extended),
		  .y_p2(p2_y_extended),
		  .x_p1(p1_x_extended),
		  .x_p2(p2_x_extended),
		  .move_speed(),
		  .direction_out(direction),
		  .goal_p1(goal_p1),
		  .goal_p2(goal_p2),
		  .cool(reset_cd),
		  .move_speed(movespeed)
	 );
	 
	 neural_p1 nn_p1(
		  .clk(clk_nn),
		  .clk_mul(pixel_tick),
		  .direction(direction),
		  .ball_x(ball_x_extended),
		  .ball_y(ball_y_extended),
		  .p1_y(p1_y_extended),
		  .p2_y(p2_y_extended),
		  .up(nn_p1_up),
		  .down(nn_p1_down),
		  .stay(nn_p1_stay),
		  .test(leds[0])
	 );
	 

	always @(posedge pixel_tick) begin
		if (! active)
			pixel <= 3'b0;
		else begin
				// render ball
            if ((hpos >= ball_start_w) & (hpos <= ball_end_w) & (vpos >= ball_start_h) & (vpos <= ball_end_h)) begin
                pixel <= 3'b111;
            end	
            else // render p1
            if ((hpos >= p1_start_w) & (hpos <= p1_end_w) & (vpos >= p1_start_h) & (vpos <= p1_end_h)) begin
                pixel <= 3'b111;
            end
				else // render p2
            if ((hpos >= p2_start_w) & (hpos <= p2_end_w) & (vpos >= p2_start_h) & (vpos <= p2_end_h)) begin
                pixel <= 3'b111;
            end	
            else begin
                pixel <= 3'b0;
            end
		end
	end

endmodule
