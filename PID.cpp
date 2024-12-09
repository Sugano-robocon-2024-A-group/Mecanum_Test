#include <Arduino.h>
#include "PID.hpp"

// PID制御のゲイン
float kp[4] = {1.0, 1.0, 1.0, 1.0};
float ki[4] = {0.0, 0.0, 0.0, 0.0};
float kd[4] = {20.0, 15.0, 20.0, 25.0};
int k[4] = {130, 120, 105, 110};

// PID制御に関する変数
float integral[4] = {0, 0, 0, 0};
float previous_error[4] = {0, 0, 0, 0};

// PID制御計算
float pidCompute(int index, float target, float current)
{
  float error = target - current;
  integral[index] += error;
  float derivative = error - previous_error[index];
  float output = kp[index] * error + ki[index] * integral[index] + kd[index] * derivative;
  previous_error[index] = error;
  if (output > 0)
  {
    output += k[index];
  }
  else if (output < 0)
  {
    output -= k[index];
  }
  return constrain(output, -255, 255); // PWMの範囲に制約
}

void resetPID()
{
  for (int i = 0; i < 4; i++)
  {
    integral[i] = 0.0;
    previous_error[i] = 0.0;
  }
}
