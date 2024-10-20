#ifndef __IDAY_HPP__
#define __IDAY_HPP__

#include <Input.hpp>
#include <Timer.hpp>

#include <string>

namespace AOCUtil {

class IDay {
protected:
    Input input;

private:
    std::string readInput(std::string path);

public:
    Timer timer;
    
    IDay() : input(Input(readInput(INPUT_PATH))) {}
    virtual ~IDay() = default;

    virtual void partA() = 0;
    virtual void partB() = 0;

    virtual void printResults(bool partA, bool partB) = 0;
};

}

#endif