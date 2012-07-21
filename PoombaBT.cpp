#include "PoombaBT.h"

const unsigned long int PoombaBT::BAUD_RATE = 115200;

const char PoombaBT::END_MESSAGE_CHAR      = '\n';
const char PoombaBT::PROTOCOL_DIVIDER_CHAR = '#';

void PoombaBT::setup(unsigned long int baudRate) {
  Serial1.begin(baudRate); // Used to communicate with the bluetooth device

  Serial.begin(9600);      // Used to debug the application

  receivedMessage = "";
}

void PoombaBT::waitForData() {
  if(Serial1.available()) {
    
    char inByte = Serial1.read();
    
    if (inByte != PoombaBT::END_MESSAGE_CHAR) { // Still receaving the message
      receivedMessage += inByte;
    } else {                                    // Message received start processing
      // TODO Process the message
      Serial.println(receivedMessage);
      Serial.println(getProtocolType(receivedMessage));
      receivedMessage = "";
    }
  }
}

String PoombaBT::getProtocolType(String message) {
  int dividerPosition = message.indexOf(PoombaBT::PROTOCOL_DIVIDER_CHAR);
  return message.substring(0, dividerPosition);
}