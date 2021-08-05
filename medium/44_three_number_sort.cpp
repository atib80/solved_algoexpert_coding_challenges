#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <typename ForwardIterType>
void print_elements(ForwardIterType first,
                    ForwardIterType last,
                    std::ostream& os) {
  if (first == last) {
    os << "[]";

  } else {
    os << '[';

    --last;

    for (; first != last; ++first) {
      os << *first << ',';
    }

    os << *last << ']';
  }
}

vector<int> threeNumberSort(vector<int> array, const vector<int>& order) {
  if (array.empty() || order.size() != 3)
    return array;

  auto litr = array.begin();
  auto ritr = --array.end();
  auto last = array.end();
  while (order[0] == *litr && litr != last)
    ++litr;
  for (auto curr = litr; curr != last;) {
    if (order[0] == *curr) {
      if (curr != litr) {
        std::swap(*litr, *curr);
        ++litr;
      } else {
        ++curr;
        continue;
      }
    }

    if (order[2] == *curr) {
      std::swap(*curr, *ritr);
      --ritr;
      --last;
    }

    if (order[1] == *curr)
      ++curr;
  }

  return array;
}

int main() {
  const auto v1 = threeNumberSort({0, 1, 2, 1, 2, 2, 2, 1, 0}, {0, 1, 2});

  print_elements(cbegin(v1), cend(v1), cout);

  cout << '\n';

  const auto v2 = threeNumberSort({2, 2, 1, 1, 1, 0, 0, 0, 0}, {0, 1, 2});

  print_elements(cbegin(v2), cend(v2), cout);

  cout << '\n';

  const auto v3 = threeNumberSort({1, 2, 0, 2, 0, 1, 0, 2, 1}, {0, 1, 2});

  print_elements(cbegin(v3), cend(v3), cout);

  cout << '\n';

  const auto v4 = threeNumberSort({0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 2});

  print_elements(cbegin(v4), cend(v4), cout);

  cout << '\n';

  const auto v5 = threeNumberSort({1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 1, 2});

  print_elements(cbegin(v5), cend(v5), cout);

  cout << '\n';

  const auto v6 = threeNumberSort({2, 2, 2, 2, 2, 2, 2, 2, 2}, {0, 1, 2});

  print_elements(cbegin(v6), cend(v6), cout);

  cout << '\n';

  const auto v7 = threeNumberSort({0}, {0, 1, 2});

  print_elements(cbegin(v7), cend(v7), cout);

  cout << '\n';

  const auto v8 = threeNumberSort({}, {0, 1, 2});

  print_elements(cbegin(v8), cend(v8), cout);

  cout << '\n';

  const auto v9 = threeNumberSort({0, 1, 2, 0}, {0, 1, 2});

  print_elements(cbegin(v9), cend(v9), cout);

  cout << '\n';

  const auto v10 = threeNumberSort({2, 1, 0, 0}, {0, 1, 2});

  print_elements(cbegin(v10), cend(v10), cout);

  cout << '\n';

  const auto v11 = threeNumberSort({1, 0, 0, -1, -1, 0, 1, 1}, {0, 1, -1});

  print_elements(cbegin(v11), cend(v11), cout);

  cout << '\n';

  return 0;
}
