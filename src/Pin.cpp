//
// Created by lenovo on 26-10-2025.
//

#include "../include/Pin.h"


Pin::Pin(int const pinId, PinType const pinType, int const parentNodeId)
   : pinId(pinId), type(pinType), parentNodeId(parentNodeId) {}
