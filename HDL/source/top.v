
module vga_demo(
	input			clk_50,					// 50 MHz / 20 ns
	input       wire [3:0] sw,
   input       wire [3:0] key,
    
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

	// ball
    
    wire signed [12:0] ball_x_extended;
    wire signed [12:0] ball_y_extended;
    wire signed [10:0] ball_x;
    wire signed [10:0] ball_y;
    wire signed [10:0] ball_start_h;
    wire signed [10:0] ball_end_h;
    wire signed [10:0] ball_start_w;
    wire signed [10:0] ball_end_w;
    	 
    wire [3:0] direction;
    assign direction = ~sw;
    assign ball_x = ball_x_extended[12:2];
    assign ball_y = ball_y_extended[12:2];
    
    localparam ball_size=20;
    
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
		  .rst(~key[3]),
        .direction(direction),
		  .move(~key[2]),
		  .x_out(ball_x_extended),
		  .y_out(ball_y_extended)
    );

	always @(posedge pixel_tick) begin
		if (! active)
			pixel <= 3'b0;
		else begin
            // render rectangle
            if ((hpos >= ball_start_w) & (hpos <= ball_end_w) & (vpos >= ball_start_h) & (vpos <= ball_end_h)) begin
                pixel <= 3'b111;
            end	
            else begin
                pixel <= 3'b0;
            end
		end
	end

endmodule
