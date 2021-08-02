#include <algorithm>
#include <string>

using namespace std;

// asymptotic time complexity:  O(n)
// asymptotic space complexity: O(n)

bool isPalindrome(const string& str) {
	
	if (str.empty()) 
		return false;
  
	string reversed_str{str};
	
	reverse(begin(reversed_str), end(reversed_str));
	
	return str == reversed_str;	
  
}
