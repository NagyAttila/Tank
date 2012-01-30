#include <Arduino.h>
#include <LiquidCrystal.h>

int ir_pin = 3;       //Sensor pin 1 wired through a 220 ohm resistor
int bin_1 = 1000;     //Binary 1 threshold (Microseconds)
int bin_0 = 400;      //Binary 0 threshold (Microseconds)

enum Digital
{
  EXT1_LCD_RS  = 4,
  EXT1_LCD_ENB = 5,
  EXT1_LCD_D4  = 6,
  EXT1_LCD_D5  = 7,
  EXT1_LCD_D6  = 8,
  EXT1_LCD_D7  = 9,
};

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(EXT1_LCD_RS, EXT1_LCD_ENB, 
                  EXT1_LCD_D4, EXT1_LCD_D5, EXT1_LCD_D6, EXT1_LCD_D7);


int getIRKey() {
  int data[12];
  while(pulseIn(ir_pin, LOW) < 2200) { //Wait for a start bit
  }
  data[0] = pulseIn(ir_pin, LOW);//Start measuring bits, I only want low pulses
  data[1] = pulseIn(ir_pin, LOW);
  data[2] = pulseIn(ir_pin, LOW);
  data[3] = pulseIn(ir_pin, LOW);
  data[4] = pulseIn(ir_pin, LOW);
  data[5] = pulseIn(ir_pin, LOW);
  data[6] = pulseIn(ir_pin, LOW);
  data[7] = pulseIn(ir_pin, LOW);
  data[8] = pulseIn(ir_pin, LOW);
  data[9] = pulseIn(ir_pin, LOW);
  data[10] = pulseIn(ir_pin, LOW);
  data[11] = pulseIn(ir_pin, LOW);

  for(int i=0;i<11;i++) {  //Parse them
    if(data[i] > bin_1) {  //is it a 1?
      data[i] = 1;
    }  else {
      if(data[i] > bin_0) {//is it a 0?
        data[i] = 0;
      } else {
        data[i] = 2;  //Flag the data as invalid; I don't know what it is!
      }
    }
  }

  for(int i=0;i<11;i++) {  //Pre-check data for errors
    if(data[i] > 1) {
      return -1;     //Return -1 on invalid data
    }
  }

  int result = 0;
  int seed = 1;
  for(int i=0;i<11;i++) {  //Convert bits to integer
    if(data[i] == 1) {
      result += seed;
    }
    seed = seed * 2;
  }
  return result;     //Return key number
}
 

void setup()
{
  pinMode(ir_pin, INPUT);

  lcd.begin(16, 2);
  lcd.print("press key");
}

void loop()
{
  int key = getIRKey();    //Fetch the key
  lcd.clear();

  switch (key)
  {
    case 1408: lcd.print("1");            break;
    case 1409: lcd.print("2");            break;
    case 1410: lcd.print("3");            break;
    case 1411: lcd.print("4");            break;
    case 1412: lcd.print("5");            break;
    case 1413: lcd.print("6");            break;
    case 1414: lcd.print("7");            break;
    case 1415: lcd.print("8");            break;
    case 1416: lcd.print("9");            break;
    case 1417: lcd.print("0");            break;
    case 1296: lcd.print("<<");           break;
    case 1297: lcd.print(">>");           break;
    case 1304: lcd.print(">");            break;
    case 1295: lcd.print("stop");         break;
    case 1294: lcd.print("||");           break;
    case 146:  lcd.print("volume +");     break;
    case 147:  lcd.print("volume -");     break;
    case 1424: lcd.print("prog +");       break;
    case 1425: lcd.print("prog -");       break;
    case 1430: lcd.print("eject");        break;
    case 1429: lcd.print("off");          break;
    case 1507: lcd.print("clear");        break;
    case 1498: lcd.print("display");      break;
    case 1418: lcd.print("-/--");         break;
    case 1487: lcd.print("input select"); break;
    case 1496: lcd.print("sp/lp");        break;
    case 1450: lcd.print("tv/video");     break;
    case 1485: lcd.print("menu");         break;
    case 1437: lcd.print("rec");          break;
    case 1504: lcd.print("timer");        break;
    case 1308: lcd.print("smart search"); break;

    default:
      lcd.print("unknown code");
      lcd.setCursor(0, 1);
      lcd.print(key);
  }
}



