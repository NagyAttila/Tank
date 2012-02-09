#include "infra.hpp"
#include <Arduino.h>

static const int bin_1 = 1000;     //Binary 1 threshold (Microseconds)
static const int bin_0 = 400;      //Binary 0 threshold (Microseconds)

Infra::Infra(int pin)
  : m_pin(pin),
    m_callback(0)
{
}

void Infra::registerEventReceiver(Callback * callback)
{
  m_callback = callback;
}


int Infra::getKey()
{
  int data[12];
  while(pulseIn(m_pin, LOW) < 2200)
  { //Wait for a start bit
  }

  data[0] = pulseIn(m_pin, LOW);//Start measuring bits, I only want low pulses
  data[1] = pulseIn(m_pin, LOW);
  data[2] = pulseIn(m_pin, LOW);
  data[3] = pulseIn(m_pin, LOW);
  data[4] = pulseIn(m_pin, LOW);
  data[5] = pulseIn(m_pin, LOW);
  data[6] = pulseIn(m_pin, LOW);
  data[7] = pulseIn(m_pin, LOW);
  data[8] = pulseIn(m_pin, LOW);
  data[9] = pulseIn(m_pin, LOW);
  data[10] = pulseIn(m_pin, LOW);
  data[11] = pulseIn(m_pin, LOW);

  for(int i=0;i<11;i++)
  {  //Parse them
    if(data[i] > bin_1)
    {  //is it a 1?
      data[i] = 1;
    }
    else {
      if(data[i] > bin_0)
      {//is it a 0?
        data[i] = 0;
      }
      else
      {
        data[i] = 2;  //Flag the data as invalid; I don't know what it is!
      }
    }
  }

  for(int i=0;i<11;i++)
  {  //Pre-check data for errors
    if(data[i] > 1)
    {
      return -1;     //Return -1 on invalid data
    }
  }

  int result = 0;
  int seed = 1;
  for(int i=0;i<11;i++)
  {  //Convert bits to integer
    if(data[i] == 1)
    {
      result += seed;
    }
    seed = seed * 2;
  }
  return result;     //Return key number
}
