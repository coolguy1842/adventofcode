#include <stdio.h>
#include <days.hpp>

#include <CLI/CLI.hpp>

int main(int argc, char** argv) {
    CLI::App app;
    
    bool showTimers = false, partA = false, partB = false;
    
    app.add_flag("-t,--timers", showTimers, "Should the timers be visible?");

    app.add_flag("-a,--parta", partA, "Should part a be run?");
    app.add_flag("-b,--partb", partB, "Should part b be run?");

    int dayNum;
    app.add_option("day", dayNum)->required();

    CLI11_PARSE(app, argc, argv);

    AOC::Day* day;
    switch (dayNum) {
    case 1: day = (AOC::Day*)new Day1(); break;
    case 2: day = (AOC::Day*)new Day2(); break;
    case 3: day = (AOC::Day*)new Day3(); break;
    case 4: day = (AOC::Day*)new Day4(); break;
    case 5: day = (AOC::Day*)new Day5(); break;
    case 6: day = (AOC::Day*)new Day6(); break;
    case 7: day = (AOC::Day*)new Day7(); break;
    default: fprintf(stderr, "Day not found.\n"); return -1;
    }


    bool both = (!partA && !partB) || (partA && partB); 

    partA = partA || both;
    partB = partB || both;

    if(partA) day->runPartA();
    if(partB) day->runPartB();
    
    day->printSolution(partA, partB);

    if(showTimers) {
        if(partA) day->getTimerA().print();
        if(partB) day->getTimerB().print();
    }

    delete day;

    return 0;
}