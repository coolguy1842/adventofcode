#include <stdio.h>
#include <days.hpp>

#include <argparse/argparse.hpp>

#include <spdlog/spdlog.h>

int main(int argc, char** argv) {
    argparse::ArgumentParser program("Advent of Code");
    program.add_argument("day").help("the day to run").scan<'i', int>().choices(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25);
    program.add_argument("-t", "--timers").help("if performance timers should be displayed").flag();
    program.add_argument("-a", "--parta").help("if part a should run(if b is also not specified both will run)").flag();
    program.add_argument("-b", "--partb").help("if part b should run(if a is also not specified both will run)").flag();

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    int dayNum = program.get<int>("day");

    AOC::Day* day;
    switch (dayNum) {
    case 1: day = (AOC::Day*)new Day1(); break;
    default: spdlog::error("Day not found."); return -1;
    }


    bool partA = program.get<bool>("-a");
    bool partB = program.get<bool>("-b");

    bool both = (!partA && !partB) || (partA && partB); 

    if(both) {
        day->runPartA();
        day->runPartB();
    }
    else if(partA) day->runPartA();
    else day->runPartB();
    
    day->printSolution(partA || both, partB || both);

    if(program.get<bool>("--timers")) {
        day->getTimerA().print();
        day->getTimerB().print();
    }

    delete day;

    return 0;
}