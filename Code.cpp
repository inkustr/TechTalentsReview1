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
Graph adjacency_matrix_initialization(std::istream& in) {
  Graph labyrinth;
  in >> labyrinth.vertex_amount >> labyrinth.edge_amount >>
      labyrinth.required_power;
  labyrinth.adjacency_matrix.resize(labyrinth.vertex_amount);
  for (int i = 0; i < labyrinth.vertex_amount; ++i) {
    labyrinth.adjacency_matrix[i].resize(labyrinth.vertex_amount);
    for (int j = 0; j < labyrinth.vertex_amount; ++j) {
      labyrinth.adjacency_matrix[i][j] = 0;
    }
  }
  for (int i = 0; i < labyrinth.edge_amount; ++i) {
    int start, finish;
    in >> start >> finish;
    start--;
    finish--;
    labyrinth.adjacency_matrix[start][finish]++;
  }
  return labyrinth;
}

// умножение матриц
std::vector<std::vector<int64_t>> matrix_multiplication(
    const std::vector<std::vector<int64_t>>& matrix_first,
    const std::vector<std::vector<int64_t>>& matrix_second) {
  std::vector<std::vector<int64_t>> matrix_result(
      matrix_first.size(), std::vector<int64_t>(matrix_first.size(), 0));
  for (int i = 0; i < matrix_first.size(); ++i) {
    for (int j = 0; j < matrix_first.size(); ++j) {
      for (int k = 0; k < matrix_first.size(); k++)
        matrix_result[i][j] =
            (matrix_result[i][j] + matrix_first[i][k] * matrix_second[k][j]) %
            (1000000007);
    }
  }
  return matrix_result;
}

// бинарное возведение матрицы в степень
std::vector<std::vector<int64_t>> matrix_exponentiation(
    const std::vector<std::vector<int64_t>>& matrix, int power) {
  std::vector<std::vector<int64_t>> matrix_copy = matrix;
  std::vector<std::vector<int64_t>> res(matrix.size(),
                                        std::vector<int64_t>(matrix.size(), 0));
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix.size(); ++j) res[i][i] = 1;
  }
  while (power > 0) {
    if (power % 2 == 1) {
      res = matrix_multiplication(res, matrix_copy);
      power--;
    }
    matrix_copy = matrix_multiplication(matrix_copy, matrix_copy);
    power /= 2;
  }
  return res;
}

// подсчёт матрицы, в которой хранится количество путей нужной длины
int64_t calculate_amount_of_fixed_routes(const Graph& labyrinth) {
  Graph answer_graph;
  answer_graph.vertex_amount = labyrinth.vertex_amount;
  answer_graph.edge_amount = labyrinth.edge_amount;
  answer_graph.required_power = 0;
  answer_graph.adjacency_matrix = matrix_exponentiation(
      labyrinth.adjacency_matrix, labyrinth.required_power);
  int64_t sum = 0;
  for (int i = 0; i < answer_graph.vertex_amount; ++i)
    sum = (sum + answer_graph.adjacency_matrix[0][i]) % (1000000007);
  return sum;
}

// вывод количества путей фиксированной длины из первой вершины
void write(std::ostream& out, int64_t amount_of_fixed_routes) {
  out << amount_of_fixed_routes;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  const Graph labyrinth = adjacency_matrix_initialization(std::cin);
  const int64_t amount_of_fixed_routes =
      calculate_amount_of_fixed_routes(labyrinth);
  write(std::cout, amount_of_fixed_routes);
  return 0;
}
