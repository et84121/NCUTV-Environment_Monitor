# NCUTV-Environment_Monitor
###攝影棚裡的溫溼度監控裝置

1. 以arduino Leonardo為主體  
2. [ESP8266 串口WIFI](http://goo.gl/dyOonf) 為通訊裝置  
3. [DHT22 數字溫濕度傳感器 AM2302](http://goo.gl/xlAVeV)作為溫溼度的量測器  
4. 串接thingspeak平台[DHT22 channel](https://thingspeak.com/channels/29670)   
5. 並且把監控資訊加到自已的網頁裡頭[小中大電視台](http://ncutv.ncu.edu.tw/)方便查看 

未來想加入[光敏電阻]探測是否有人進入(因為人進來這個房間一定會開日光燈)

用到的函式庫  
[arduino-DHT](https://github.com/markruys/arduino-DHT) DHT22的lib  
[ITEADLIB_Arduino_WeeESP8266](https://github.com/itead/ITEADLIB_Arduino_WeeESP8266) WIFI的lib  
