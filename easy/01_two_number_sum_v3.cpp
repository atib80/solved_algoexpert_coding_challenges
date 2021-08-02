#include <vector>

// asymptotic time complexity:  O(n^2))
// asymptotic space complexity: O(1)

using namespace std;

vector<int> twoNumberSum(const vector<int>& array, const int target_sum) {	

	for (size_t i{}; i < array.size() - 1; ++i) {
		for (size_t j{i + 1}; j < array.size(); ++j) {
			if (array[i] + array[j] == target_sum) 
				return {array[i], array[j]};
		}
	}
  return {};
}
