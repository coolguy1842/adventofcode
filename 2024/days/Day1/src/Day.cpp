#include <DayInput.hpp>
#include <Day.hpp>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

inline int compare(const long* a, const long* b) {
    return *a - *b;
}

long aSolution = 0, bSolution = 0;
void Day::partA() {
    std::vector<long> leftList, rightList;
    long left, right;
    int len = 0;

    const char* str = input.text.c_str();

    while(sscanf(str += len, "%ld%*[ ]%ld\n%n", &left, &right, &len) == 2) {
        leftList.push_back(left);
        rightList.push_back(right);
    }

    std::qsort(leftList.data(), leftList.size(), sizeof(long), (__compar_fn_t)compare);
    std::qsort(rightList.data(), rightList.size(), sizeof(long), (__compar_fn_t)compare);

    long *leftPtr = leftList.data(), *rightPtr = rightList.data();
    for(size_t i = 0; i < leftList.size(); i++) {
        aSolution += std::abs(*leftPtr++ - *rightPtr++);
    }
}

void Day::partB() {
    std::vector<long> leftList;
    long left, right;
    int len = 0;

    const char* str = input.text.c_str();
    sscanf(str, "%*d%*[^0-9]%ld", &right);

    // round to nearest next power of 10 - 1 e.g 500 rounds to 999
    size_t arrSize = std::pow(10, std::ceil(std::log10(right))) - 1;
    
    // can have issues if your inputs numbers go past the stack limit, would have to swap to malloc and free or using new and delete[]
    long frequency[arrSize];
    memset(frequency, 0, arrSize * sizeof(long));

    while(sscanf(str += len, "%ld%*[ ]%ld\n%n", &left, &right, &len) == 2) {
        leftList.push_back(left);
        frequency[right]++;
    }

    long* ptr = leftList.data();
    for(size_t i = 0; i < leftList.size(); i++, ptr++) {
        bSolution += *ptr * frequency[*ptr];
    }
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}