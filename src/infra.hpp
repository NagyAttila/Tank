#ifndef _INFRA_HPP_
#define _INFRA_HPP_

class Infra
{
public:
  Infra(int pin);

  typedef void Callback(int key);
  void registerEventReceiver(Callback * callback);

  int getKey();

protected:
  int        m_pin;
  Callback * m_callback;
};


#endif
