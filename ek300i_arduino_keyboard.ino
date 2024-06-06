
// 
//    ek300i_arduino_keyboard.ino
//    Copyright (C) 2024  burigyu
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.
// 

#include "Keyboard.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

float extractWeight(String message){
  
  String signString = message.substring(3,4); // 符号の抽出
  String dataString = message.substring(4,12); //数値だけを抽出
  float weight = dataString.toFloat(); // 浮動小数点へ変換
  
  if (signString == "-"){
    weight = weight * -1; // 符号の反転
  }

  return(weight);
}

void setup() {
  Serial.begin(115200); // ハードウェアシリアルを準備
  while (!Serial) {
    ; // シリアルポートの準備ができるのを待つ(Leonardoのみ必要)
  }
  Serial.println(F("Ready"));
  mySerial.begin(1200); // ソフトウェアシリアルの初期化
  Keyboard.begin(); // USB キーボードの初期化
}

void loop() {
  if (mySerial.available()){
    String receivedString = "";
    while(mySerial.available()){
      char c  = mySerial.read();
      receivedString += c;
      
      delay(10);
    }
    
    Serial.print(receivedString);

    if (receivedString.substring(0,2) == "ST") {
       // 正常な測定
        // // dataString = receivedString.substring(4,12); //数値だけを抽出
        // // float weight = dataString.toFloat(); // 浮動小数点へ変換
        // // Serial.println(weight);
      float weight = extractWeight(receivedString);
        //String weightString = String(weight, 2); // 小数点以下2桁の文字列へ変換
        //Keyboard.print(weightString);
      Serial.println(weight);
      Keyboard.print(weight);
      Keyboard.write('\n'); // 改行
    }
    else if (receivedString.substring(0,2) == "QT"){       
      // 個数モード
      //dataString = receivedString.substring(4,12); //数値だけを抽出
      float pcs = extractWeight(receivedString);
      long pcsInt = (long)pcs; // 整数へ変換
      Serial.println(pcsInt);
      Keyboard.print(pcsInt);
      Keyboard.write('\n'); // 改行     
    }
    else if (receivedString.substring(0,2) == "US"){
      // 不安定
      float weight = extractWeight(receivedString);
      Serial.print(F("Balance unstable. "));
      Serial.println(weight);
      Keyboard.print(weight);
      Keyboard.print("U");
      Keyboard.write('\n'); // 改行
    }  
    else if (receivedString.substring(0,2) == "OL"){
      // 測定範囲外
      float weight = extractWeight(receivedString);
      Serial.print(F("Balance out of range. "));
      Serial.println(weight);
      Keyboard.print(weight);
      Keyboard.print(F("OL"));
      Keyboard.write('\n'); // 改行
      // 実際には液晶にE表示だとデータは送信されない
    }

  }
}
