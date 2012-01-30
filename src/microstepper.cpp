#include "microstepper.hpp"
#include <Arduino.h>

MicroStepper::MicroStepper(int a, int b, int c, int d)
  : m_idx(0)
{
  m_pins[0] = a;
  m_pins[1] = b;
  m_pins[2] = c;
  m_pins[3] = d;

  for (int i = 0; i < m_steps; ++i)
  {
    double value = sin((double)i * TWO_PI / m_steps);
    int intValue = (0.0 < value) ? 255 * value : 0;

    m_states[0][i] = intValue;
    m_states[1][(i + m_steps * 1 / 4) % m_steps] = intValue;
    m_states[2][(i + m_steps * 2 / 4) % m_steps] = intValue;
    m_states[3][(i + m_steps * 3 / 4) % m_steps] = intValue;
  }

  step();
}

void MicroStepper::forward()
{
  m_idx = (m_idx + 1) % m_steps;
  step();
}

void MicroStepper::backward()
{
  m_idx = (m_idx - 1) % m_steps;
  step();
}

void MicroStepper::step()
{
  analogWrite(m_pins[0], m_states[0][m_idx]);
  analogWrite(m_pins[1], m_states[1][m_idx]);
  analogWrite(m_pins[2], m_states[2][m_idx]);
  analogWrite(m_pins[3], m_states[3][m_idx]);
}

