#include <IDay.hpp>

#include <ios>
#include <fstream>
#include <sstream>

std::string AOCUtil::IDay::readInput(std::string path) {
    std::ifstream fstream(path, std::ios_base::binary);
    std::stringstream stream;

    stream << fstream.rdbuf();

    return stream.str();
}