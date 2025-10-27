#pragma once

#include <unordered_map>
#include <vector>
#include "Pin.h"
#include "Node.h"

class EditorContext;

class NodeGraph {
public:


    void Init(EditorContext* ctx) { this->m_ctx = ctx; }

    void AddEdge(int fromPinId, int toPinId);
    void AddNode( int noOfInputPins, int noOfOutputPins, ImVec2 position = ImVec2(0,0) );

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

private:
    EditorContext* m_ctx = nullptr;

};
