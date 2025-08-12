#include <iostream>
#include <fstream>
#include <filesystem>
#include "maze_solver.h"

using std::cout, std::endl, std::string;

void MazeSolver::solve(const string &input_maze_file) {
    char maze[MAX_MAZE_LENGTH][MAX_MAZE_LENGTH];

    if(!read_file(input_maze_file, maze)) {
        cout << "Failed to read file " << input_maze_file << endl;
        return;
    }

    Stack stack;
    Data data;
    bool is_dead_end = false;

    int current[COORDINATES_COUNT] = {START_ROW,START_COL};

    do {
        //checks if the program has hit a dead end
        if (!is_dead_end) {
            // puts a hash in that spot, and checks for valid paths.
            maze[current[X]][current[Y]] = HASH;
            is_dead_end = check_for_valid_paths(stack, maze, current, data, is_dead_end);
        } else {
            /// if not runs the dead end function
            /// which pops off the top of the stack and clears the hash
            dead_end(stack, current, maze);
        }

        // passes the stack to find if there's a direction to take
        direction_to_take(stack, current, is_dead_end);

        print_maze(maze);

    } while (stack.top()->_x_value != END_ROW || stack.top()->_y_value != END_COL);

    save_maze_to_solved(maze);
}

bool MazeSolver::read_file(const string& file_name, char maze[MAX_MAZE_LENGTH][MAX_MAZE_LENGTH]) {

    if (!std::filesystem::exists(file_name)) {
        return false;
    }

    std::ifstream maze_file(file_name);

    if (maze_file.is_open()) {
        string line;
        for (int i = 0; i < MAX_MAZE_LENGTH; i++) {
            getline(maze_file, line);
            for (int j = 0; j < MAX_MAZE_LENGTH; j++) {
                maze[i][j] = line[j];
            }
        }
    }

    maze_file.close();

    return true;
}

void MazeSolver::save_maze_to_solved(const char maze[MAX_MAZE_LENGTH][MAX_MAZE_LENGTH]) {
    const string base_filename = "../solved/solved.txt";
    char file_generation = '1';
    string filename = base_filename;

    //checks if file exists
    while (std::filesystem::exists(filename)) {
        filename = base_filename;
        file_generation++;

        //if not finds the index of the . character then adds a number before it
        filename.insert(filename.begin() + filename.find('.', 3), 1, file_generation);
    }

    std::ofstream file;
    string line;
    file.open(filename);

    if (file.is_open()) {
        for (int i = 0; i < MAX_MAZE_LENGTH; ++i) {
            for (int j = 0; j < MAX_MAZE_LENGTH; ++j) {
                file << maze[i][j];
            }
            file << endl;
        }
    }

    file.close();
}

void MazeSolver::dead_end(Stack &stack, int current[COORDINATES_COUNT], char maze[MAX_MAZE_LENGTH][MAX_MAZE_LENGTH]) {
    maze[current[X]][current[Y]] = SPACE;
    stack.pop();
    current[X] = stack.top()->_x_value;
    current[Y] = stack.top()->_y_value;
}

bool MazeSolver::check_for_valid_paths(Stack &stack, char maze[MAX_MAZE_LENGTH][MAX_MAZE_LENGTH], const int current[COORDINATES_COUNT], Data &data, bool &is_dead_end) {
    is_dead_end = true;
    data._x_value = current[X];
    data._y_value = current[Y];

    // This for loop populates the possible_direction array for each node
    for (int i = 0; i < DIRECTION_LENGTH; i++) {
        // If we are at col 0 we don't try to check west
        if (current[X] == START_COL && i == W) {
            data._possible_directions[i] = OBSTACLE;
            continue;
        }

        // Adds the offsets declared in the DIRECTION array then checks that direction for and obstacle
        // The assignments of obstacle or index will be used in tandem with the Direction enum that get used later in direction_to_take function
        if (maze[current[X]+DIRECTION[i][X]][current[Y]+DIRECTION[i][Y]] == PLUS || maze[current[X]+DIRECTION[i][X]][current[Y]+DIRECTION[i][Y]] == MINUS || maze[current[X]+DIRECTION[i][X]][current[Y]+DIRECTION[i][Y]] == PIPE || maze[current[X]+DIRECTION[i][X]][current[Y]+DIRECTION[i][Y]] == HASH) {
            data._possible_directions[i] = OBSTACLE;
        }else {
            data._possible_directions[i] = i;
            is_dead_end = false;
        }
    }

    stack.push(data);

    return is_dead_end;
}

void MazeSolver::direction_to_take(const Stack &stack, int current[COORDINATES_COUNT], bool &is_dead_end) {
    //this function takes in the stack and checks the top's directions for a valid one
    for (int &cardinal_direction: stack.top()->_possible_directions) {
        if (cardinal_direction != OBSTACLE) {
            //if there is one it changes the current position to the direction it traveled to
            current[X] = stack.top()->_x_value + DIRECTION[cardinal_direction][X];
            current[Y] = stack.top()->_y_value + DIRECTION[cardinal_direction][Y];
            //then sets the direction used to an obstacle in case there's a dead end we don't try this route again
            cardinal_direction = OBSTACLE;
            // and resets the dead end flag so we can continue
            is_dead_end = false;
            return;
        }
    }
}

void MazeSolver::print_maze(const char maze[MAX_MAZE_LENGTH][MAX_MAZE_LENGTH]) {
    for (int i = 0; i < MAX_MAZE_LENGTH; i++) {
        for (int j = 0; j < MAX_MAZE_LENGTH; j++) {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

