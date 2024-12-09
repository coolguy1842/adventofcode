#include <DayInput.hpp>
#include <Day.hpp>
#include <cstdint>
#include <spdlog/spdlog.h>
#include <utility>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

struct FileInfo {
    int64_t id = 0;
    unsigned char blocks;
};

size_t partFunc(const std::string& diskMapStr, const bool& partA) {
    std::vector<FileInfo> diskMap;

    int64_t id = 0;
    bool isFile = true;
    for(const char& c : diskMapStr) {
        unsigned char blocks =  c - '0';
        diskMap.push_back({ isFile ? id++ : -1, blocks });
        
        isFile = !isFile;
    }

    for(int64_t i = diskMap.size() - 1; i >= 0; i--) {
        FileInfo& info = diskMap[i];
        if(info.id == -1) {
            continue;
        }

        for(size_t j = 0; j < i; j++) {
            FileInfo& space = diskMap[j];
            if(space.id != -1 || (!partA && space.blocks < info.blocks)) {
                continue;
            }

            if(space.blocks == info.blocks) {
                std::swap(info, space);
            }
            else if(space.blocks > info.blocks) {
                unsigned char blocksLeft = space.blocks - info.blocks;
                space.blocks = info.blocks;

                std::swap(info, space);

                diskMap.insert(diskMap.begin() + j + 1, { -1, blocksLeft });
            }
            else if(partA) {
                unsigned char blocksLeft = info.blocks - space.blocks;
                info.blocks = space.blocks;

                std::swap(info, space);
                
                // info reference was swapped to space, so use space for the id
                diskMap.insert(diskMap.begin() + i, { space.id, blocksLeft });
                i++;
            }

            break;
        }
    }

    size_t block = 0, out = 0;
    for(size_t i = 0; i < diskMap.size(); i++) {
        FileInfo& info = diskMap[i];
        if(info.id == -1) {
            block += info.blocks;
            continue;
        }

        for(unsigned char i = 0; i < info.blocks; i++) {
            out += info.id * block++;
        }
    }

    return out;
}

size_t aSolution = 0, bSolution = 0;
void Day::partA() { aSolution = partFunc(input.text, true ); }
void Day::partB() { bSolution = partFunc(input.text, false); }

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}