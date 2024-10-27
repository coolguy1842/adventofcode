#ifndef __DAY_HPP__
#define __DAY_HPP__

#include "Circuit.hpp"
#include <Includes.hpp>
#include <IDay.hpp>

#include <scn/scan.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <optional>

#include <Wire.hpp>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

class Day : public AOCUtil::IDay {
private:
    std::optional<DataType> aWireValue;
    std::optional<DataType> bWireValue;

    Circuit loadCircuit() {
        Circuit circuit;

        for(std::string& line : input.getSplitText("\n")) {
            if(!circuit.runLine(line)) {
                spdlog::info("Circuit Failed Running Line: {}", line);
            }
        }

        return circuit;
    }

public:
    Day() : AOCUtil::IDay(INPUT_PATH), aWireValue(std::nullopt) {}

    void partA() {
        Circuit circuit = loadCircuit();
        aWireValue = circuit.getWire("a").getValue();

    }

    void partB() {
        Circuit circuit = loadCircuit();

        DataType bValue;
        if(aWireValue.has_value()) {
            bValue = aWireValue.value();
        }
        else {
            bValue = circuit.getWire("a").getValue();
        }

        Wire& wire = circuit.getWire("b");
        wire.setGateType(GateType::NOOP);
        wire.setSources({ bValue });

        circuit.resetCaches();
        bWireValue = circuit.getWire("a").getValue();
    }
    

    void printResults(bool partA, bool partB) {
        if(partA) {
            if(aWireValue.has_value()) {
                spdlog::info("Part A: {}", aWireValue.value());
            }
            else {
                spdlog::info("Part A: Invalid Input");
            }
        }

        if(partB) {
            if(bWireValue.has_value()) {
                spdlog::info("Part B: {}", bWireValue.value());
            }
            else {
                spdlog::info("Part B: Invalid Input");
            }
        }
    }
};

#endif