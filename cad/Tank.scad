cube([40,2,10]);

for( i =[
  [35,4,0],
  [35,4,10],
  [5,4,0],
  [5,4,10] ])
{
  translate(i)
  rotate(a=[0,180,0])
  cylinder(h = 1, r=3);
}

color([1,0,0])
stepper(5,0,5);

color([1,0,0])
stepper(35,0,5);

module stepper(x,y,z)
{
  translate([x,y,z])
  cube([4,4,4], center = true);
  
  translate([x,y+2,z])
  rotate([270,0,0])
  pulley( );
}

module pulley(){
  difference(){
    union(){
      cylinder(r=0.6, h=0.3, $fn=32);
      cylinder(r=0.3, h=1, $fn=32);
      
    }
    cylinder(r=0.05, h=1, $fn=32);
  }
}
