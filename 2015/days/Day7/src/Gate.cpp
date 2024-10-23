#include "includes.hpp"
#include <Gate.hpp>
#include <Wire.hpp>
#include <optional>
#include <variant>

DataType getValue(std::variant<DataType, Gate*, Wire*>& source, std::optional<DataType>& cacheVariable, bool useCache) {
    if(!useCache) {
        cacheVariable = std::nullopt;
    }

    if(std::holds_alternative<Wire*>(source)) {
        cacheVariable = std::get<Wire*>(source)->getValue();
        return cacheVariable.value();
    }
    else if(std::holds_alternative<Gate*>(source)) {
        cacheVariable = std::get<Gate*>(source)->getResult();
        return cacheVariable.value();
    }
    
    cacheVariable = std::get<DataType>(source);
    return cacheVariable.value();

}

DataType NothingGate::getResult(bool useCache) { return getValue(_sources[0], _cached[0], useCache); }
DataType NotGate::getResult(bool useCache) { return ~getValue(_sources[0], _cached[0], useCache); }

DataType AndGate::getResult(bool useCache) { return getValue(_sources[0], _cached[0], useCache) & getValue(_sources[1], _cached[1], useCache); }
DataType OrGate::getResult(bool useCache) { return getValue(_sources[0], _cached[0], useCache) | getValue(_sources[1], _cached[1], useCache); }

DataType LShiftGate::getResult(bool useCache) { return getValue(_sources[0], _cached[0], useCache) << getValue(_sources[1], _cached[1], useCache); }
DataType RShiftGate::getResult(bool useCache) { return getValue(_sources[0], _cached[0], useCache) >> getValue(_sources[1], _cached[1], useCache); }