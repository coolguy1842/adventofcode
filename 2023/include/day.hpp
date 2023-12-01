#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <stdio.h>
#include <util/stringUtil.hpp>

#include <timer.hpp>

namespace AOC {

class Day {
protected:
    std::vector<std::string> input;

    AOC::Timer partATimer = Timer("partA");
    AOC::Timer partBTimer = Timer("partB");

private:
    void readInput(std::string path) {
        std::ifstream file(path);
        std::stringstream sstream;

        sstream << file.rdbuf();
        input = split(sstream.str(), "\n");
    }

public:
    Day(std::string inputPath) {
        this->readInput(inputPath);
    }

    virtual ~Day() {}

    virtual void partA() {};
    virtual void partB() {};

    virtual void printSolution(bool partA, bool partB) {};

    void runPartA() {
        partATimer.start();
        partA();
        partATimer.stop();
    }
    
    void runPartB() {
        partBTimer.start();
        partB();
        partBTimer.stop();
    }

    AOC::Timer getTimerA() { return partATimer; }
    AOC::Timer getTimerB() { return partBTimer; }
};

}

#endif