#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include "utils/StringUtils.hpp"
#include <Wire.hpp>
#include <Gate.hpp>

#include <includes.hpp>
#include <optional>
#include <spdlog/spdlog.h>
#include <utils/Range.hpp>

#include <Wire.hpp>
#include <Lexer.hpp>

#include <unordered_map>
#include <variant>
#include <vector>

enum OperatorType {
    MOVE,
    
    RSHIFT,
    LSHIFT,

    AND,
    OR,

    INVALID
};

class Interpreter {
private:
    std::unordered_map<std::string, Wire*> _wires;
    
    // for cleaning up
    std::vector<Gate*> _gatesList;

    OperatorType getOperatorType(std::string& str) {
        std::unordered_map<std::string, OperatorType> types = {
            { "->", OperatorType::MOVE },

            { "RSHIFT", OperatorType::RSHIFT },
            { "LSHIFT", OperatorType::LSHIFT },
            
            { "AND", OperatorType::AND },
            { "OR", OperatorType::OR }
        };

        if(types.contains(str)) {
            return types[str];
        }

        return OperatorType::INVALID;
    }

    Wire* getWireWithCreate(std::string& wire) {
        if(!_wires.contains(wire)) {
            _wires[wire] = new Wire(wire, (DataType)0);
        }

        return _wires[wire];
    }

public:
    Interpreter() {}
    ~Interpreter() {
        for(Gate*& gate : _gatesList) {
            delete gate;
        }

        for(auto& pair : _wires) {
            delete pair.second;
        }
    }

    bool runLiteralOrIdentifier(std::vector<Token>& tokens) {
        OperatorType operatorType = getOperatorType(tokens[1].value);

        if(tokens[0].type != TokenType::LITERAL && tokens[0].type != TokenType::IDENTIFIER) {
            return false;
        }
        else if(tokens[1].type != TokenType::OPERATOR || operatorType == OperatorType::INVALID) {
            return false;
        }

        std::variant<DataType, Gate*, Wire*> lHS;
        if(tokens[0].type == TokenType::IDENTIFIER) {
            lHS = getWireWithCreate(tokens[0].value);
        }
        else if(tokens[0].type == TokenType::LITERAL) {
            lHS = AOCUtil::strtonumeric<DataType>(tokens[0].value.c_str());
        }


        if(operatorType == OperatorType::MOVE) {
            if(tokens[2].type != TokenType::IDENTIFIER) {
                return false;
            }

            Wire* wire = getWireWithCreate(tokens[2].value);
            wire->setValue(lHS);
        }
        else if(operatorType == OperatorType::AND || operatorType == OperatorType::OR) {
            if(tokens[2].type != TokenType::IDENTIFIER || tokens[3].type != TokenType::OPERATOR || tokens[4].type != TokenType::IDENTIFIER) {
                return false;
            }
            
            Wire* rHS = getWireWithCreate(tokens[2].value);
            Gate* gate;
            
            if(operatorType == OperatorType::AND) {
                gate = new AndGate(lHS, rHS);
            }
            else {
                gate = new OrGate(lHS, rHS);
            }


            Wire* wire = getWireWithCreate(tokens[4].value);
            wire->setValue(gate);
            
            _gatesList.push_back(gate);
        }
        else if(operatorType == OperatorType::LSHIFT || operatorType == OperatorType::RSHIFT) {
            if(tokens[2].type != TokenType::LITERAL || tokens[3].type != TokenType::OPERATOR || tokens[4].type != TokenType::IDENTIFIER) {
                return false;
            }

            DataType shiftAmount = AOCUtil::strtonumeric<DataType>(tokens[2].value.c_str());
            Gate* gate;

            if(operatorType == OperatorType::LSHIFT) {
                gate = new LShiftGate(lHS, shiftAmount);
            }
            else {
                gate = new RShiftGate(lHS, shiftAmount);
            }

            Wire* wire = getWireWithCreate(tokens[4].value);
            wire->setValue(gate);

            _gatesList.push_back(gate);
        }
        else {
            return false;
        }

        return true;
    }

    bool run(std::vector<Token> tokens) {
        if(tokens.size() <= 0) return false;

        switch(tokens[0].type) {
        case TokenType::KEYWORD: {
            if(tokens[0].value == "NOT") {
                if(tokens[1].type != TokenType::IDENTIFIER || tokens[2].type != TokenType::OPERATOR || tokens[3].type != TokenType::IDENTIFIER) {
                    return false;
                }

                Wire* lHS = getWireWithCreate(tokens[1].value);
                std::string wire = tokens[3].value;

                Gate* gate = new NotGate(lHS);

                getWireWithCreate(wire)->setValue(gate);
                _gatesList.push_back(gate);
            }

            return true;
        }
        case TokenType::LITERAL: 
        case TokenType::IDENTIFIER:
            return runLiteralOrIdentifier(tokens);
        default: return false;
        }
    }


    std::optional<Wire*> getWire(std::string wire) {
        if(!_wires.contains(wire)) {
            return std::nullopt;
        }

        return _wires[wire];
    }

    void print() {
        for(auto pair : _wires) {
            spdlog::info("{}: {}", pair.first, pair.second->getValue());
        }
    }
};

#endif