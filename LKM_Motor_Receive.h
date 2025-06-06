#ifndef LKM_Motor_Receive_H
#define LKM_Motor_Receive_H

#include "Arduino.h"
#include "LKM_Motor.h"
#include <map>

class LKM_Motor_Receive {
public:
  LKM_Motor_Receive();
  LKM_Motor_Receive(int serial_port);

  void RegisterMotor(LKM_Motor* motor);
  void Receive_All(const int pack_length);
  bool debug_mode = true; //decide whether to use Serial print debug message in Receive_All() function

private:
  Stream* shared_serial;
  std::map<int, LKM_Motor*> motor_map;
};

#endif
