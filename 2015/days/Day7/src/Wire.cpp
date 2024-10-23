#include <Wire.hpp>
#include <Gate.hpp>
#include <optional>
#include <spdlog/spdlog.h>

std::string Wire::getName() { return _name; }

DataType Wire::getValue(bool useCache) {
    if(!useCache) {
        _cached = std::nullopt;
    }

    if(std::holds_alternative<Gate*>(_value)) {
        _cached = std::get<Gate*>(_value)->getResult();
        return _cached.value();
    }
    else if(std::holds_alternative<Wire*>(_value)) {
        _cached = std::get<Wire*>(_value)->getValue();
        return _cached.value();
    }

    _cached = std::get<DataType>(_value);
    return _cached.value();
}

void Wire::setValue(TValue value) {
    _value = value;
    _cached = std::nullopt;
}