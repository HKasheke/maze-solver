#include "maze_solver.h"

int main(const int argc, char *argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Invalid input missing <maze_file>" << std::endl;
            return 1;
        }

        const std::string maze_file = argv[1];

        MazeSolver solver;
        solver.solve(maze_file);
    }catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}