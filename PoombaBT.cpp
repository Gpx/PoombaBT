#include "PoombaBT.h"

const unsigned long int PoombaBT::BAUD_RATE = 115200;

const char PoombaBT::END_MESSAGE_CHAR      = '\n';
const char PoombaBT::PROTOCOL_DIVIDER_CHAR = '#';

const char PoombaBT::MEDP_PROTOCOL_IDENTIFIER[] = "medp";

void PoombaBT::setup(unsigned long int baudRate) {
  Serial.begin(9600);      // Used to debug the application
  
  Serial1.begin(baudRate); // Used to communicate with the bluetooth device

  receivedMessage = "";
}

void PoombaBT::waitForData() {
  if (Serial1.available()) {
    
    char inByte = Serial1.read();
    
    if (inByte != PoombaBT::END_MESSAGE_CHAR) { // Still receaving the message
      receivedMessage += inByte;
    } else {                                    // Message received start processing
      processMessage(receivedMessage);
      receivedMessage = "";
    }
  }
}

void PoombaBT::processMessage(String message) {
  String protocolIdentifier = getProtocolIdentifier(message);
  if (protocolIdentifier == PoombaBT::MEDP_PROTOCOL_IDENTIFIER) {
    MEDP medp;
    medp.execute(message);
  }
}

String PoombaBT::getProtocolIdentifier(String message) {
  int dividerPosition = message.indexOf(PoombaBT::PROTOCOL_DIVIDER_CHAR);
  return message.substring(0, dividerPosition);
}