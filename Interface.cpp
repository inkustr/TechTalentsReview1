#include <iostream>
#include <cmath>
#include <vector>

struct graph {
    int vertex_amount;
    int edge_amount;
    int required_power;
    std::vector<std::vector<int64_t>> adjacency_matrix;
};

// инициализация матрицы смежности
graph init_adjacency_matrix();

// умножение матриц
std::vector<std::vector<int64_t>> matrix_multiplication(const std::vector<std::vector<int64_t>>& matrix_first, const std::vector<std::vector<int64_t>>& matrix_second, int size);

// бинарное возведение матрицы в степень
std::vector<std::vector<int64_t>> matrix_binary_exponentiation(const std::vector<std::vector<int64_t>>& matrix, int size, int power);

// восстановление и вывод ответа
void write_fixed_routes_from_vertex(const graph& answer_graph);

int main() {
    std::ios_base::sync_with_stdio(false);
    const graph labyrinth = init_adjacency_matrix();
    const graph answer_graph = { labyrinth.vertex_amount, labyrinth.edge_amount, 0, matrix_binary_exponentiation(labyrinth.adjacency_matrix, labyrinth.vertex_amount, labyrinth.required_power) };
    write_fixed_routes_from_vertex(answer_graph);
    return 0;
}

