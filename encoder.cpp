#include <Arduino.h>
#include "encoder.hpp"

// エンコーダ関連の変数
volatile int encoderCount[4] = {0, 0, 0, 0}; // 各ホイールのエンコーダカウント

void IRAM_ATTR handleEncoder(int index)
{
  if (index < 2)  // 左側のモーターの場合
  {
    if (digitalRead(encoderA[index]) != digitalRead(encoderB[index]))
    {
      encoderCount[index]++;
    }
    else
    {
      encoderCount[index]--;
    }
  }
  else  // 右側のモーターの場合
  {
    if (digitalRead(encoderA[index]) == digitalRead(encoderB[index]))
    {
      encoderCount[index]++;
    }
    else
    {
      encoderCount[index]--;
    }    
  }
}

void setupEncoders()
{
  for (int i = 0; i < 4; i++)
  {
    pinMode(encoderA[i], INPUT_PULLUP);
    pinMode(encoderB[i], INPUT_PULLUP);
  }

  attachInterrupt(digitalPinToInterrupt(encoderA[0]), []() { handleEncoder(0); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[1]), []() { handleEncoder(1); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[2]), []() { handleEncoder(2); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderA[3]), []() { handleEncoder(3); }, CHANGE);
}

void resetEncoders()
{
  for (int i = 0; i < 4; i++)
  {
    encoderCount[i] = 0;
  }
}
