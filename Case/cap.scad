use <rounded_box.scad>

$fn=50;

w=60;
d=32;
h=1.6;
r=4;

o=.3;
t=0.45*3;
th=9;
i=2.54;

difference() {
	
	union () {
		
		rd = 2.5;

		difference()
		{		
			rounded_box(
				o+o+w+t+t,
				o+o+d+t+t,
				th+t,
				r+o+t
			);
			
			// first stage pcb rim
			translate([0,0,-1])
			rounded_box(
				w+o+o,
				d+o+o,
				th+1,
				r+o
			);
			
			
			// display 10.5 
		}
		
		
		translate([-6 + 20, -6 + .5, th-3])
		cube([12, 12, 3]);
		
	}
	
	// knob
	translate([20, 0 + 1, 0])
	cylinder(30, 3.6, 3.6);
	
	// display
	translate([-31/2 - 7.7, -16/2 + 2, 0])
	cube([31, 16, 20]);


	// plug openings
	translate([0,-7,3]) {
		
	rotate([0,270,0])
	cylinder(40,3,3);
	
	translate([-40, -3, -6])
	cube([40, 6, 6]);
	}

	// plug openings
	translate([0,7,3]) {
		
	rotate([0,270,0])
	cylinder(40,3,3);
	
	translate([-40, -3, -6])
	cube([40, 6, 6]);
	}
	
}

if($preview && 0) {
	color("black", 0.9) rounded_box(w,d,h,r);
}

module usbSocket() {
	usb = 9;
	color("red", 0.2)
	translate([-usb/2,d/2-usb/2,-usb+th-h])
	cube(usb);
	
	usb2 = 32;
	color("red", 0.2)
	translate([-usb2/2,d/2-usb2+o,-usb2+th-h])
	cube(usb2);
	
}