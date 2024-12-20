#include "utils/MathUtils.hpp"
#include <DayInput.hpp>
#include <Day.hpp>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <limits>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

Day::Day() : AOCUtil::IDay(dayInput) {}

typedef uint64_t TRegister;
enum OPCodes {
    ADV = '0', // DIV register A by 2 to the power of the combo operand, store in register A
    BXL, // XOR register B by the literal operand, store to register B
    BST, // MOD of the combo operand by 8 and writes to register B
    JNZ, // JMP to the instruction pointer of the literal operand if A is not 0
    BXC, // XOR register B by register C and stores result in B, operand does nothing
    OUT, // PRINT the combo operand mod 8 to the console
    BDV, // DIV register A by 2 to the power of the combo operand, store in register B
    CDV  // DIV register A by 2 to the power of the combo operand, store in register C
};

inline uint64_t getComboOperandValue(const TRegister& a, const TRegister& b, const TRegister& c, const uint8_t& operand) {
    switch(operand) {
    case '0' ... '3': return operand - '0';
    case '4': return a;
    case '5': return b;
    case '6': return c;
    default: return 0;
    }
}

void runProgram(TRegister a, const char* program, const size_t& programLen, char* output) {
    TRegister b, c;
    const char* ptr = program;

    top:
    const uint8_t& operand = ptr[2];

    switch(*ptr) {
    case ADV: a = a / quick_pow<2>(getComboOperandValue(a,b,c, operand)); break;
    case BDV: b = a / quick_pow<2>(getComboOperandValue(a,b,c, operand)); break;
    case CDV: c = a / quick_pow<2>(getComboOperandValue(a,b,c, operand)); break;
    case BXC: b ^= c; break;
    case BXL: b ^= operand - '0'; break;
    case BST: b = getComboOperandValue(a,b,c, operand) & 0b111; break;
    case OUT: *output++ = (getComboOperandValue(a,b,c, operand) & 0b111) + '0'; *output++ = ','; break;
    case JNZ:
        if(a) {
            ptr = program + ((operand - '0') << 2);
            goto top;
        }

        break;
    case '\0': *(output - 1) = '\0'; return;
    default: break;
    }

    ptr += 4;
    goto top;
}

std::string aSolution = "";
void Day::partA() {
    char output[256];

    TRegister a;
    int read;

    sscanf(input.text.c_str(), "Register A: %lu\nRegister B: 0\nRegister C: 0\n\nProgram: %n", &a, &read);
    runProgram(a, input.text.c_str() + read, input.text.size() - read + 1, output);

    aSolution = std::string(output);
}

uint64_t bSolution;
void Day::partB() {
    int read;

    sscanf(input.text.c_str(), "Register A: %*lu\nRegister B: 0\nRegister C: 0\n\nProgram: %n", &read);

    const char* program = input.text.c_str() + read;
    const uint64_t programLen = input.text.size() - read;

    std::vector<uint64_t> candidates = { 0 };
    for(uint64_t digit = 0; digit <= programLen >> 1; digit++) {
        const char& findDigit = program[(programLen - 1) - (digit << 1)];
        std::vector<uint64_t> nextCandidates;

        for(const uint64_t& candidate : candidates) {
            uint64_t a = candidate << 3;

            do {
                TRegister aReg = a, b, c;
                const char* ptr = program;

                top:
                const uint8_t& operand = ptr[2];

                switch(*ptr) {
                case ADV: aReg = aReg / quick_pow<2>(getComboOperandValue(aReg,b,c, operand)); break;
                case BDV: b = aReg / quick_pow<2>(getComboOperandValue(aReg,b,c, operand)); break;
                case CDV: c = aReg / quick_pow<2>(getComboOperandValue(aReg,b,c, operand)); break;
                case BXC: b ^= c; break;
                case BXL: b ^= operand - '0'; break;
                case BST: b = getComboOperandValue(aReg,b,c, operand) & 0b111; break;
                case OUT:
                    if((getComboOperandValue(aReg,b,c, operand) & 0b111) + '0' == findDigit) {
                        nextCandidates.push_back(a);
                    }

                    continue;
                case JNZ:
                    if(aReg) {
                        ptr = program + ((operand - '0') << 2);
                        goto top;
                    }

                    break;
                case '\0': continue;
                default: break;
                }

                ptr += 4;
                goto top;
            } while((++a & 0b111) != 0b111);
        }

        candidates = nextCandidates;
    }

    uint64_t res = std::numeric_limits<uint64_t>::max();
    for(const uint64_t& candidate : candidates) {
        res = std::min(candidate, res);
    }

    bSolution = res;
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}