#include "ESP8266.h"
#include "DHT.h"

#define SSID        "NCUTV-2.4GHz"
#define PASSWORD    "ncutv123"
#define HOST_NAME   "184.106.153.149" //thingsgirving 's IP
#define HOST_PORT   (80)

ESP8266 wifi(Serial1);
DHT dht;

int dhtbuf[2];  //TEMP and HUM 's buffer
void setup(void)
{
    Serial.begin(9600);
    Serial.print("setup begin\r\n");
    
    Serial.print("FW Version:");
    Serial.println(wifi.getVersion().c_str());
     
    dht.setup(2);  //DHT22 is connet on pin 2
      
    if (wifi.setOprToStationSoftAP()) {
        Serial.print("to station + softap ok\r\n");
    } else {
        Serial.print("to station + softap err\r\n");
    }
 
    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Join AP success\r\n");
        Serial.print("IP:");
        Serial.println( wifi.getLocalIP().c_str());       
    } else {
        Serial.print("Join AP failure\r\n");
    }
    
    if (wifi.disableMUX()) {
        Serial.print("single ok\r\n");
    } else {
        Serial.print("single err\r\n");
    }
    
    Serial.print("setup end\r\n");
}
 
void loop(void)
{
    uint8_t buffer[128] = {0};  
    
    if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
        Serial.print("create tcp ok\r\n");
    } else {
        Serial.print("create tcp err\r\n");
    }
        dhtbuf[0] = dht.getHumidity()*10;
        dhtbuf[1] = dht.getTemperature()*10;
        char buf[5];
        String HH, TT;
        buf[0] = 48 + dhtbuf[1] / 100;
        buf[1] = 48 + (dhtbuf[1]-(dhtbuf[1]/100)*100) / 10;
        buf[3] = 48 + dhtbuf[1] % 10 ;
        buf[2] = 46;
        TT = (String(buf)).substring( 0, 4 );
        buf[0] = 0x30 + dhtbuf[0] / 100;
        buf[1] = 0x30 + (dhtbuf[1]-(dhtbuf[1]/100)*100) / 10;
        buf[3] = 0x30 + dhtbuf[0] % 10;
        buf[2] = 46;
        HH = (String(buf)).substring( 0, 4 );
        
    String hello ;
    hello = "GET /update?key=PT2AWDSC8R7MI4IW&field1=" + HH + "&field2=" + TT + "\r\n";
    Serial.println(hello);
    char cmd[100];
    strcpy(cmd, hello.c_str());
    wifi.send((const uint8_t*)cmd, 100);
    
    uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
    if (len > 0) {
        Serial.print("Received:[");
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
        }
        Serial.print("]\r\n");
    }
    
    if (wifi.releaseTCP()) {
        Serial.print("release tcp ok\r\n");
    } else {
        Serial.print("release tcp err\r\n");
    }
    delay(5000);
}
     
