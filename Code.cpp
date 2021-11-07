#include <iostream>
#include <cmath>
#include <vector>

const int MODULUS = 1000000007;
const int INDEXING_SHIFT = 1;

struct Graph {
    int vertex_amount;
    int edge_amount;
    int required_power;
    std::vector<std::vector<int64_t> > adjacency_matrix;
};

// инициализация матрицы смежности
Graph adjacency_matrix_initialization(std::istream& in)
{
    Graph labyrinth;
    in >> labyrinth.vertex_amount >> labyrinth.edge_amount
       >> labyrinth.required_power;
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
        start = start - INDEXING_SHIFT;
        finish = finish - INDEXING_SHIFT;
        labyrinth.adjacency_matrix[start][finish]++;
    }
    return labyrinth;
}

// умножение матриц
std::vector<std::vector<int64_t> > matrix_multiplication(
    const std::vector<std::vector<int64_t> >& matrix_first,
    const std::vector<std::vector<int64_t> >& matrix_second)
{
    if (matrix_first.size() < 1 || matrix_second.size() < 1 ||
        matrix_first[0].size() != matrix_second.size()) {
        throw std::invalid_argument(
            "The dimensions of the matrices are not suitable.");
    }
    std::vector<std::vector<int64_t> > matrix_result(
        matrix_first.size(), std::vector<int64_t>(matrix_second[0].size(), 0));
    for (int i = 0; i < matrix_first.size(); ++i) {
        for (int j = 0; j < matrix_second[0].size(); ++j) {
            for (int k = 0; k < matrix_first[0].size(); ++k)
                matrix_result[i][j] = (matrix_result[i][j] + matrix_first[i][k]
                    * matrix_second[k][j]) % MODULUS;
        }
    }
    return matrix_result;
}

// бинарное возведение матрицы в степень
std::vector<std::vector<int64_t> > matrix_exponentiation(
    const std::vector<std::vector<int64_t> >& matrix, int power)
{
    std::vector<std::vector<int64_t> > matrix_copy = matrix;
    std::vector<std::vector<int64_t> > res(matrix.size(),
        std::vector<int64_t>(matrix.size(), 0));
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.size(); ++j)
            res[i][i] = 1;
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
int64_t calculate_amount_of_fixed_routes(const Graph& labyrinth)
{
    std::vector<std::vector<int64_t> > answer_graph = matrix_exponentiation(
        labyrinth.adjacency_matrix, labyrinth.required_power);
    int64_t sum = 0;
    for (int i = 0; i < answer_graph.size(); ++i) {
        sum = (sum + answer_graph[0][i]) % MODULUS;
    }
    return sum;
}

// вывод количества путей фиксированной длины из первой вершины
void write(std::ostream& out, int64_t amount_of_fixed_routes)
{
    out << amount_of_fixed_routes;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    const Graph labyrinth = adjacency_matrix_initialization(std::cin);
    const int64_t amount_of_fixed_routes =
        calculate_amount_of_fixed_routes(labyrinth);
    write(std::cout, amount_of_fixed_routes);
    return 0;
}
