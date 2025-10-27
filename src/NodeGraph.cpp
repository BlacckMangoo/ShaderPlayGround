#include "../include/NodeGraph.h"
#include <iostream>
#include "../include/Utils.h"
#include "imnodes.h"


void NodeGraph::AddEdge(int fromPinId, int toPinId)
{
  Pin input_pin = pinDatabase[fromPinId];
  Pin output_pin = pinDatabase[toPinId];

    if ( input_pin.type != PinType::OUTPUT || output_pin.type != PinType::INPUT) {
        std::cerr << "Error: Invalid pin types for edge creation. fromPinId should be OUTPUT and toPinId should be INPUT.\n";
        return;
    }

    if ( input_pin.parentNodeId == output_pin.parentNodeId) {
        std::cerr << "Error: Cannot connect pins from the same node. fromPinId and toPinId belong to the same node.\n";
        return;
    }

    adjList[fromPinId].push_back(toPinId);
}

void NodeGraph::AddNode( int noOfInputPins, int noOfOutputPins, ImVec2 position )
{
    int nodeId = GenerateId();

    Node node(nodeId, noOfInputPins, noOfOutputPins, pinDatabase,position);
    nodes[nodeId] = node;
    for (auto pinId : nodes[nodeId].inputPins) {
        adjList[pinId] = std::vector<int>(); // Initialize adjacency list for pin - will be populated by AddEdge
    }
    for (auto pinId : nodes[nodeId].outputPins) {
        adjList[pinId] = std::vector<int>();
    }


}


void NodeGraph::PrintAllData() const {


    // node data
    for ( auto& node: nodes) {
        std::cout << "Node ID: " << node.first << "\n";
        std::cout << " Input Pins: ";
        for (const auto pinId : node.second.inputPins) {
            std::cout << pinId << " ";
        }
        std::cout << "\n Output Pins: ";
        for (const auto pinId : node.second.outputPins) {
            std::cout << pinId << " ";
        }
        std::cout << "\n";
    }
    std :: cout << "\n";

    // pin data base

    for ( auto& pin : pinDatabase) {
        std::cout << "Pin ID: " << pin.first << ", Type: " << (pin.second.type == PinType::INPUT ? "INPUT" : "OUTPUT")
                  << ", Parent Node ID: " << pin.second.parentNodeId << "\n";
    }

    // adjacency list

    std :: cout << "\n";

    for ( auto & adj : adjList) {
        std::cout << "Pin ID: " << adj.first << " -> Connected Pins: ";
        for ( const auto connectedPinId : adj.second) {
            std::cout << connectedPinId << " ";
        }
        std::cout << "\n";
    }
}
