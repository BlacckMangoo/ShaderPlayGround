#pragma once


#include <vector>
#include <unordered_map>
#include "Pin.h"
#include "imgui.h"

class Node {
public:
    Node() = default;
    explicit Node(int nodeId, int noOfInputPins, int noOfOutputPins, std::unordered_map<int, Pin>& pinDatabase, ImVec2 position);

    int nodeId;
    std::vector<int> inputPins;
    std::vector<int> outputPins;

    mutable bool initialized = false;

    mutable ImVec2 position = ImVec2(0,0);

};

