#ifndef __WIRE_HPP__
#define __WIRE_HPP__

#include <spdlog/spdlog.h>
#include <utils/Range.hpp>
#include <Includes.hpp>

#include <string>
#include <variant>
#include <vector>

enum GateType {
    NOOP,
    NOT,
    
    AND,
    OR,

    LSHIFT,
    RSHIFT,

    // for ->
    MOVE,
    // for unmatched
    INVALID
};

class Wire {
private:
    typedef std::variant<DataType, Wire*> TSource;

    std::string _name;
    DataType _cachedValue;

    GateType _gateType;
    std::vector<TSource> _sources;

    DataType& getSourceValue(int index, bool useCache = true) {
        TSource& source = _sources[index];
        if(std::holds_alternative<Wire*>(source)) {
            return (std::get<Wire*>(source))->getValue(useCache);
        }
        else {
            return std::get<DataType>(source);
        }
    }

    DataType _getValue(bool useCache) {
        size_t requiredSources = 0;
        switch(_gateType) {
        case GateType::NOOP: case GateType::NOT:
            requiredSources = 1;
            break;
        case GateType::AND: case GateType::OR: case GateType::LSHIFT: case GateType::RSHIFT:
            requiredSources = 2;
            break;
        default: return 0;
        }

        if(_sources.size() != requiredSources) {
            return 0;
        }
        
        DataType lHS = getSourceValue(0, useCache);
        DataType rHS = _sources.size() > 1 ? getSourceValue(1, useCache) : 0;
        DataType out = 0;
            
        switch(_gateType) {
        case GateType::NOOP: out = lHS; spdlog::debug("{}: {} = {}", _name, lHS, out); break;
        case GateType::NOT: out = ~lHS; spdlog::debug("{}: ~{} = {}", _name, lHS, out); break;

        case GateType::AND: out = lHS & rHS; spdlog::debug("{}: {} & {} = {}", _name, lHS, rHS, out); break;
        case GateType::OR: out = lHS | rHS; spdlog::debug("{}: {} | {} = {}", _name, lHS, rHS, out); break;

        case GateType::LSHIFT: out = lHS << rHS; spdlog::debug("{}: {} << {} = {}", _name, lHS, rHS, out); break;
        case GateType::RSHIFT: out = lHS >> rHS; spdlog::debug("{}: {} >> {} = {}", _name, lHS, rHS, out); break;

        default: return 0;
        }

        return out;
    }

public:
    Wire() : _name(""), _cachedValue(0), _gateType(GateType::NOOP), _sources({}) {}
    Wire(std::string name, GateType gateType, std::vector<TSource> sources) : _name(name), _cachedValue(0), _gateType(gateType), _sources(sources) {}
    
    void setName(std::string name) { _name = name; }
    std::string getName() const { return _name; }


    void clearCache() {
        _cachedValue = 0;
    }

    void setGateType(GateType type) {
        _gateType = type;
        _cachedValue = 0;
    }

    void setSources(std::vector<TSource> sources) {
        _sources = sources;
        _cachedValue = 0;
    }

    DataType& getValue(bool useCache = true) {
        if(!useCache) {
            _cachedValue = 0;
        }
        else if(_cachedValue != 0) {
            return _cachedValue;
        }

        _cachedValue = _getValue(useCache);
        return _cachedValue;
    }
};

#endif