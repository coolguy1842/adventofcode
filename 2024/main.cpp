#include <CLI/CLI.hpp>
#include <Day.hpp>

#include <csignal>

int main(int argc, char** argv) {
    bool partA = false;
    bool partB = false;
    bool timer = false;
    
    CLI::App app("Advent of Code Runner", "AOCRunner");
    argv = app.ensure_utf8(argv);

    app.add_flag("-a,--parta", partA, "If the program should run part A");
    app.add_flag("-b,--partb", partB, "If the program should run part B");
    app.add_flag("-t,--timer", timer, "Display timings");

    CLI11_PARSE(app, argc, argv);
    
    Day day = Day();

    {
        bool both = !(partA ^ partB);
        partA = partA || both;
        partB = partB || both;
        
        if(partA) {
            day.timerA.start();
            day.partA();
            day.timerA.stop();
        }
        
        if(partB) {
            day.timerB.start();
            day.partB();
            day.timerB.stop();
        }
    }
    
    day.printResults(partA, partB);

    if(timer) {
        if(partA) day.timerA.print();
        if(partB) day.timerB.print();
    }
    
    return 0;
}