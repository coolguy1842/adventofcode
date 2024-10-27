#ifndef __CIRCUIT_HPP__
#define __CIRCUIT_HPP__

#include "utils/StringUtils.hpp"
#include <Includes.hpp>

#include <Lexer.hpp>
#include <Wire.hpp>

#include <optional>
#include <spdlog/spdlog.h>
#include <unordered_map>
#include <variant>
#include <vector>

class Circuit {
private:
    Lexer _lexer;
    std::unordered_map<std::string, Wire> _wires;

    GateType getOperatorType(std::string& str) {
        std::unordered_map<std::string, GateType> types = {
            { "->", GateType::MOVE },

            { "RSHIFT", GateType::RSHIFT },
            { "LSHIFT", GateType::LSHIFT },
            
            { "AND", GateType::AND },
            { "OR", GateType::OR }
        };

        if(types.contains(str)) {
            return types[str];
        }

        return GateType::INVALID;
    }

public:
    Circuit() {
        
    }

    ~Circuit() {}


    bool runLine(std::string& line) {
        std::optional<std::vector<Token>> tokensOpt = _lexer.analyse(line);
        if(!tokensOpt.has_value()) {
            return false;
        }

        std::vector<Token> tokens = tokensOpt.value();
        if(tokens.size() <= 0) {
            return false;
        }

        switch(tokens[0].type) {
        case TokenType::KEYWORD: {
            if(tokens[0].value == "NOT") {
                if(tokens.size() != 4) {
                    return false;
                }

                Token lHS = tokens[1];
                Token op = tokens[2];
                Token rHS = tokens[3];
                if(
                    (lHS.type != TokenType::IDENTIFIER && lHS.type != TokenType::LITERAL) ||
                    op.type != TokenType::OPERATOR || getOperatorType(op.value) != GateType::MOVE ||
                    (rHS.type != TokenType::IDENTIFIER && rHS.type != TokenType::LITERAL)
                ) {
                    return false;
                }

                Wire& outputWire = getWire(rHS.value);
                outputWire.setGateType(GateType::NOT);

                if(lHS.type == TokenType::IDENTIFIER) {
                    outputWire.setSources({ &getWire(lHS.value) });
                }
                else {
                    outputWire.setSources({ AOCUtil::strtonumeric<DataType>(lHS.value.c_str()) });
                }
            }
            else {
                return false;
            }

            return true;
        }
        case TokenType::IDENTIFIER: case TokenType::LITERAL: {
            if(tokens.size() < 2) {
                return false;
            }

            Token lHS = tokens[0];
            Token op = tokens[1];

            if(op.type != TokenType::OPERATOR) {
                return false;
            }

            GateType opType = getOperatorType(op.value);
            switch(opType) {
            case GateType::MOVE: {
                if(tokens.size() != 3) {
                    return false;
                }
                
                Token rHS = tokens[2];
                if(rHS.type != TokenType::IDENTIFIER) {
                    return false;
                }
                
                Wire& outputWire = getWire(rHS.value);
                outputWire.setGateType(GateType::NOOP);

                if(lHS.type == TokenType::IDENTIFIER) {
                    outputWire.setSources({ &getWire(lHS.value) });
                }
                else {
                    outputWire.setSources({ AOCUtil::strtonumeric<DataType>(lHS.value.c_str()) });
                }

                break;
            }
            case GateType::AND: case GateType::OR: {
                if(tokens.size() != 5) {
                    return false;
                }

                Token rHS = tokens[2];
                Token moveOp = tokens[3];
                Token out = tokens[4];

                if(
                    (rHS.type != TokenType::IDENTIFIER && rHS.type != TokenType::LITERAL) ||
                    moveOp.type != TokenType::OPERATOR || getOperatorType(moveOp.value) != GateType::MOVE ||
                    out.type != TokenType::IDENTIFIER
                    
                ) {
                    return false;
                }
                
                Wire& outputWire = getWire(out.value);
                outputWire.setGateType(opType);

                std::variant<DataType, Wire*> lHSVal;
                std::variant<DataType, Wire*> rHSVal;
                
                if(lHS.type == TokenType::IDENTIFIER) lHSVal = &getWire(lHS.value);
                else lHSVal = AOCUtil::strtonumeric<DataType>(lHS.value.c_str());

                if(rHS.type == TokenType::IDENTIFIER) rHSVal = &getWire(rHS.value);
                else rHSVal = AOCUtil::strtonumeric<DataType>(rHS.value.c_str());
                
                outputWire.setSources({ lHSVal, rHSVal });
                
                break;
            }
            case GateType::LSHIFT: case GateType::RSHIFT: {
                if(tokens.size() != 5) {
                    return false;
                }

                Token rHS = tokens[2];
                Token moveOp = tokens[3];
                Token out = tokens[4];

                if(
                    rHS.type != TokenType::LITERAL ||
                    moveOp.type != TokenType::OPERATOR || getOperatorType(moveOp.value) != GateType::MOVE ||
                    out.type != TokenType::IDENTIFIER 
                ) {
                    return false;
                }
                
                Wire& outputWire = getWire(out.value);
                outputWire.setGateType(opType);

                std::variant<DataType, Wire*> lHSVal;
                std::variant<DataType, Wire*> rHSVal;
                
                if(lHS.type == TokenType::IDENTIFIER) lHSVal = &getWire(lHS.value);
                else lHSVal = AOCUtil::strtonumeric<DataType>(lHS.value.c_str());

                if(rHS.type == TokenType::IDENTIFIER) rHSVal = &getWire(rHS.value);
                else rHSVal = AOCUtil::strtonumeric<DataType>(rHS.value.c_str());
                
                outputWire.setSources({ lHSVal, rHSVal });
                
                break;
            }
            default: return false;
            }

            return true;
        }
        default: return false;
        }
    }


    void print() {
        for(auto& pair : _wires) {
            Wire& wire = pair.second;
            spdlog::info("{}: {}", wire.getName(), wire.getValue());
        }
    }

    void resetCaches() {
        for(auto& pair : _wires) {
            Wire& wire = pair.second;
            wire.clearCache();
        }
    }

    Wire& getWire(const std::string& name) {
        if(!_wires.contains(name)) {
            _wires[name] = Wire(name, GateType::INVALID, {});
        }

        return _wires[name];
    }
};

#endif