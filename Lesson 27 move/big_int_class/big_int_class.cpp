#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <assert.h>
#include <cmath>

class big_integer {
private:
  std::vector<int> digits;

  void remove_leading_zeros() {
    while (digits.size() > 0 && digits.back() == 0) {
      digits.pop_back();
    }
  }

public:
  big_integer(const std::string& s) {
    if (s.empty()) {
      throw std::invalid_argument("Empty string");
    }

    for (size_t i = s.size(); i > 0; --i) {
      char c = s[i - 1];
      if (!isdigit(c)) {
        throw std::invalid_argument("Invalid character in number");
      }
      digits.push_back(static_cast<int>(c) - static_cast<int>('0'));
    }

    remove_leading_zeros();
  }

  big_integer(big_integer&& other) noexcept
    : digits(std::move(other.digits)) {
    other.digits = { 0 };
  }

  big_integer& operator=(big_integer&& other) noexcept {
    if (this != &other) {
      digits = std::move(other.digits);
      other.digits = { 0 };
    }
    return *this;
  }

  big_integer operator+(const big_integer& other) const {
    big_integer result("0");

    size_t max_len = std::max(digits.size(), other.digits.size());
    result.digits.reserve(max_len + 1);

    int carry = 0;
    for (size_t i = 0; i < max_len || carry; ++i) {
      int a = i < digits.size() ? digits[i] : 0;
      int b = i < other.digits.size() ? other.digits[i] : 0;
      int sum = a + b + carry;

      result.digits.push_back(sum % 10);
      carry = sum / 10;
    }

    result.remove_leading_zeros();

    return result;
  }

  big_integer operator*(int num) const {
    if (num == 0) {
      return big_integer("0");
    }

    big_integer result("0");

    int numDigits = static_cast<int>(log10(abs(num)) + 1);

    int max_len = digits.size() + numDigits;

    result.digits.reserve(max_len + 1);

    int carry = 0;
    for (size_t i = 0; i < digits.size(); ++i) {
      int product = digits[i] * num + carry;
      result.digits.push_back(product % 10);
      carry = product / 10;      
    }   

    while (carry > 0) {
      result.digits.push_back(carry % 10);
      carry /= 10;
    }

    result.remove_leading_zeros();
    return result;
  }

  friend std::ostream& operator<<(std::ostream& os, const big_integer& num) {
    for (auto k = num.digits.rbegin(); k != num.digits.rend(); ++k) {
      os << *k;
    }
    return os;
  }

  big_integer(const big_integer&) = delete;
  big_integer& operator=(const big_integer&) = delete;
};

int main() {
  auto number1 = big_integer("914575");
  auto number2 = big_integer("98524");
  auto result = number1 + number2; 
  std::cout << result << std::endl;
  std::stringstream ss1;
  ss1 << result;
  assert(ss1.str() == "1013099");

  auto number3 = big_integer("444444444");
  auto result2 = number3 * 2;
  std::cout << result2 << std::endl;
  std::stringstream ss;
  ss << result2;
  assert(ss.str() == "888888888");

}
