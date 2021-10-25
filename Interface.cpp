#include <iostream>
#include <cmath>
#include <vector>

struct Graph {
    int vertex_amount;
    int edge_amount;
    int required_power;
    std::vector<std::vector<int64_t>> adjacency_matrix;
};

// инициализация матрицы смежности
Graph adjacency_matrix_initialization();

// умножение матриц
std::vector<std::vector<int64_t>> matrix_multiplication(
    const std::vector<std::vector<int64_t>>& matrix_first,
    const std::vector<std::vector<int64_t>>& matrix_second);

// возведение матрицы в степень
std::vector<std::vector<int64_t>> matrix_exponentiation(
    const std::vector<std::vector<int64_t>>& matrix, int power);

// подсчёт матрицы, в которой хранится количество путей нужной длины
int64_t calculate_amount_of_fixed_routes(const Graph& labyrinth);

// вывод количества путей фиксированной длины из первой вершины
void write(int64_t amount_of_fixed_routes);

int main() {
    std::ios_base::sync_with_stdio(false);
    const Graph labyrinth = adjacency_matrix_initialization();
    const int64_t amount_of_fixed_routes =
        calculate_amount_of_fixed_routes(labyrinth);
    write(amount_of_fixed_routes);
    return 0;
}
