#include <unordered_set>
#include <vector>

// asymptotic time complexity:  O(n)
// asymptotic space complexity: O(n)

using namespace std;

vector<int> twoNumberSum(const vector<int>& array, const int target_sum) {
	
	unordered_set<int> visited_numbers{};
	
	for (const auto n : array) {
		if (visited_numbers.find(target_sum - n) != end(visited_numbers)) {
			   return {n, target_sum - n};
			}
		visited_numbers.emplace(n);
	}

	return {};
}
