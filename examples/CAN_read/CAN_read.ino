#include <SPI.h>
#include "mcp2515.h"

struct can_frame canMsg;
MCP2515 mcp2515(10);


void setup() {
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_16MHZ);
  mcp2515.setNormalMode();

}

void loop() {
  
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print("CAN ID:");
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print("  Length:"); 
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print("  Data: ");
    
    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
      Serial.print(canMsg.data[i],HEX);
      Serial.print(" ");
    }

    Serial.println();      
  }
  
}
