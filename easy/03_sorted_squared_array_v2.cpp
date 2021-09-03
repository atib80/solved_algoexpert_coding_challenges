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

vector<int> sortedSquaredArray(const vector<int>& array) {
  auto src_first = cbegin(array);
  auto src_last = --cend(array);

  vector<int> result(array.size());

  auto dst_last = end(result);

  while (src_first <= src_last) {
    if (abs(*src_first) > abs(*src_last)) {
      *--dst_last = *src_first * *src_first;
      ++src_first;
    } else {
      *--dst_last = *src_last * *src_last;
      --src_last;
    }
  }

  return result;
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
