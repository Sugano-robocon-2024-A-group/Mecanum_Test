#ifndef PID_HPP
#define PID_HPP

// エンコーダ関連の設定
const float wheelDiameter = 80.0; // ホイールの直径[mm]
const float encoderPulsesPerRevolution = 750; // エンコーダの1回転あたりのパルス数
const float distancePerCount = (PI * wheelDiameter) / encoderPulsesPerRevolution; // 1カウントあたりの距離[mm]

// PID制御に関する変数の宣言
extern float integral[4];
extern float previous_error[4];

// 関数のプロトタイプ宣言
float pidCompute(int index, float target, float current);
void resetPID();

#endif
