#ifndef ENCODER_HPP
#define ENCODER_HPP

// エンコーダのピン設定 （左前　左後　右前　右後）
const int encoderA[4] = {36, 0, 2, 12}; // エンコーダA相ピン
const int encoderB[4] = {39, 1, 3, 17}; // エンコーダB相ピン

// エンコーダ関連の変数の宣言
extern volatile int encoderCount[4]; // 各ホイールのエンコーダカウント

// 関数のプロトタイプ宣言
void IRAM_ATTR handleEncoder(int index);
void setupEncoders();
void resetEncoders();

#endif
