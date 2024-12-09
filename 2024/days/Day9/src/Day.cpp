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

void printDiskMap(const std::vector<FileInfo>& diskMap) {
    for(const FileInfo& info : diskMap) {
        for(unsigned char i = 0; i < info.blocks; i++) {
            if(info.id != -1) {
                printf("%zu", info.id);
            }
            else {
                printf(".");
            }
        }
    }

    printf("\n");
}

size_t aSolution = 0;
void Day::partA() {
    std::vector<int64_t> info;

    int64_t id = 0;
    bool isFile = true;
    for(const char& c : input.text) {
        unsigned char blocks =  c - '0';
        int64_t insert = isFile ? id++ : -1;
        
        for(unsigned char i = 0; i < blocks; i++) {
            info.push_back(insert);
        }
        
        isFile = !isFile;
    }

    for(long i = info.size() - 1; i >= 0; i--) {
        int64_t& cur = info[i];
        if(cur == -1) {
            continue;
        }

        for(size_t j = 0; j <= info.size(); j++) {
            int64_t& check = info[j];
            if(check != -1) {
                continue;
            }

            std::swap(info[i], info[j]);
            break;
        }
    }

    info.erase(info.begin());
    info.push_back(-1);

    for(size_t i = 0; i < info.size(); i++) {
        int64_t& id = info[i];
        if(id == -1) continue;

        aSolution += id * i;
    }
}

size_t bSolution = 0;
void Day::partB() {
    std::vector<FileInfo> diskMap;

    int64_t id = 0;
    bool isFile = true;
    for(const char& c : input.text) {
        unsigned char blocks =  c - '0';
        diskMap.push_back({ isFile ? id++ : -1, blocks });
        
        isFile = !isFile;
    }

    for(int64_t i = diskMap.size() - 1; i >= 0; i--) {
        const FileInfo& info = diskMap[i];
        if(info.id == -1) {
            continue;
        }

        for(size_t j = 0; j < i; j++) {
            FileInfo& space = diskMap[j];
            if(space.id != -1 || space.blocks < info.blocks) {
                continue;
            }

            if(space.blocks == info.blocks) {
                std::swap(diskMap[i], diskMap[j]);
            }
            else {
                unsigned char blocksLeft = space.blocks - info.blocks;
                space.blocks = info.blocks;

                std::swap(diskMap[i], diskMap[j]);
                
                if(blocksLeft > 0) {
                    diskMap.insert(diskMap.begin() + j + 1, { -1, blocksLeft });
                }
            }

            break;
        }
    }

    size_t block = 0;
    for(size_t i = 0; i < diskMap.size(); i++) {
        FileInfo& info = diskMap[i];
        if(info.id == -1) {
            block += info.blocks;
            continue;
        }

        for(unsigned char i = 0; i < info.blocks; i++) {
            bSolution += info.id * block++;
        }
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}