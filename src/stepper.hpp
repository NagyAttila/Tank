#ifndef STEPPER_HPP
#define STEPPER_HPP

class Stepper
{
public:
  Stepper(int a, int b, int c, int d);

  void forward();
  void backward();

  static const unsigned int resolution = 10;

protected:
  void step();

  int m_idx;
  int m_pins[4];

  static const unsigned int steps = 8;

  static int m_states[4][steps];
};

#endif

