#include "UARTConnection.h"
#include <utility>

UARTConnection::UARTConnection(std::string portName, int baudRate) : _portName(std::move(portName)), _baudRate(baudRate) {}

UARTConnection::~UARTConnection() {}
