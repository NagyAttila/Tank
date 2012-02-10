#include "infra.hpp"
#include <Arduino.h>

static const int TIME_START = 2500;     // start signal (Microseconds)
static const int TIME_1     = 1000;     // Binary 1 (Microseconds)
static const int TIME_0     = 500;      // Binary 0 (Microseconds)

#define isX(t,x) ((t > 3*(x)/4) && (t < 5*(x)/4))
#define is0(t) isX(t,TIME_0)
#define is1(t) isX(t,TIME_1)
#define isStart(t) isX(t,TIME_START)

static Infra * self;

static unsigned long elapsedTime()
{
  static unsigned long before = micros();
  unsigned long now = micros();
  unsigned long elapsed = before < now ? now - before : 0xFFFFFFFFUL - (now - before);
  before = now;
  return elapsed;
}

void Infra::interruptHandler()
{
  // compute elapsed time since last change
  unsigned long elapsed = elapsedTime();

  if (LOW == digitalRead(self->m_pin)) { return; } // measure low periods only

  switch (self->m_state)
  {
    case Infra::WF_START:
      if (isStart(elapsed))
      {
        self->m_newKey = 0;
        self->m_bitCount = 0;
        self->m_state = WF_BITS;
      }
      break;

    case Infra::WF_BITS:
      self->m_newKey <<= 1;
      ++self->m_bitCount;

      if (is1(elapsed))      { self->m_newKey |= 1; }
      else if (is0(elapsed)) { }
      else                   { self->m_state = WF_START; }

      if (12 == self->m_bitCount)
      {
        self->m_key = self->m_newKey;
        self->m_state = WF_START;
        if (self->m_callback) { (*self->m_callback)(self->m_key); }
      }
      break;
  }
}

Infra::Infra()
  : m_pin(3),
    m_int(1),
    m_callback(0),
    m_state(Infra::WF_START),
    m_key(0),
    m_newKey(0),
    m_bitCount(0)
{
  pinMode(m_pin, INPUT);
  self = this;
  attachInterrupt(m_int, interruptHandler, CHANGE);
}

void Infra::registerEventReceiver(Callback * callback)
{
  m_callback = callback;
}

int Infra::getKey()
{
  noInterrupts();
  int key = m_key;
  m_key = 0;
  interrupts();
  return key;
}
