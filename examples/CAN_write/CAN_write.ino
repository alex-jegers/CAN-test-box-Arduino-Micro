#include <SPI.h>
#include "mcp2515.h"

struct can_frame can_msg_1;
struct can_frame can_msg_2;
MCP2515 mcp2515(10);


void setup() {
  /*
    Here you can change the information contained in the CAN frame. ID is obv the identifier. DLC
    is the Data Length Code and specifies how many bytes will be sent. The data array is the data.
    You can add as many can_frame structs as you'd like.
  */
  can_msg_1.can_id  = 0x69;
  can_msg_1.can_dlc = 8;
  can_msg_1.data[0] = 0x8E;
  can_msg_1.data[1] = 0x87;
  can_msg_1.data[2] = 0x32;
  can_msg_1.data[3] = 0xFA;
  can_msg_1.data[4] = 0x26;
  can_msg_1.data[5] = 0x8E;
  can_msg_1.data[6] = 0xBE;
  can_msg_1.data[7] = 0x86;

  can_msg_2.can_id  = 0xB00B;
  can_msg_2.can_dlc = 5;
  can_msg_2.data[0] = 0xDE;
  can_msg_2.data[1] = 0xAD;
  can_msg_2.data[2] = 0x00;
  can_msg_2.data[3] = 0xBE;
  can_msg_2.data[4] = 0xEF;

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
  mcp2515.sendMessage(&can_msg_1);
  
  /*
    Changing some of the data in can_msg_1, this should be 
    seen on the receiving end.
  */
  can_msg_1.data[0]++;            
  delay(500);

  mcp2515.sendMessage(&can_msg_2);
  delay(500);
}
