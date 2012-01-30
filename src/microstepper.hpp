#ifndef MICROSTEPPER_HPP
#define MICROSTEPPER_HPP

class MicroStepper
{
public:
  static const int m_steps = 64;

  MicroStepper(int a, int b, int c, int d);

  void forward();
  void backward();

protected:
  void step();

  int m_idx;
  int m_pins[4];

  int m_states[4][m_steps];
};

#endif

