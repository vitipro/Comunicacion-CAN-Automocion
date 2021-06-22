#include <SPI.h>
#include <mcp_can.h>
#include <can-serial.h>
#include <mcp2515_can.h>
#include <mcp2515_can_dfs.h>

#define MSG_LEN 8

const int spiCSPin = 53;
boolean ledON = 1;
unsigned char len;
unsigned char buf[MSG_LEN];

mcp2515_can CAN(spiCSPin); // Set CS pin

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

    while (CAN_OK != CAN.begin(CAN_500KBPS)) {
        Serial.println("CAN BUS Init Failed");
        delay(100);
    }
    Serial.println("CAN BUS  Init OK!");
}

void loop()
{
    len = 0;

    if (CAN_MSGAVAIL == CAN.checkReceive()) {
      
        CAN.readMsgBuf(&len, buf);
        
        unsigned long canID = CAN.getCanId();
        
        Serial.println("-----------------------------");
        Serial.print("Data from ID: 0x");
        Serial.println(canID, HEX);
        
        for (int i = 0; i < len; ++i) {
            Serial.print(buf[i]);
            Serial.print("\t");
            if (ledON && i == 0) {
                digitalWrite(LED_BUILTIN, buf[i]);
                ledON = 0;
                delay(500);
            }
            else if ((!(ledON)) && i == 4) {
                digitalWrite(LED_BUILTIN, buf[i]);
                ledON = 1;
            }
        }
        
        Serial.println();
    }
}
