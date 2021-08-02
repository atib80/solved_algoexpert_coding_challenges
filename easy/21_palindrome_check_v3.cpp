#include <stack>
#include <string>

using namespace std;

// asymptotic time complexity:  O(n)
// asymptotic space complexity: O(n)

bool isPalindrome(const string& str) {
	
	if (str.empty()) 
		return false;
  
	std::stack<char> s;
	
	for (const char ch : str) 
		s.emplace(ch);
	
	for (const char ch : str) {
		if (ch != s.top()) 
			return false;		
		s.pop();
	}	
	
  return true;
}
