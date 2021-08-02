#include <string>

using namespace std;

// asymptotic time complexity:  O(n)
// asymptotic space complexity: O(1)

bool isPalindrome(const string& str) {
	
	if (str.empty()) 
		return false;
	
	for (size_t i{}, j{str.length() - 1}; i < j; ++i, --j) {
		if (str[i] != str[j]) 
			return false;
	}
  
  return true;
}
