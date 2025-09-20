#include <SPI.h>
#include "mcp2515.h"

struct can_frame can_msg;
MCP2515 mcp2515(10);


void setup() {
  Serial.begin(115200);

  mcp2515.reset();

  /*
    This will set the baud rate. The second argument, "MCP_16MHZ",
    tells the software what the speed of the physical clock on the board
    is. Dont change that.
  */
  mcp2515.setBitrate(CAN_500KBPS, MCP_16MHZ);  
  //mcp2515.setBitrate(CAN_250KBPS, MCP_16MHZ);
  //mcp2515.setBitrate(CAN_125KBPS, MCP_16MHZ);

  /*
    All configuration needs to happen before setting normal mode.
    Default mode is config mode.
  */
  mcp2515.setNormalMode();  
}

void loop() {
  
  /*
    This checks to see if there's new data in one of the buffers.
    Will return ERROR_NOMSG if there's not.
  */
  if (mcp2515.readMessage(&can_msg) == MCP2515::ERROR_OK) {
    /*Formats and prints CAN ID and data length code (DLC).*/
    Serial.print("CAN ID:");
    Serial.print(can_msg.can_id, HEX);
    Serial.print("    Length:"); 
    Serial.print(can_msg.can_dlc, HEX);
    Serial.print("    Data: ");

    /*Formats and prints all the data bytes.*/
    for (int i = 0; i < can_msg.can_dlc; i++)  {
      Serial.print(can_msg.data[i],HEX);
      Serial.print(" ");
    }
    Serial.println();      
  }
  
}
