#ifndef POOMBA_BT_H
#define POOMBA_BT_H

#include "Arduino.h"
#include "MEDP.h"

/**
Class to receive a data stream via bluetooth
*/
class PoombaBT {
public:
  void setup(unsigned long int baudRate = PoombaBT::BAUD_RATE); /** Setup the bluetooth device */
  void waitForData();                                           /** Porcess incoming data */

private:
  /** Device constants */
  static const unsigned long int BAUD_RATE;
  
  /** Protocol constants declarations */
  static const char END_MESSAGE_CHAR;
  static const char PROTOCOL_DIVIDER_CHAR;

  /** Protocol identifiers constants declaration */
  static const char MEDP_PROTOCOL_IDENTIFIER[];

  String receivedMessage;

  void processMessage(String message);
  String getProtocolIdentifier(String message);
};

#endif