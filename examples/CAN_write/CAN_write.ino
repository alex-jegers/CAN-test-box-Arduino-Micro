#include <SPI.h>
#include "mcp2515.h"

struct can_frame canMsg1;
struct can_frame canMsg2;
MCP2515 mcp2515(10);


void setup() {
  canMsg1.can_id  = 0x0F6;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x8E;
  canMsg1.data[1] = 0x87;
  canMsg1.data[2] = 0x32;
  canMsg1.data[3] = 0xFA;
  canMsg1.data[4] = 0x26;
  canMsg1.data[5] = 0x8E;
  canMsg1.data[6] = 0xBE;
  canMsg1.data[7] = 0x86;

  canMsg2.can_id  = 0xB00B;
  canMsg2.can_dlc = 5;
  canMsg2.data[0] = 0xDE;
  canMsg2.data[1] = 0xAD;
  canMsg2.data[2] = 0x00;
  canMsg2.data[3] = 0xBE;
  canMsg2.data[4] = 0xEF;
  
  while (!Serial);
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_16MHZ);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");
}

void loop() {
  mcp2515.sendMessage(&canMsg1);
  canMsg1.data[0]++;
  delay(500);

  mcp2515.sendMessage(&canMsg2);
  delay(500);
}
