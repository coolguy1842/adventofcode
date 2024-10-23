#ifndef __WIRE_HPP__
#define __WIRE_HPP__

#include <includes.hpp>

#include <optional>
#include <string>
#include <variant>

class Gate;
class Wire {
private:
    typedef std::variant<DataType, Gate*, Wire*> TValue;
    
    std::string _name;
    TValue _value;

    std::optional<DataType> _cached;

public:
    Wire(std::string name, TValue value) : _name(name), _value(value) {}

    std::string getName();

    DataType getValue(bool useCache = true);
    void setValue(TValue value);
};

#endif