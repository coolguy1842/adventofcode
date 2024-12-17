#include "utils/MathUtils.hpp"
#include <DayInput.hpp>
#include <Day.hpp>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <spdlog/spdlog.h>
#include <string>

Day::Day() : AOCUtil::IDay(dayInput) {}

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

enum Registers {
    A = 0,
    B,
    C
};

inline uint64_t getComboOperandValue(const uint64_t* registers, const uint8_t& operand) {
    switch(operand) {
    case '0' ... '3': return operand - '0';
    case '4' ... '6': return registers[operand - '4'];
    default: return 0;
    }
}

void runProgram(uint64_t* registers, const char* program, const size_t& programLen, char* output) {
    const char* ptr = program;

    top:
    const uint8_t& operand = ptr[2];

    switch(*ptr) {
    case ADV: registers[A] = registers[A] / quick_pow<2>(getComboOperandValue(registers, operand)); break;
    case BDV: registers[B] = registers[A] / quick_pow<2>(getComboOperandValue(registers, operand)); break;
    case CDV: registers[C] = registers[A] / quick_pow<2>(getComboOperandValue(registers, operand)); break;
    case BXL: registers[B] ^= operand - '0'; break;
    case BST: registers[B] = getComboOperandValue(registers, operand) & 0b111; break;
    case BXC: registers[B] ^= registers[C]; break;
    case OUT: *output++ = (getComboOperandValue(registers, operand) & 0b111) + '0'; *output++ = ','; break;
    case JNZ:
        if(registers[A]) {
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

    uint64_t registers[3] = { 0, 0, 0 };
    int read;

    sscanf(input.text.c_str(), "Register A: %lu\nRegister B: 0\nRegister C: 0\n\nProgram: %n", registers + A, &read);
    runProgram(registers, input.text.c_str() + read, input.text.size() - read + 1, output);

    aSolution = std::string(output);
}

uint64_t bSolution;
void Day::partB() {
    char output[256];
    int read;

    sscanf(input.text.c_str(), "Register A: %*lu\nRegister B: 0\nRegister C: 0\n\nProgram: %n", &read);

    const char* program = input.text.c_str() + read;
    const uint64_t programLen = input.text.size() - read;

    // do stuff here
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}