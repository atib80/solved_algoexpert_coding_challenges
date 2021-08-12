#include <iostream>
#include <queue>
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
*/

struct travelled_square {
  const size_t right_x;
  const size_t right_y;
  const size_t down_x;
  const size_t down_y;
  const bool is_dir_outbound;

  travelled_square(const size_t right_x,
                   const size_t right_y,
                   const size_t down_x,
                   const size_t down_y,
                   const bool is_dir_outbound) noexcept
      : right_x{right_x},
        right_y{right_y},
        down_x{down_x},
        down_y{down_y},
        is_dir_outbound{is_dir_outbound} { }

  bool check_if_two_points_are_equal() const noexcept {
    return right_x == down_x && right_y == down_y;
  }
};

bool squareOfZeroes(const vector<vector<int>>& matrix) {
  if (matrix.size() <= 1)
    return false;

  const size_t N{matrix.size()};

  for (size_t i{}; i < N - 1; ++i) {
    for (size_t j{}; j < N - 1; ++j) {
      if (matrix[i][j] == 0 && matrix[i][j + 1] == 0 && matrix[i + 1][j] == 0) {
        queue<travelled_square> q{};
        q.emplace(i, j + 1, i + 1, j, true);

        while (!q.empty()) {
          const travelled_square points{(q.front())};
          q.pop();

          if (points.check_if_two_points_are_equal())
            return true;

          if (points.is_dir_outbound) {
            if (points.right_y + 1 < N &&
                matrix[points.right_x][points.right_y + 1] == 0 &&
                points.down_x + 1 < N &&
                matrix[points.down_x + 1][points.down_y] == 0) {
              q.emplace(points.right_x, points.right_y + 1, points.down_x + 1,
                        points.down_y, true);
            }

            if (points.right_x + 1 < N &&
                matrix[points.right_x + 1][points.right_y] == 0 &&
                points.down_y + 1 < N &&
                matrix[points.down_x][points.down_y + 1] == 0) {
              q.emplace(points.right_x + 1, points.right_y, points.down_x,
                        points.down_y + 1, false);
            }

          } else if (points.right_x + 1 < N &&
                     matrix[points.right_x + 1][points.right_y] == 0 &&
                     points.down_y + 1 < N &&
                     matrix[points.down_x][points.down_y + 1] == 0) {
            q.emplace(points.right_x + 1, points.right_y, points.down_x,
                      points.down_y + 1, false);
          }
        }
      }
    }
  }

  return false;
}

int main() {
  vector<vector<int>> matrix{{1, 1, 1, 0, 1, 0},
                             {0, 0, 0, 0, 0, 1},
                             {0, 1, 1, 1, 0, 1},
                             {0, 0, 0, 1, 0, 1},
                             {0, 1, 1, 1, 0, 1},
                             {0, 0, 0, 0, 0, 1}};

  cout << boolalpha << squareOfZeroes(matrix) << endl;

  return 0;
}
