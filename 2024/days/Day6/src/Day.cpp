#include <DayInput.hpp>
#include <Day.hpp>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <spdlog/spdlog.h>
#include <string>

#define MAX_LOOP_STEPS 5'700

Day::Day() : AOCUtil::IDay(dayInput) {}

enum Direction {
    UP    = 1 << 0,
    RIGHT = 1 << 1,
    DOWN  = 1 << 2,
    LEFT  = 1 << 3
};

struct Guard {
    size_t pos;
    Direction dir = UP;
};

enum GridType {
    EMPTY,
    BLOCK
};

struct Grid {
    size_t width, height;
    GridType* data;

    Guard guard;

    Grid(const std::string& input) {
        const char* strPtr = input.c_str();
        width = strpbrk(strPtr, "\n") - strPtr;
        height = input.size() / width;
        
        data = (GridType*)calloc(width * height, sizeof(GridType));

        size_t pos = 0;
        for(size_t i = 0; i < input.size(); i++) {
            switch(strPtr[i]) {
            case '#': data[pos++] = GridType::BLOCK; break;
            case '^': guard.pos = pos;
            case '.': data[pos++] = GridType::EMPTY; break;
            default: break;
            }
        }
    }

    ~Grid() {
        free(data);
    }


    bool stepGuard() {
        top:
        size_t nextPos;
        switch(guard.dir) {
        case UP   : if(guard.pos <= width) return false; nextPos = guard.pos - width; break;
        case DOWN : if(guard.pos >= (width * height) - width) return false; nextPos = guard.pos + width; break;
        // if left or right, then check if the x row changed, if it did then we went out of the border
        case RIGHT: if(guard.pos / width != (guard.pos + 1) / width) return false; nextPos = guard.pos + 1; break;
        case LEFT : if(guard.pos / width != (guard.pos - 1) / width) return false; nextPos = guard.pos - 1; break;
        default: return false;
        }

        if(data[nextPos] == GridType::BLOCK) {
            if(guard.dir == Direction::LEFT) {
                guard.dir = Direction::UP;

                goto top;
            }

            guard.dir = (Direction)(guard.dir << 1);
            goto top;
        }

        guard.pos = nextPos;
        return true;
    }
};

size_t aSolution = 0;
void Day::partA() {
    Grid grid(input.text);

    bool* visited = (bool*)calloc(grid.width * grid.height, sizeof(bool));
    do {
        bool& visit = visited[grid.guard.pos];
        if(!visit) {
            visit = true;
            aSolution++;
        }
    } while(grid.stepGuard());

    free(visited);
}

size_t bSolution = 0;
void Day::partB() {
    Grid grid(input.text);
    size_t guardPos = grid.guard.pos;

    // get main path
    bool* visited = (bool*)calloc(grid.width * grid.height, sizeof(bool));
    while(grid.stepGuard()) {
        bool& visit = visited[grid.guard.pos];
        if(!visit) {
            visit = true;

            size_t prevPos = grid.guard.pos;
            Direction prevDir = grid.guard.dir;
            
            GridType& block = grid.data[prevPos], prevType = block;
            block = BLOCK;

            grid.guard.pos = guardPos;
            grid.guard.dir = UP;
            
            size_t steps = 0;
            while(grid.stepGuard()) {
                // this might need adjusting depending on input
                if(steps++ > MAX_LOOP_STEPS) {
                    bSolution++;
                    break;
                }
            }

            block = prevType;

            grid.guard.pos = prevPos;
            grid.guard.dir = prevDir;
        }
    }

    free(visited);
}

void Day::printResults(bool partA, bool partB) {
    if(partA) spdlog::info("Part A: {}", aSolution);
    if(partB) spdlog::info("Part B: {}", bSolution);
}