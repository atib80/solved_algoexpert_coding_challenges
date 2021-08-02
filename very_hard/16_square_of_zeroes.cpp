#include <cmath>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

/* input matrix (n x n):

[1, 1, 1, 0, 1, 0]
[0, 0, 0, 0, 0, 1]
[0, 1, 1, 1, 0, 1]
[0, 0, 0, 1, 0, 1]
[0, 1, 1, 1, 0, 1]
[0, 0, 0, 0, 0, 1]

output: true
*/

bool check_if_square_of_zeroes_exists(
    const size_t x1,
    const size_t y1,
    const size_t N,
    const vector<set<size_t>>& row_ones_coordinates,
    const vector<set<size_t>>& col_ones_coordinates) {
  const size_t max_square_width{min(N - x1, N - y1)};
  for (size_t i{2}; i <= max_square_width; ++i) {
    auto itr1 = row_ones_coordinates[x1].upper_bound(y1);
    auto itr2 = col_ones_coordinates[y1].upper_bound(x1);

    if ((itr1 != cend(row_ones_coordinates[x1]) && *itr1 <= y1 + i - 1) ||
        (itr2 != cend(col_ones_coordinates[y1]) && *itr2 <= x1 + i - 1))
      return false;
    itr1 = row_ones_coordinates[x1 + i - 1].upper_bound(y1);
    itr2 = col_ones_coordinates[y1 + i - 1].upper_bound(x1);
    if ((itr1 == cend(row_ones_coordinates[x1 + i - 1]) ||
         *itr1 > y1 + i - 1) &&
        (itr2 == cend(col_ones_coordinates[y1 + i - 1]) || *itr2 > x1 + i - 1))
      return true;
  }

  return false;
}

bool squareOfZeroes(const vector<vector<int>>& matrix) {
  if (matrix.size() <= 1)
    return false;

  const size_t N{matrix.size()};

  vector<set<size_t>> row_ones_coordinates(N), col_ones_coordinates(N);

  for (size_t i{}; i < N; ++i) {
    for (size_t j{}; j < N; ++j) {
      if (matrix[i][j] == 1) {
        row_ones_coordinates[i].emplace(j);
        col_ones_coordinates[j].emplace(i);
      }
    }
  }

  for (size_t i{}; i < N - 1; ++i) {
    for (size_t j{}; j < N - 1; ++j) {
      if (matrix[i][j] == 0 &&
          check_if_square_of_zeroes_exists(i, j, N, row_ones_coordinates,
                                           col_ones_coordinates))
        return true;
    }
  }

  return false;
}

int main() {
  vector<vector<int>> matrix{{1, 1, 1, 0, 1, 0}, {0, 0, 0, 0, 0, 1},
                             {0, 1, 1, 1, 0, 1}, {0, 0, 0, 1, 0, 1},
                             {0, 1, 1, 1, 0, 1}, {0, 0, 0, 0, 0, 1}};

  cout << boolalpha << squareOfZeroes(matrix) << endl;

  return 0;
}
