


// screws
house_diameter = 100;
screw_distance = 55;
n_slots = 3;
subdivision = 50;


difference () {
    
    union() {
           
        difference() { 
            cylinder(d1=house_diameter, d2=house_diameter, h=15, $fn=subdivision);
            translate([0,0,-1]) cylinder(d1=house_diameter-6, d2=house_diameter-6, h=17, $fn=subdivision);
        }
        
        difference() { 
            cylinder(r1=house_diameter/2, r2=house_diameter/2, h=2, $fn=subdivision);
            translate([0,0,-1]) cylinder(d1=screw_distance-6, d2=screw_distance-10, h=4, $fn=subdivision);
            
            translate([screw_distance/2,0,-1]) cylinder(r1=2.5, r2=2.5, h=4, $fn=subdivision);
            translate([-screw_distance/2,0,-1]) cylinder(r1=2.5, r2=2.5, h=4, $fn=subdivision);   
        }
        
       translate([0,0,2]) difference() {
            cylinder(d1=house_diameter-5, d2=house_diameter-5, h=3, $fn=subdivision);
            translate([0,0,-1]) cylinder(d1=house_diameter-20, d2=house_diameter, h=5, $fn=subdivision);
       }
    }
    
   
    for (a =[0:n_slots]) {        
        rotate([0,0,a*(360/n_slots)]) translate([(house_diameter/2)-1.5,0,-1]) cube([2,2,17]);
        *rotate([0,0,a*(360/n_slots)]) translate([(house_diameter/2)-1.5,0,0]) cube([2,10,2]);
    }
    
    translate([0,0,-1]) difference() {
        cylinder(d1=house_diameter+1, d2=house_diameter+1, h=2, $fn=subdivision);
        translate([0,0,-1]) cylinder(d1=house_diameter-3, d2=house_diameter-3, h=4, $fn=subdivision);
    }
}