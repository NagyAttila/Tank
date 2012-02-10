#ifndef _INFRA_HPP_
#define _INFRA_HPP_

class Infra
{
public:
  Infra();

  typedef void Callback(int key);
  void registerEventReceiver(Callback * callback);

  int getKey();

protected:
  static void interruptHandler();

  enum State
  {
    WF_START,
    WF_BITS,
  };

  int        m_pin;
  int        m_int;
  Callback * m_callback;
  State      m_state;
  int        m_key;
  int        m_newKey;
  int        m_bitCount;
};


#endif
