#pragma once


enum PinType {
    INPUT,
    OUTPUT
};

struct Pin {
    Pin() = default ;
    Pin(int pinId, PinType pinType, int parentNodeId);

    int pinId;
    PinType type;
    int parentNodeId;
};


