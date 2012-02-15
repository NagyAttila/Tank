#include "stepper.hpp"
#include <Arduino.h>

int Stepper::m_states[4][steps] = 
{
  //{1,0,0,0},
  //{0,1,0,0},
  //{0,0,1,0},
  //{0,0,0,1}
  {1,0,0,0,0,0,1,1},
  {1,1,1,0,0,0,0,0},
  {0,0,1,1,1,0,0,0},
  {0,0,0,0,1,1,1,0}
};

Stepper::Stepper(int a, int b, int c, int d)
  : m_idx(0)
{
  m_pins[0] = a;
  m_pins[1] = b;
  m_pins[2] = c;
  m_pins[3] = d;

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);

  step();
}

void Stepper::forward()
{
  m_idx = (m_idx + 1) % steps;
  step();
}

void Stepper::backward()
{
  m_idx = (m_idx - 1) % steps;
  step();
}

void Stepper::step()
{
  digitalWrite(m_pins[0], m_states[0][m_idx]);
  digitalWrite(m_pins[1], m_states[1][m_idx]);
  digitalWrite(m_pins[2], m_states[2][m_idx]);
  digitalWrite(m_pins[3], m_states[3][m_idx]);
}

