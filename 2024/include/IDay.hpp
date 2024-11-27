#ifndef __IDAY_HPP__
#define __IDAY_HPP__

#include <Input.hpp>
#include <Timer.hpp>

#include <string>

namespace AOCUtil {

class IDay {
private:
    std::string readInput(std::string path);

protected:
    Input input;

public:
    Timer timerA;
    Timer timerB;
    
    IDay(std::string inputPath) : input(Input(readInput(inputPath))), timerA("A"), timerB("B") {}
    IDay(Input input) : input(input), timerA("A"), timerB("B") {}
    
    virtual ~IDay() = default;

    virtual void partA() = 0;
    virtual void partB() = 0;

    virtual void printResults(bool partA, bool partB) = 0;
};

}

#endif