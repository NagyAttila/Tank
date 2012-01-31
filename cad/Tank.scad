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
