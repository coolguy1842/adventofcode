#include <CLI/CLI.hpp>
#include <Days.hpp>
#include <spdlog/spdlog.h>

namespace {
std::string dayValidator(const std::string& str) {
    const char* buf = str.c_str();
    char* end       = nullptr;

    unsigned long day = std::strtoul(buf, &end, 10);
    if(end == nullptr || static_cast<size_t>(end - buf) != str.size() || day <= 0 || day > days.size()) {
        throw CLI::ValidationError("Invalid Day");
    }

    return "";
}

std::string partValidator(const std::string& str) {
    if(str.size() != 1) {
        throw CLI::ValidationError("Invalid Part");
    }

    switch(tolower(str[0])) {
    case '1':
    case 'a':
    case '2':
    case 'b': return "";
    default:  throw CLI::ValidationError("Invalid Part");
    }
}
}; // namespace

int main(int argc, char** argv) {
    if(days.empty()) {
        spdlog::error("No days to run");

        return 1;
    }

    CLI::App app("Advent of Code Runner");

    uint8_t dayNum = 0;
    app.add_option("-d,--day", dayNum, "Day from 1 to 12")->required()->check(dayValidator);

    char part = '\0';
    app.add_option("-p,--part", part, "Part, A(1) or B(2), not specifying will run both")->check(partValidator);

    bool showTimes = false;
    app.add_flag("-t,--time", showTimes, "Show timings")->default_val(false);

    CLI11_PARSE(app, argc, app.ensure_utf8(argv));

    // daynum is validated in dayValidator so this is fine
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
    const auto& day = days[dayNum - 1];

    std::bitset<2> parts;
    switch(tolower(part)) {
    case 'a':
    case '1': parts.set(IDay::A); break;
    case 'b':
    case '2': parts.set(IDay::B); break;
    default:  parts.flip(); break;
    }

    spdlog::info("Running Day {}", dayNum);
    day->runParts(parts);
    day->printSolutions(parts);

    if(showTimes) {
        puts("");
        spdlog::info("Timers");

        if(parts.test(IDay::A)) {
            std::chrono::microseconds microseconds = std::chrono::duration_cast<std::chrono::microseconds>(day->partATimer().offset());
            spdlog::info("Part A took {:03f}ms", static_cast<float>(microseconds.count()) / 1000.0f);
        }

        if(parts.test(IDay::B)) {
            std::chrono::microseconds microseconds = std::chrono::duration_cast<std::chrono::microseconds>(day->partBTimer().offset());
            spdlog::info("Part B took {:03f}ms", static_cast<float>(microseconds.count()) / 1000.0f);
        }
    }

    return 0;
}