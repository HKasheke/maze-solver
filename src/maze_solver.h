#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H
#include <iostream>
#include "stack.h"

constexpr int MAX_MAZE_LENGTH = 51;
constexpr int COORDINATES_COUNT = 2;

constexpr char PLUS = '+';
constexpr char MINUS = '-';
constexpr char PIPE = '|';
constexpr char SPACE = ' ';
constexpr char HASH = '#';
constexpr int START_ROW = 1;
constexpr int START_COL = 0;
constexpr int X = 0;
constexpr int Y = 1;
constexpr int NORTH[] = {-1,0};
constexpr int EAST[] = {0,1};
constexpr int SOUTH[] = {1,0};
constexpr int WEST[] = {0,-1};
constexpr int DIRECTION_LENGTH = 4;
constexpr int END_ROW = 49;
constexpr int END_COL = 50;

inline const int *DIRECTION[] = {NORTH, EAST, SOUTH, WEST}; //inline to avoid multiple definitions

class MazeSolver {

    static bool read_file(const std::string& fileName, char maze[MAX_MAZE_LENGTH][MAX_MAZE_LENGTH]);
    static void dead_end(Stack &stack, int current[COORDINATES_COUNT], char maze[MAX_MAZE_LENGTH][MAX_MAZE_LENGTH]);
    static bool check_for_valid_paths(Stack &stack, char maze[MAX_MAZE_LENGTH][MAX_MAZE_LENGTH], const int current[COORDINATES_COUNT], Data &data, bool &is_dead_end);
    static void direction_to_take(const Stack &stack, int current[COORDINATES_COUNT], bool &is_dead_end);
    static void save_maze_to_solved(const char maze[MAX_MAZE_LENGTH][MAX_MAZE_LENGTH]);
    static void print_maze(const char maze[MAX_MAZE_LENGTH][MAX_MAZE_LENGTH]);

public:
    void solve(const std::string &input_maze_file);
};

#endif //MAZE_SOLVER_H
