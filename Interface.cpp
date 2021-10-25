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
int64_t find_answer(const Graph& labyrinth);

// вывод ответа
void write(int answer);

int main() {
    std::ios_base::sync_with_stdio(false);
    const Graph labyrinth = init_adjacency_matrix();
    int64_t answer = find_answer(labyrinth);
    write(answer);
    return 0;
}

