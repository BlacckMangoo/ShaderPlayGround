#pragma once

#include <unordered_map>
#include <vector>
#include "Pin.h"
#include "Node.h"

class NodeGraph {
public:
    void AddEdge(int fromPinId, int toPinId);
    void AddNode( int noOfInputPins, int noOfOutputPins);

    void PrintAllData() const;

    Node* GetNode(const int nodeId) {
        const auto it = nodes.find(nodeId);
        if (it != nodes.end()) {
            return &it->second;
        }
        return nullptr;
    }


    std::unordered_map<int, Node> nodes; // nodeId -> Node
    std::unordered_map<int, Pin> pinDatabase; // pinId -> Pin
    std::unordered_map<int, std::vector<int>> adjList; // pinId -> connected pinIds
};
