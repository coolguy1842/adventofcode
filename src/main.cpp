#include <stdio.h>
#include <days.hpp>

#include <thirdparty/catch.hpp>
#include <thirdparty/args.hxx>

int main(int argc, char** argv) {
    args::ArgumentParser parser("Advent of Code runner.", "Usage: ./adventofcode day");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::CompletionFlag completion(parser, {"complete"});

    args::CounterFlag showTimersOption(parser, "timers", "Show timer values", {'t', "timers"});
    args::Positional<int> dayOption(parser, "day", "The day to run (1 to 25)");

    try {
        parser.ParseCLI(argc, argv);
    }
    catch (const args::Completion& e) {
        std::cout << e.what();
        return 0;
    }
    catch (const args::Help&) {
        std::cout << parser;
        return 0;
    }
    catch (const args::ParseError& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    if(!dayOption) {
        printf("%s\n", parser.Help().c_str());
        return -1;
    } 

    int dayNum = dayOption.Get();
    if(dayNum < 1 || dayNum > 25) {
        printf("Day number is out of range.\n");
        return -1;
    } 

    AOC::Day* day;
    switch (dayNum) {
    case 1: day = (AOC::Day*)new Day1(); break;    
    default: printf("Day not found.\n"); return -1;
    }

    day->runPartA();
    day->runPartB();
    
    day->printSolution();

    if(showTimersOption.Get()) {    
        day->getTimerA().print();
        day->getTimerB().print();
    }

    delete day;

    return 0;
}