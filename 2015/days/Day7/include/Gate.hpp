#ifndef __GATE_HPP__
#define __GATE_HPP__

#include <includes.hpp>

#include <optional>
#include <string>
#include <variant>
#include <vector>

class Wire;
class Gate {
protected:
    typedef std::variant<DataType, Gate*, Wire*> TValue;
    std::vector<TValue> _sources;

    std::vector<std::optional<DataType>> _cached;

private:
    std::string _name;

public:
    Gate(std::string name, std::vector<TValue> sources) : _sources(sources), _name(name), _cached(sources.size(), std::nullopt) {}
    virtual ~Gate() {}

    virtual DataType getResult(bool useCache = true) = 0;

    std::string getName() const { return _name; }
};

class NothingGate : public Gate {
public:
    NothingGate(TValue source) : Gate("NOTHING", { source }) {}

    DataType getResult(bool useCache = true);
};

class NotGate : public Gate {
public:
    NotGate(TValue source) : Gate("NOT", { source }) {}

    DataType getResult(bool useCache = true);
};

class AndGate : public Gate {
public:
    AndGate(TValue lHS, TValue rHS) : Gate("AND", { lHS, rHS }) {}

    DataType getResult(bool useCache = true);
};

class OrGate : public Gate {
public:
    OrGate(TValue lHS, TValue rHS) : Gate("OR", { lHS, rHS }) {}

    DataType getResult(bool useCache = true);
};

class LShiftGate : public Gate {
public:
    LShiftGate(TValue lHS, TValue rHS) : Gate("LSHIFT", { lHS, rHS }) {}

    DataType getResult(bool useCache = true);
};

class RShiftGate : public Gate {
public:
    RShiftGate(TValue lHS, TValue rHS) : Gate("RSHIFT", { lHS, rHS }) {}

    DataType getResult(bool useCache = true);
};

#endif