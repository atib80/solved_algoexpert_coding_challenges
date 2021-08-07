#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class valid_ip_address_generator {
 public:
  valid_ip_address_generator(const std::string& ip_address_digits)
      : ip_address_digits_{ip_address_digits}, state_{"3333"} {
    generate_all_valid_ip_addresses();
  }

  std::vector<std::string>& get_all_valid_ip_addresses() noexcept {
    return valid_ip_addresses_;
  }

 private:
  void generate_all_valid_ip_addresses() {
    const size_t max_ip_address_length{ip_address_digits_.length() + 3};

    while (true) {
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
        is_repeated_ = !is_repeated_;
        if (!is_repeated_)
          break;
      }

      if (ip_address_digits_.length() != get_state_sum(state_))
        continue;

      size_t pos{};
      std::string ip_address;
      ip_address.reserve(max_ip_address_length);

      for (const char s : state_) {
        std::string ip_part;

        if (0 != pos) {
          ip_address.push_back('.');
        }

        for (size_t k{pos}, last = pos + (s - '0'); k < last; ++k) {
          ip_part.push_back(ip_address_digits_[k]);
        }

        if (('0' == ip_part[0] && ip_part.length() != 1U) ||
            stoi(ip_part) > 255)
          break;

        ip_address += ip_part;
        pos += s - '0';
      }

      if (ip_address_digits_.length() == pos)
        valid_ip_addresses_.emplace_back(std::move(ip_address));
    }
  }

  inline size_t get_state_sum(const std::string& state) const noexcept {
    size_t sum{};
    for (const char ch : state)
      sum += ch - '0';
    return sum;
  }

  const std::string ip_address_digits_;
  std::string state_;
  std::vector<std::string> valid_ip_addresses_;
  bool is_repeated_ = false;
};

std::vector<std::string> validIPAddresses(const std::string& str) {
  valid_ip_address_generator ip_address_generator{str};

  return std::move(ip_address_generator.get_all_valid_ip_addresses());
}

int main() {
  const std::vector<std::string> valid_ip_addresses{
      validIPAddresses("1921680")};

  for (const auto& valid_ip : valid_ip_addresses) {
    std::cout << valid_ip << '\n';
  }

  return 0;
}
