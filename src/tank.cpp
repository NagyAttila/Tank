#include <Arduino.h>
//#include <LiquidCrystal.h>
#include "infra.hpp"
#include "stepper.hpp"

// enum Digital
// {
//   INFRA        = 3,
//   EXT1_LCD_RS  = 4,
//   EXT1_LCD_ENB = 5,
//   EXT1_LCD_D4  = 6,
//   EXT1_LCD_D5  = 7,
//   EXT1_LCD_D6  = 8,
//   EXT1_LCD_D7  = 9,
// };

// initialize the library with the numbers of the interface pins
// LiquidCrystal lcd(EXT1_LCD_RS, EXT1_LCD_ENB,
//                   EXT1_LCD_D4, EXT1_LCD_D5, EXT1_LCD_D6, EXT1_LCD_D7);
enum PinSetup
  {
    STEPPER_0 = 6,
    STEPPER_1 = 7,
    STEPPER_2 = 8,
    STEPPER_3 = 9,
  };

Stepper stepper(STEPPER_0, STEPPER_1, STEPPER_2, STEPPER_3);
Infra infra;
unsigned int m_delay = 10;

void setup()
{
  // lcd.begin(16, 2);
  // lcd.print("press key");
  pinMode(3, INPUT);
}

void loop()
{
  int key = infra.getKey();    //Fetch the key
  if (0 == key) { return; }

  for(int i = 4; i < 10; ++i)
    digitalWrite(i, LOW);
  
  switch (key)
    {
    case 1409: // Forward
      digitalWrite(4, HIGH);
      break;
    case 1412: // Backward
      digitalWrite(5, HIGH);
      break;
    case 1411:
      stepper.forward();
      delay(m_delay);
      break;
    case 1413:
      stepper.backward();
      delay(m_delay);
      break;

    case 146:
      if (m_delay > stepper.resolution) m_delay -= stepper.resolution;
      delay(200);
      break;

    case 147:
      m_delay += stepper.resolution;
      delay(200);
      break;

    default:
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
    }

  // lcd.clear();

  // switch (key)
  // {
  //   case 1408: lcd.print("1");            break;
  //   case 1409: lcd.print("2");            break;
  //   case 1410: lcd.print("3");            break;
  //   case 1411: lcd.print("4");            break;
  //   case 1412: lcd.print("5");            break;
  //   case 1413: lcd.print("6");            break;
  //   case 1414: lcd.print("7");            break;
  //   case 1415: lcd.print("8");            break;
  //   case 1416: lcd.print("9");            break;
  //   case 1417: lcd.print("0");            break;
  //   case 1296: lcd.print("<<");           break;
  //   case 1297: lcd.print(">>");           break;
  //   case 1304: lcd.print(">");            break;
  //   case 1295: lcd.print("stop");         break;
  //   case 1294: lcd.print("||");           break;
  //   case 146:  lcd.print("volume +");     break;
  //   case 147:  lcd.print("volume -");     break;
  //   case 1424: lcd.print("prog +");       break;
  //   case 1425: lcd.print("prog -");       break;
  //   case 1430: lcd.print("eject");        break;
  //   case 1429: lcd.print("off");          break;
  //   case 1507: lcd.print("clear");        break;
  //   case 1498: lcd.print("display");      break;
  //   case 1418: lcd.print("-/--");         break;
  //   case 1487: lcd.print("input select"); break;
  //   case 1496: lcd.print("sp/lp");        break;
  //   case 1450: lcd.print("tv/video");     break;
  //   case 1485: lcd.print("menu");         break;
  //   case 1437: lcd.print("rec");          break;
  //   case 1504: lcd.print("timer");        break;
  //   case 1308: lcd.print("smart search"); break;

  //   default:
  //     lcd.print("unknown code");
  //     lcd.setCursor(0, 1);
  //     lcd.print(key);
  // }
}


