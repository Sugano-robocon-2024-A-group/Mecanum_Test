#include <Arduino.h>
#include "motor.hpp"
#include "encoder.hpp"
#include "PID.hpp"

// 1回の入力で移動する距離[mm]
float travelDistance = 150.0;

const int test = 0;

// 移動距離の目標設定[mm]
float targetDistance[4] = {0, 0, 0, 0}; // 各ホイールの移動距離目標

//許容誤差[mm]
const int allowableError = 1;

void setup()
{
  setupMotors();
  setupEncoders();
  
  stopMotors();

  Serial.begin(115200);
}

void loop()
{
  bool reachedTarget = true;

  float currentDistance = encoderCount[test] * distancePerCount; // 現在の移動距離
  float controlSignal = pidCompute(test, targetDistance[test], currentDistance);

  // 制御信号に基づいてモーターを駆動
  driveMotor(test, controlSignal);

  // シリアルモニタでデバッグ情報出力
  Serial.print(targetDistance[test]);
  Serial.print("  ");
  Serial.print(currentDistance);
  Serial.print("  ");
  Serial.println(controlSignal);

  // 全ホイールが目標距離に到達したかを確認
  if (abs(currentDistance - targetDistance[test]) > allowableError)
  {
    reachedTarget = false;
  }

  if (reachedTarget)
  {
    Serial.println("Reached");

    stopMotors(); // 現在の移動を停止
//    resetEncoders();
//    resetPID();
//    for (int i = 0; i < 4; i++)
//    {
//      targetDistance[i] = 0;
//    }

    if (Serial.available() > 0)
    {
      switch(Serial.read())
      {
        case '1':
          for (int i = 0; i < 4; i++)
          {
            targetDistance[i] = travelDistance;
          }
          break;
        case '2':
          for (int i = 0; i < 4; i++)
          {
            targetDistance[i] = -travelDistance;
          }
          break;
      }
    }
  }
}
