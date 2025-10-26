#pragma once


#include <vector>
#include <unordered_map>
#include "Pin.h"

class Node {
public:
    Node() = default;
    explicit Node(int nodeId, int noOfInputPins, int noOfOutputPins, std::unordered_map<int, Pin>& pinDatabase);

    int nodeId;
    std::vector<int> inputPins;
    std::vector<int> outputPins;
};

