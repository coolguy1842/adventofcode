#include <CLI/CLI.hpp>
#include <Day.hpp>

int main(int argc, char** argv) {
    CLI::App app("Advent of Code Runner", "AOCRunner");
    argv = app.ensure_utf8(argv);

    bool partA = false;
    bool partB = false;
    bool timer = false;
    
    app.add_flag("-a,--parta", partA, "If the program should run part A");
    app.add_flag("-b,--partb", partB, "If the program should run part B");
    app.add_flag("-t,--timer", timer, "Display timings");

    CLI11_PARSE(app, argc, argv);
    
    Day day = Day();
    day.timer.start();

    if(!(partA ^ partB)) {
        day.partA();
        day.partB();
    }
    else if(partA) {
        day.partA();
    }
    else {
        day.partB();
    }

    day.timer.stop();
    day.printResults(partA, partB);

    if(timer) {
        day.timer.print();
    }
    
    return 0;
}