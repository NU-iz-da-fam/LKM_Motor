#include <LKM_Motor.h>

LKM_Motor motor(1, 8, 5);

void setup() {
  motor.Change_Baudrate(2000000);
  motor.Serial_Init();
  motor.Set_Need_Receive(true);
  Serial.begin(115200);
  pinMode(11, OUTPUT);  // LED2 NTU ASR-LAB
  pinMode(12, OUTPUT);  // LED3 NTU ASR-LAB
}

void loop() {
  digitalWrite(11, HIGH);  // LED2 ON
  Serial.println("-> Go to 0 !");
  // send multi-round command to motor, go to 0 degree, speed = 300
  motor.Write_Angle_MultiRound(0.0, 200.0);
  motor.Print_Data();
  delay(2000);

  digitalWrite(12, HIGH);  // LED3 ON
  Serial.println("-> Go to -300 !");
  motor.Write_Angle_MultiRound(-300.0, 200.0);
  motor.Print_Data();
  delay(2000);
  digitalWrite(12, LOW);  // LED3 OFF
}
