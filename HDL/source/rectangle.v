`define CLAMP(value,min,max) ((value<min)?min:(value>max?max:value))
`define CLAMP_DOWN(value,min) ((value<min)?min:value)
`define CLAMP_UP(value,max) (value>max?max:value)

module 
    rectangle  
    (
        input [10:0] y,
        input [10:0] x,
        
        output [10:0] start_h,
        output [10:0] end_h,
        output [10:0] start_w,    
        output [10:0] end_w    
    );
	 parameter size_x=3,size_y=3, WIDTH=639, HEIGHT=479;
    
    assign start_h = y<size_y?0:y-size_y;
    assign end_h = `CLAMP_UP(y + size_y,HEIGHT);
    assign start_w = x<size_x?0:x-size_x;
    assign end_w = `CLAMP_UP(x + size_x,WIDTH);
    
endmodule