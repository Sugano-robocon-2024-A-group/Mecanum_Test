#include <Arduino.h>
#include "motor.hpp"

void setupMotors()
{
  for (int i = 0; i < 4; i++)
  {
    // モーターピンを出力に設定
    pinMode(motor_pwm[i], OUTPUT);
    pinMode(motor_dir1[i], OUTPUT);
    pinMode(motor_dir2[i], OUTPUT);
    ledcAttach(motor_pwm[i], 5000, 8);  // PWMの設定
  }
}

// モーターの駆動方向を制御
void driveMotor(int index, float controlSignal)
{
  if (controlSignal >= 0)
  {
    digitalWrite(motor_dir1[index], HIGH);
    digitalWrite(motor_dir2[index], LOW);
  }
  else
  {
    digitalWrite(motor_dir1[index], LOW);
    digitalWrite(motor_dir2[index], HIGH);
    controlSignal = -controlSignal;
  }
  ledcWrite(motor_pwm[index], (int)controlSignal);
}

// モーターを停止
void stopMotors()
{
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(motor_dir1[i], HIGH);
    digitalWrite(motor_dir2[i], HIGH);
    ledcWrite(motor_pwm[i], 0);
  }
}
