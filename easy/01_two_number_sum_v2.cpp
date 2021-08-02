#include <algorithm>
#include <vector>

// asymptotic time complexity:  O(n*lg(n))
// asymptotic space complexity: O(1)

using namespace std;

vector<int> twoNumberSum(vector<int> array, const int target_sum) {

	sort(begin(array), end(array));
  vector<int>::const_iterator low = cbegin(array);
	vector<int>::const_iterator high = --cend(array);
	
	while (low < high) {
		const int current_sum = *low + *high;
		
		if (current_sum == target_sum) {
			return {*low, *high};
		}
		
		if (current_sum < target_sum) {
			++low;			
		} else {
			--high;			
		}
	}
	
  return {};
}
