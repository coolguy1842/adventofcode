#ifndef __DAY_HPP__
#define __DAY_HPP__

#include <IDay.hpp>

// stop clangd from complaining
#ifndef INPUT_PATH
#define INPUT_PATH ""
#endif

class Day : public AOCUtil::IDay {
private:

public:
    Day() : AOCUtil::IDay(INPUT_PATH) {}

    void partA() { }
    void partB() { }

    void printResults(bool partA, bool partB) {

    }
};

#endif