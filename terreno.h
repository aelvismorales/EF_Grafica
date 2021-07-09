double gradient[MAX_X][MAX_Z][2];

#include <iomanip>
#include "perlin.h"

using uint = unsigned int;

template <uint rows, uint columns>
void print_matrix(double(&terrain)[rows][columns]) {
    printf("\n");
    for (auto i = 0u; i < rows; ++i) {
        for (auto j = 0u; j < columns; ++j) {
            printf("%f  ", terrain[i][j]);
        }
        printf("\n");
    }
}

template <uint rows, uint columns>
void generate_gradient_matrix(double(&grad)[rows][columns][2]) {
    static std::random_device rd;  //Will be used to obtain a seed for the random number engine
    static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    static std::uniform_real_distribution<> dis(0.0, 2.0);

    for (auto i = 0u; i < rows; ++i) {
        for (auto j = 0u; j < columns; ++j) {
            grad[i][j][0] = dis(gen);
            grad[i][j][1] = dis(gen);
        }
    }
}

template <uint rows, uint columns>
inline bool in_range(int x, int y) {
    return x > -1 && x < rows&& y > -1 && y < columns;
}

template <uint rows, uint columns>
void generate_terrain(double(&terrain)[rows][columns], uint number_of_iterations) {
    generate_gradient_matrix(gradient);
    for (auto i = 0u; i < rows; ++i) {
        for (auto j = 0u; j < columns; ++j) {
            terrain[i][j] = perlin(i * 0.135f, j * 0.135) + 0.50;
        }
    }
}

template <uint rows, uint columns>
void generate_transitions(double(&terrain)[rows][columns], std::vector<glm::vec4>& transition, glm::vec3 position,ui32 set_pos_x,ui32 set_pos_z) {
    for (auto i = 0u; i < rows; ++i) {
        for (auto j = 0u; j < columns; ++j) {
            terrain[i][j] *= 6.75;
            terrain[i][j] = std::round(terrain[i][j]);
        }
    }
    for (auto i = 0u; i < rows; ++i) {
        for (auto j = 0u; j < columns; ++j) {
            for (auto h = 0; h < terrain[i][j]; ++h) {
                transition.push_back(glm::vec4(i * 0.5f+set_pos_x*16, h / 2.0, j * 0.5f + set_pos_z * 16, h == (terrain[i][j] - 1)));
            }
        }
    }
}