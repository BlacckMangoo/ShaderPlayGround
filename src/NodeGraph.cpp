#include <vector>
#include <unordered_map>
#include "../include/Utils.h"

enum NodeType {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
};

struct Pin {

    Pin( int const id , bool const  isInput ) : id(id), isInput(isInput) {};
    int id ;
    bool isInput ;
};

struct Node {

    Node(const std::vector<int>& inputPins, const std::vector<int>& outputPins, const NodeType type , int id = -1) {
        this->type = type;
        this->id = 1 ;
        for (const auto& pin_id : inputPins) {
            Pin pin(GenerateId(), true);
            input_pins.push_back(pin);
        }
        for (const auto& pin_id : outputPins) {
            Pin pin(pin_id, true);
            input_pins.push_back(pin);
        }
    }

    std::vector<Pin> input_pins;
    std::vector<Pin> output_pins;
    NodeType type;
    int id{} ;
    float value = 0.0f;

};

struct Link {
     int input_pin_id;
     int output_pin_id;
    int id ;
};


class NodeGraph {

public:
    std::unordered_map<int, Node> nodes;
    std::unordered_map<int, Pin> pins;
    std::unordered_map<int, Link> links;

};