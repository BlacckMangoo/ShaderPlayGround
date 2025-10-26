//
// Created by lenovo on 26-10-2025.
//

#include "../include/Node.h"
#include "../include/Utils.h" // For GenerateId()

Node::Node(const int nodeId, const int noOfInputPins, const int noOfOutputPins, std::unordered_map<int, Pin>& pinDatabase)
    : nodeId(nodeId)
{
    for (int i = 0; i < noOfInputPins; ++i) {
        int id = GenerateId();
        pinDatabase[id] = Pin(id, PinType::INPUT, nodeId);
        inputPins.push_back(id);
    }
    for (int j = 0; j < noOfOutputPins; ++j) {
        int id = GenerateId();
        pinDatabase[id] = Pin(id, PinType::OUTPUT, nodeId);
        outputPins.push_back(id);
    }
}