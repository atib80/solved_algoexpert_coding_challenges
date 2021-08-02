#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class valid_ip_address_generator {
  class iterator {
    std::vector<std::string>::iterator pos_;
    const std::vector<std::string>& ip_addresses_;

   public:
    using iterator_category = std::forward_iterator_tag;

    explicit iterator(const std::vector<std::string>::iterator& pos,
                      const std::vector<std::string>& ip_addresses)
        : pos_{pos}, ip_addresses_{ip_addresses} {}

    std::string& operator*() { return *pos_; }
    const std::string& operator*() const { return *pos_; }

    iterator& operator++() {
      if (ip_addresses_.end() != pos_)
        ++pos_;
      return *this;
    }

    iterator operator++(int) {
      iterator temp{*this};
      if (ip_addresses_.end() != pos_)
        ++pos_;
      return temp;
    }

    bool operator==(const iterator& other) const {
      return this->pos_ == other.pos_;
    }
    bool operator!=(const iterator& other) const { return !(*this == other); }
  };

  class const_iterator {
    std::vector<std::string>::const_iterator const_pos_;
    const std::vector<std::string>& ip_addresses_;

   public:
    using iterator_category = std::forward_iterator_tag;

    explicit const_iterator(
        const std::vector<std::string>::const_iterator& const_pos,
        const std::vector<std::string>& ip_addresses)
        : const_pos_{const_pos}, ip_addresses_{ip_addresses} {}

    const std::string& operator*() const { return *const_pos_; }

    const_iterator& operator++() {
      if (ip_addresses_.cend() != const_pos_)
        ++const_pos_;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator temp{*this};
      if (ip_addresses_.cend() != const_pos_)
        ++const_pos_;
      return temp;
    }

    bool operator==(const const_iterator& other) const {
      return this->const_pos_ == other.const_pos_;
    }
    bool operator!=(const const_iterator& other) const {
      return !(*this == other);
    }
  };

 public:
  valid_ip_address_generator(const std::string& ip_address_digits)
      : ip_address_digits_{ip_address_digits}, state_{"3333"} {
    generate_all_valid_ip_addresses();
  }

  const std::vector<std::string>& get_all_valid_ip_addresses() const noexcept {
    return valid_ip_addresses_;
  }

  iterator begin() {
    return iterator{valid_ip_addresses_.begin(), valid_ip_addresses_};
  }

  iterator end() {
    return iterator{valid_ip_addresses_.end(), valid_ip_addresses_};
  }

  const_iterator begin() const {
    return const_iterator{valid_ip_addresses_.cbegin(), valid_ip_addresses_};
  }

  const_iterator end() const {
    return const_iterator{valid_ip_addresses_.cend(), valid_ip_addresses_};
  }

  const_iterator cbegin() const {
    return const_iterator{valid_ip_addresses_.cbegin(), valid_ip_addresses_};
  }

  const_iterator cend() const {
    return const_iterator{valid_ip_addresses_.cend(), valid_ip_addresses_};
  }

 private:
  void generate_all_valid_ip_addresses() const {
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

        for (size_t k{pos},
             last = std::min(pos + (s - '0'), ip_address_digits_.length());
             k < last; ++k) {
          ip_part.push_back(ip_address_digits_[k]);
        }

        if (!(ip_part.length() >= 1U && ip_part.length() <= 3U) ||
            std::any_of(std::cbegin(ip_part), std::cend(ip_part),
                        [](const char ch) { return ch < '0' || ch > '9'; }) ||
            ('0' == ip_part[0] && ip_part.length() != 1U) ||
            (stoi(ip_part) > 255))
          break;

        ip_address += ip_part;

        pos += s - '0';
      }

      if (ip_address_digits_.length() == pos)
        valid_ip_addresses_.emplace_back(std::move(ip_address));
    }
  }

  size_t get_state_sum(const std::string& state) const noexcept {
    size_t sum{};
    for (const char ch : state)
      sum += ch - '0';
    return sum;
  }

  const std::string ip_address_digits_;
  mutable std::string state_;
  mutable std::vector<std::string> valid_ip_addresses_;
  mutable bool is_repeated_ = false;
};

std::vector<std::string> validIPAddresses(const std::string& str) {
  valid_ip_address_generator ip_address_generator{str};

  std::vector<std::string> valid_ip_addresses;

  for (auto&& valid_ip : ip_address_generator) {
    valid_ip_addresses.emplace_back(std::move(valid_ip));
  }

  return valid_ip_addresses;
}

int main() {
  const std::vector<std::string> valid_ip_addresses{
      validIPAddresses("1921680")};

  for (const auto& valid_ip : valid_ip_addresses) {
    std::cout << valid_ip << '\n';
  }

  return 0;
}
