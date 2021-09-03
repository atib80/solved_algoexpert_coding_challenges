#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <typename ForwardIteratorType>
void print_sequence(ForwardIteratorType first,
                    ForwardIteratorType last,
                    ostream& os) {
  if (first == last) {
    os << "[ ]";
  } else {
    os << '[';
    --last;
    while (first != last) {
      os << *first << ", ";
      ++first;
    }
    os << *first << ']';
  }
}

vector<int> sortedSquaredArray(vector<int> array) {
  std::sort(begin(array), end(array),
            [](const int ln, const int rn) { return abs(ln) < abs(rn); });

  for (auto& number : array)
    number *= number;

  return array;
}

int main() {
  const auto v1{sortedSquaredArray({1, 2, 3, 5, 6, 8, 9})};
  cout << "sortedSquaredArray([1, 2, 3, 5, 6, 8, 9]) -> ";
  print_sequence(v1.cbegin(), v1.cend(),
                 cout);  // expected output: [1, 4, 9, 25, 36, 64, 81]
  cout << '\n';

  const auto v2{sortedSquaredArray({-4, -2, -1, 0, 3, 7})};
  cout << "sortedSquaredArray([-4, -2, -1, 0, 3, 7]) -> ";
  print_sequence(v2.cbegin(), v2.cend(),
                 cout);  // expected output: [0, 1, 4, 9, 16, 49]
  cout << '\n';

  const auto v3{sortedSquaredArray({-6, -3, 1, 2, 5})};
  cout << "sortedSquaredArray([-6, -3, 1, 2, 5]) -> ";
  print_sequence(v3.cbegin(), v3.cend(),
                 cout);  // expected output: [1, 4, 9, 25, 36]
  cout << '\n';

  return 0;
}
