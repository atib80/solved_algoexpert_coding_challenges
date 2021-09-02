#include <iostream>
#include <vector>

using namespace std;

bool isValidSubsequence(const vector<int>& array, const vector<int>& sequence) {
  if (array.empty() || sequence.empty())
    return false;

  auto target = sequence.cbegin();
  auto current = array.cbegin();
  while (target != sequence.cend() && current != array.cend()) {
    if (*target == *current) {
      ++target;
      ++current;
    } else {
      ++current;
    }
  }

  return target == sequence.cend();
}

int main() {
  cout << boolalpha;
  cout << "isValidSubsequence([1, 2, 3, 4], [1, 3, 4]) -> "
       << isValidSubsequence({1, 2, 3, 4}, {1, 3, 4})
       << '\n';  // expected output: true
  cout << "isValidSubsequence([1, 2, 3, 4], [2, 4]) -> "
       << isValidSubsequence({1, 2, 3, 4}, {2, 4})
       << '\n';  // expected output: true
  cout << "isValidSubsequence([1, 2, 3, 4], [1, 4, 5]) -> "
       << isValidSubsequence({1, 2, 3, 4}, {1, 4, 5})
       << '\n';  // expected output: false
  cout << "isValidSubsequence([5, 1, 22, 25, 6, -1, 8, 10], [1, 6, -1, 10]) -> "
       << isValidSubsequence({5, 1, 22, 25, 6, -1, 8, 10}, {1, 6, -1, 10})
       << '\n';  // expected output: true
  cout << "isValidSubsequence([5, 1, 22, 25, 6, -1, 8, 10], [1, 7, -1, 10]) -> "
       << isValidSubsequence({5, 1, 22, 25, 6, -1, 8, 10}, {1, 7, -1, 10})
       << '\n';  // expected output: false

  return 0;
}
