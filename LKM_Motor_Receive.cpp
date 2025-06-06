#include "LKM_Motor_Receive.h"

LKM_Motor_Receive::LKM_Motor_Receive(){
}

LKM_Motor_Receive::LKM_Motor_Receive(int serial_port) {
  if(serial_port == 1) shared_serial = &Serial1;
  else if(serial_port == 2) shared_serial = &Serial2;
  else if(serial_port == 3) shared_serial = &Serial3;
  else if(serial_port == 4) shared_serial = &Serial4;
  else if(serial_port == 5) shared_serial = &Serial5;
  else if(serial_port == 6) shared_serial = &Serial6;
  else if(serial_port == 7) shared_serial = &Serial7;
  else Serial.println("===== Serial Port Error! =====");
}

void LKM_Motor_Receive::RegisterMotor(LKM_Motor* motor) {
  int motor_id = motor->GetID();
  motor_map[motor_id] = motor;
  motor->SetBus(this); // 告訴該馬達它的 Bus 是我
}

void LKM_Motor_Receive::Receive_All(const int pack_length) {
  int id = 0; //馬達ID
  int data_length = pack_length - 6;
  uint8_t temp; //每次接收進來之byte
  uint8_t data[pack_length] = {0};

  int count_RX = 0;
  bool get_header = false;
  if (!shared_serial) {
    Serial.println("Error: shared_serial is nullptr!");
    return;
  }
  while (shared_serial->available() > 0) {
    temp = shared_serial->read(); // Read incoming byte

    if (!get_header) { // If header not yet received
      if (temp == 0x3E) { // Check if it's the header byte
        data[0] = temp;
        count_RX = 1;
        get_header = true;
      }
      // else: discard this byte
    } 
    else { // Header already received
      data[count_RX] = temp;
      if (count_RX == 2) { // ID
        id = (int)data[count_RX];
        if (debug_mode) Serial.printf("Packet received for ID %d\n", id);
      } 
      else if (count_RX == 3) { // Data length check
        if (data[count_RX] != data_length) {
          if (debug_mode) Serial.printf("===== LKM_Motor_Receive ID:%d Packet Error: Data Length Error! =====\n", id);
          break;
        }
      } 
      else if (count_RX == 4) { // Header checksum validation
        uint8_t headerCheckSum = data[0] + data[1] + data[2] + data[3];
        if (headerCheckSum != data[count_RX]) {
          if (debug_mode) Serial.printf("===== LKM_Motor_Receive ID:%d Packet Error: Header Checksum Error! =====\n", id);
          break;
        }
      } 
      else if (count_RX == data_length + 5) { // Data checksum validation
        uint8_t dataCheckSum = 0;
        for (int i = 5; i < count_RX; i++) {
          dataCheckSum += data[i];
        }
        if (dataCheckSum != data[count_RX]) {
          if (debug_mode) Serial.printf("===== LKM_Motor_Receive ID:%d Packet Error: Data Checksum Error! =====\n", id);
          break;
        } 
        else {
          if (motor_map.count(id)) {
            motor_map[id]->Unpack(data); // 如果有註冊對應的馬達，呼叫它的解封包函數
          }
          break;
        }
      }
      count_RX++;
    }
  }
}
