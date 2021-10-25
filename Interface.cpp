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
Graph init_adjacency_matrix();

// умножение матриц
std::vector<std::vector<int64_t>> matrix_multiplication(const std::vector<std::vector<int64_t>>& matrix_first, const std::vector<std::vector<int64_t>>& matrix_second);

// бинарное возведение матрицы в степень
std::vector<std::vector<int64_t>> matrix_binary_exponentiation(const std::vector<std::vector<int64_t>>& matrix, int power);

// подсчёт матрицы, в которой хранится количество путей нужной длины
Graph find_answer_graph(const Graph& labyrinth);

// восстановление и вывод ответа
void write_fixed_routes_from_vertex(const Graph& answer_graph);

int main() {
    std::ios_base::sync_with_stdio(false);
    const Graph labyrinth = init_adjacency_matrix();
    const Graph answer_graph = find_answer_graph(labyrinth);
    write_fixed_routes_from_vertex(answer_graph);
    return 0;
}
