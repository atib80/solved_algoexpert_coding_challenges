#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string& source,
                     const string& needle,
                     const bool split_on_whole_needle = true,
                     const bool ignore_empty_string = true,
                     size_t const max_count = string::npos) {
  const size_t source_len{source.length()};
  if (0U == source_len)
    return {};

  const size_t needle_len{split_on_whole_needle ? needle.length() : 1U};

  if (0U == needle_len) {
    const size_t upper_limit{max_count < source_len ? max_count : source_len};
    vector<string> parts(upper_limit);
    for (size_t i{}; i < upper_limit; ++i)
      parts[i] = string{1, source[i]};
    return parts;
  }

  vector<string> parts{};
  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current = split_on_whole_needle
                               ? source.find(needle.c_str(), prev)
                               : source.find_first_of(needle.c_str(), prev);

    if (string::npos == current)
      break;

    if (string::npos != max_count && parts.size() == max_count)
      break;

    if (current - prev > 0 || !ignore_empty_string) {
      if (!ignore_empty_string)
        parts.emplace_back();
      else
        parts.emplace_back(cbegin(source) + prev, cbegin(source) + current);
      number_of_parts++;
    }

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len &&
      (string::npos == max_count || parts.size() < max_count))
    parts.emplace_back(cbegin(source) + prev, cend(source));

  return parts;
}

size_t get_state_sum(const string& state) noexcept {
  size_t sum{};
  for (const char ch : state)
    sum += ch - '0';
  return sum;
}

bool get_next_state(
    string& state,
    const size_t desired_state_sum = numeric_limits<size_t>::max(),
    const bool is_reset = false) {
  static string state_{"3333"};
  static bool is_repeated = false;

  if (is_reset) {
    state_ = "3333";
    is_repeated = false;
    return false;
  }

  do {
    for (size_t i{state_.size()}; i > 0; --i) {
      const size_t index{i - 1};
      if ('3' == state_[index]) {
        state_[index] = '1';
      } else {
        state_[index] += 1;
        break;
      }
    }

    if (state_ == "1111") {
      is_repeated = !is_repeated;
      if (!is_repeated) {
        state = state_;
        return false;
      }
    }

  } while (desired_state_sum != numeric_limits<size_t>::max() &&
           desired_state_sum != get_state_sum(state_));

  state = state_;
  return true;
}

bool check_if_ip_address_is_valid(const string& ip) {
  const vector<string> ip_parts{split(ip, ".")};

  if (ip_parts.size() != 4)
    return false;

  for (const auto& ip_part : ip_parts) {
    if (!(ip_part.length() >= 1U && ip_part.length() <= 3U) ||
        any_of(cbegin(ip_part), cend(ip_part),
               [](const char ch) { return ch < '0' || ch > '9'; }) ||
        ('0' == ip_part[0] && ip_part.length() != 1U) || (stoi(ip_part) > 255))
      return false;
  }

  return true;
}

vector<string> validIPAddresses(const string& str) {
  const size_t max_ip_address_length{str.length() + 3};

  vector<string> valid_ip_addresses;
  string state;

  get_next_state(state, str.length(), true);

  while (get_next_state(state, str.length())) {
    size_t pos{};
    string ip_address;
    ip_address.reserve(max_ip_address_length);

    for (const char s : state) {
      if (0 != pos) {
        ip_address.push_back('.');
      }

      for (size_t k{pos}, last = min(pos + (s - '0'), str.length()); k < last;
           ++k) {
        ip_address.push_back(str[k]);
      }

      pos += s - '0';
    }

    if (check_if_ip_address_is_valid(ip_address))
      valid_ip_addresses.emplace_back(ip_address);
  }

  return valid_ip_addresses;
}

int main() {
  const vector<string> valid_ip_addresses{validIPAddresses("1921680")};

  for (const auto& valid_ip : valid_ip_addresses) {
    cout << valid_ip << '\n';
  }

  return 0;
}
