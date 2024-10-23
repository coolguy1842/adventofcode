#ifndef __DAY_HPP__
#define __DAY_HPP__

#include "Interpreter.hpp"
#include "includes.hpp"
#include <optional>
#include <scn/scan.h>
#include <IDay.hpp>

#include <Gate.hpp>
#include <Wire.hpp>

#include <Lexer.hpp>

#include <spdlog/spdlog.h>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

class Day : public AOCUtil::IDay {
private:
    std::optional<DataType> aWireValue;

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aWireValue(std::nullopt) {}

    void partA() {
        Lexer lexer;
        Interpreter interpreter;

        for(std::string& line : input.getSplitText("\n")) {
            std::optional<std::vector<Token>> tokensOpt = lexer.analyse(line);
            if(!tokensOpt.has_value()) {
                spdlog::info("Invalid Line: {}", line);
                continue;
            }

            std::vector<Token> tokens = tokensOpt.value();
            if(!interpreter.run(tokens)) {
                spdlog::info("Interpreter failed running line: {}", line);
            }
        }

        interpreter.print();

        std::optional<Wire*> wire = interpreter.getWire("a");
        if(wire.has_value()) {
            aWireValue = wire.value()->getValue();
        }
    }

    void partB() { }
    

    void printResults(bool partA, bool partB) {
        if(partA) {
            if(aWireValue.has_value()) {
                spdlog::info("Part A: {}", aWireValue.value());
            }
            else {
                spdlog::info("Part A: Invalid Input");
            }
        }
    }
};

#endif