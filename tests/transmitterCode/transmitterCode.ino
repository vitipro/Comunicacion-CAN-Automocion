#include <SPI.h>
#include <mcp_can.h>
#include <can-serial.h>
#include <mcp2515_can.h>
#include <mcp2515_can_dfs.h>

#define MSG_LEN 8

const int spiCSPin = 53;

mcp2515_can CAN(spiCSPin); // Set CS pin

unsigned char message[MSG_LEN] = {0, 1, 2, 3, 1, 5, 6, 7};

void setup()
{
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS))
    {
        Serial.println("CAN BUS init Failed");
        delay(100);
    }
    Serial.println("CAN BUS Shield Init OK!");
}

void loop()
{
    Serial.println("In loop");
    CAN.sendMsgBuf(0x43, 0, MSG_LEN, message);
    delay(1000);
}
