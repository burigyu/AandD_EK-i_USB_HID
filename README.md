# AandD_EK-i_USB_HID
A&Dの電子天びん EK-iシリーズとArduino Leonardoなどを接続して，USBキーボードとしてふるまわせるスケッチです。
RS232CをTTLシリアルに変換するモジュール（MAX232シリーズなど）が必要です。
電子天びん側の通信条件は，8ビットノンパリティにする必要があります。
テストはEK-300iで行いました。A&Dの他のシリーズでもおそらく使えるでしょう。

Connects your A&D EK-i series electronic balance to PCs as a USB keyboard.
Your need Arduino Leonard and RS232C-TTL converter.
Balance's settings: 8 bit, none parity.
Tested on EK-300i.
