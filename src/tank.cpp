#include <Arduino.h>
#include "infra.hpp"
#include "stepper.hpp"

enum PinSetup
{
  STEPPER_0 = 6,
  STEPPER_1 = 7,
  STEPPER_2 = 8,
  STEPPER_3 = 9,
};

Stepper stepper(STEPPER_0, STEPPER_1, STEPPER_2, STEPPER_3);
Infra infra;
unsigned int g_delay = 10;
bool g_forward = true;

void infraHandler(int key)
{
  // some overload control
  // accept only one key press in every 200ms (5 key/s)
  static unsigned long last = micros();
  unsigned long now = micros();
  if (now - last < 200000) { return; }
  last = now;

  switch (key)
  {
    case  146: Serial.println("volume +");     break;
    case  147: Serial.println("volume -");     break;
    case 1408: Serial.println("1");            break;
    case 1409: Serial.println("2");            break;
    case 1410: Serial.println("3");            break;
    case 1411: Serial.println("4");            break;
    case 1412: Serial.println("5");            break;
    case 1413: Serial.println("6");            break;
    case 1414: Serial.println("7");            break;
    case 1415: Serial.println("8");            break;
    case 1416: Serial.println("9");            break;
    case 1417: Serial.println("0");            break;
    case 1418: Serial.println("-/--");         break;
    case 1424: Serial.println("prog +");       break;
    case 1425: Serial.println("prog -");       break;
    case 1429: Serial.println("off");          break;
    case 1430: Serial.println("eject");        break;
    case 1437: Serial.println("rec");          break;
    case 1450: Serial.println("tv/video");     break;
    case 1485: Serial.println("menu");         break;
    case 1487: Serial.println("input select"); break;
    case 1496: Serial.println("sp/lp");        break;
    case 1498: Serial.println("display");      break;
    case 1504: Serial.println("timer");        break;
    case 1507: Serial.println("clear");        break;
    case 3342: Serial.println("||");           break;
    case 3343: Serial.println("stop");         break;
    case 3344: Serial.println("<<");           break;
    case 3345: Serial.println(">>");           break;
    case 3352: Serial.println(">");            break;
    case 3356: Serial.println("smart search"); break;

    default:
      Serial.print("unknown code: ");
      Serial.println(key);
  }

  for(int i = 4; i < 10; ++i)
  {
    digitalWrite(i, LOW);
  }

  switch (key)
  {
    case 1409: // 2: Forward
      digitalWrite(4, HIGH);
      break;

    case 1412: // 5: Backward
      digitalWrite(5, HIGH);
      break;

    case 1411: // 4
      g_forward = true;
      break;

    case 1413: // 6:
      g_forward = false;
      break;

    case 146: // vol+:
      if (g_delay > stepper.resolution) g_delay -= stepper.resolution;
      break;

    case 147: // vol-
      g_delay += stepper.resolution;
      break;

    default:
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      g_delay = 0;
  }
}

void setup()
{
  pinMode(3, INPUT);
  Serial.begin(9600);
  infra.registerEventReceiver(infraHandler);
}

void loop()
{
  if (g_forward)
  {
    stepper.forward();
  }
  else
  {
    stepper.backward();
  }
  delay(g_delay);
}


