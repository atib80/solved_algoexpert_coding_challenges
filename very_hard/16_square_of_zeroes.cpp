#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

/* input matrix (N x N):

[1, 1, 1, 0, 1, 0]
[0, 0, 0, 0, 0, 1]
[0, 1, 1, 1, 0, 1]
[0, 0, 0, 1, 0, 1]
[0, 1, 1, 1, 0, 1]
[0, 0, 0, 0, 0, 1]

output: true

asymptotic time complexity: O(N^3 * lgN)
asymptotic space complexity: O(1)
*/

bool check_if_matrix_column_consists_of_zeroes(
    const vector<vector<int>>& matrix,
    const size_t x,
    const size_t y,
    const size_t max_height_to_check) {
  for (size_t low{x},
       high{std::min(x + max_height_to_check, matrix.size()) - 1};
       low <= high;) {
    const size_t middle{(low + high) / 2};
    if (0 != matrix[middle][y])
      return false;

    low = middle + 1;
  }

  return true;
}

bool check_if_square_of_zeroes_exists(const vector<vector<int>>& matrix,
                                      const size_t x1,
                                      const size_t y1,
                                      const size_t N) {
  const size_t max_square_width{min(N - x1, N - y1)};
  for (size_t i{2}; i <= max_square_width; ++i) {
    auto itr1 =
        upper_bound(cbegin(matrix[x1]) + y1, cbegin(matrix[x1]) + y1 + i, 0);

    if ((itr1 != (cbegin(matrix[x1]) + y1 + i)) ||
        !check_if_matrix_column_consists_of_zeroes(matrix, x1, y1, i))
      return false;
    itr1 = upper_bound(cbegin(matrix[x1 + i - 1]) + y1,
                       cbegin(matrix[x1 + i - 1]) + y1 + i, 0);
    if (itr1 == (cbegin(matrix[x1 + i - 1]) + y1 + i) &&
        check_if_matrix_column_consists_of_zeroes(matrix, x1, y1 + i - 1, i))
      return true;
  }

  return false;
}

bool squareOfZeroes(const vector<vector<int>>& matrix) {
  if (matrix.size() <= 1)
    return false;

  const size_t N{matrix.size()};

  for (size_t i{}; i < N - 1; ++i) {
    for (size_t j{}; j < N - 1; ++j) {
      if (matrix[i][j] == 0 &&
          check_if_square_of_zeroes_exists(matrix, i, j, N))
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
