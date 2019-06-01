#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include "big_integer.h"

using namespace std;

big_integer::big_integer(): sign(0), digits(1) {
}

big_integer::big_integer(big_integer const &other) {
    digits = other.digits;
    sign = other.sign;
}

big_integer::big_integer(shared_vector digits, int sign) : digits(digits), sign(sign) {}

big_integer::big_integer(int a) {
    sign = a != 0 ? (a > 0 ? 1 : -1) : 0;
    digits.push_back(static_cast<uint32_t>(abs(1LL * a)));
}

big_integer::big_integer(std::string const &str) {
    for (ptrdiff_t i = static_cast<size_t>(str[0] == '-'); i < str.size(); i++) {
        *this = *this * 10 + (str[i] - '0');
    }
    sign = (str[0] == '-' ? -1 : 1);
    norm();
}

big_integer &big_integer::operator=(big_integer const &other) = default;

big_integer::~big_integer() = default;

void big_integer::add_with_shift(const big_integer &a, int shift) {
    uint64_t tmp = 0;
    if (a.sign == 0) {
        return;
    }
    if (this->digits.size() >= a.digits.size() + shift) {
        for (ptrdiff_t i = 0; i < a.digits.size(); i++) {
            uint64_t res = (uint64_t) a.digits[i] + this->digits[i + shift] + tmp;
            this->digits[shift + i] = (uint32_t) res;
            tmp = static_cast<uint64_t>(res > big_integer::max_digit);
        }

        for (ptrdiff_t i = a.digits.size(); i < this->digits.size() - shift; i++) {
            uint64_t res = this->digits[i] + tmp;
            this->digits[shift + i] = (uint32_t) res;
            tmp = static_cast<uint64_t>(res > big_integer::max_digit);
        }
    } else if (shift >= this->digits.size()) {
        for (ptrdiff_t i = this->digits.size(); i < shift; i++) {
            this->digits.push_back(0);
        }
        for (ptrdiff_t i = 0; i < a.digits.size(); i++) {
            uint32_t digit = a.digits[i];
            this->digits.push_back(digit);
        }
    } else {
        for (ptrdiff_t i = static_cast<size_t>(shift); i < this->digits.size(); i++) {
            uint64_t res = uint64_t(a.digits[i - shift]) + this->digits[i] + tmp;
            tmp = static_cast<uint64_t>(res > big_integer::max_digit);
            this->digits[i] = static_cast<uint32_t>(res);
        }
        for (ptrdiff_t i = this->digits.size(); i < a.digits.size() + shift; i++) {
            uint64_t res = a.digits[i - shift] + tmp;
            tmp = static_cast<uint64_t>(res > big_integer::max_digit);
            this->digits.push_back(static_cast<uint32_t>(res));
        }
    }
    if (tmp > 0) {
        this->digits.push_back(static_cast<uint32_t>(tmp));
    }
    sign = 1;
}

big_integer big_integer::mul_short(uint32_t a) const {
    if (a == 0) {
        return big_integer();
    }

    big_integer ans;
    ans.digits.pop_back();
    uint32_t carry = 0;
    for (int i = 0; i < digits.size(); i++) {
        uint32_t digit = digits[i];
        uint64_t res = uint64_t(digit) * a + carry;
        carry = static_cast<uint32_t>(res / (big_integer::max_digit + 1));
        ans.digits.push_back(static_cast<uint32_t>(res));
    }
    if (carry != 0) {
        ans.digits.push_back(carry);
    }
    ans.sign = sign;
    return ans;
}


big_integer operator+(big_integer a, big_integer const &b) {
    if (b.sign < 0) {
        return a - (-b);
    } else if (a.sign < 0) {
        return b - (-a);
    }
    big_integer res = a;
    res.add_with_shift(b, 0);
    return res;
}

big_integer operator-(big_integer a, big_integer const &b) {
    if (a.sign < 0) {
        return -((-a) + b);
    } else if (b.sign < 0) {
        return a + (-b);
    }
    const big_integer *less, *more;
    int new_sign = 0;
    if (a.digits.size() >= b.digits.size()) {
        new_sign = 1;
        less = &b, more = &a;
    } else {
        new_sign = -1;
        less = &a, more = &b;
    }

    big_integer res;
    res.digits.pop_back();
    int carry = 0;
    for (ptrdiff_t i = 0; i < less->digits.size(); i++) {
        if (less->digits[i] <= more->digits[i] - carry) {
            res.digits.push_back(more->digits[i] - carry - less->digits[i]);
            carry = 0;
        } else {
            uint64_t new_digit = more->digits[i] + big_integer::max_digit + 1;
            res.digits.push_back(static_cast<uint32_t>(new_digit - carry - less->digits[i]));
            carry = 1;
        }
    }

    for (ptrdiff_t i = less->digits.size(); i < more->digits.size(); i++) {
        res.digits.push_back(more->digits[i] - carry);
        carry = 0;
    }
    if (carry == 1 && less->digits.size() == more->digits.size()) {
        new_sign = -new_sign;
        res.digits[res.digits.size() - 1] = static_cast<uint32_t>(big_integer::max_digit + 1 -
                                                                  res.digits[res.digits.size() - 1]);
    }
    res.sign = new_sign;
    res.norm();
    return res;
}

big_integer big_integer::operator+() const {
    return (*this);
}

big_integer big_integer::operator-() const {
    big_integer result(*this);
    result.sign *= -1;
    return result;
}

big_integer operator*(big_integer a, big_integer const &b) {
    if (a.sign == 0 && b.sign == 0) {
        return big_integer();
    }

    big_integer res;
    for (ptrdiff_t i = 0; i < b.digits.size(); i++) {
        res.add_with_shift(a.mul_short(b.digits[i]), i);
    }
    res.sign = a.sign * b.sign;
    return res;
}

std::pair<big_integer, uint32_t> big_integer::div_short(uint32_t b) const {
    if (b == 0)
        throw std::runtime_error("Divide by zero");
    uint32_t ost;
    uint64_t carry = 0;
    //big_integer result;
    vector<uint32_t> new_digits;
    new_digits.resize(digits.size());
    //result.digits.pop_back();

    //new_digits.resize(digits.size());
    for (ptrdiff_t i = digits.size() - 1; i >= 0; i--) {
        uint64_t cur = digits[i] + carry * (big_integer::max_digit + 1);
        new_digits[i] = uint32_t(cur / b);
        carry = cur % b;
    }
    ost = uint32_t(carry);
    big_integer result = big_integer(shared_vector(new_digits), 0);
    result.sign = sign * (b > 0 ? 1 : -1);
    result.norm();
    return std::pair<big_integer, uint32_t>(result, ost);
}

uint64_t normalize(big_integer &a, big_integer &b) {
    uint64_t normalizer = (big_integer(1).shl_32(1).div_short(b.digits[b.digits.size() - 1] + 1)).first.digits[0];
    a *= normalizer;
    b *= normalizer;
    return normalizer;
}


big_integer operator/(big_integer a, big_integer const &b) {
    if (a.sign == -1 && b.sign == -1)
        return (-a) / (-b);
    if (a.sign == -1)
        return -((-a) / b);
    if (b.sign == -1)
        return -(a / (-b));
    if (b > a)
        return big_integer();
    if (b.digits.size() == 1) {
        a.sign *= b.sign;
        return a.div_short(b.digits[0]).first;
    }
    int size = sizeof(unsigned int) * 8;
    auto normalizer = static_cast<uint32_t>((1LL << size) / ((uint64_t) (b.digits.back() + 1)));
    big_integer dividend = a.mul_short(normalizer);
    big_integer divisor = b.mul_short(normalizer);

    big_integer res = 0; res.digits.pop_back();
    vector<uint32_t> res_digits;
    size_t n = dividend.digits.size();
    size_t m = divisor.digits.size();
    big_integer mod;
    big_integer tmp = dividend;
    mod = dividend.shr_32(n-m+1);
    dividend = tmp;
    uint64_t top = divisor.digits.back();
    for (ptrdiff_t index = 0; index <= n - m; index++) {
        size_t idx = n - m - index;
        mod = mod.shl_32(1);
        mod.digits[0] = dividend.digits[idx];
        uint64_t mod_top = mod.digits.back();

        if (mod.digits.size() > m) {
            mod_top <<= size;
            mod_top += mod.digits[mod.digits.size()-2];
        }

        uint64_t guess = mod_top / top;
        if (guess > UINT32_MAX) {
            guess = UINT32_MAX;
        }
        big_integer res_guess = divisor.mul_short(static_cast<uint32_t>(guess));
        while (mod < res_guess) {
            guess--;
            res_guess -= divisor;
        }
        res_digits.push_back(static_cast<uint32_t>(guess));
        mod -= res_guess;
    }
    std::reverse(res_digits.begin(), res_digits.end());
    res.digits = shared_vector(res_digits);
    res.sign = a.sign * b.sign;
    res.norm();
    return res;
}

big_integer operator%(big_integer a, big_integer const &b) {
    return a - b * (a / b);
}

big_integer &big_integer::operator%=(big_integer const &rhs) {
    return (*this = *this % rhs);
}

bool operator==(big_integer const &a, big_integer const &b) {
    if (a.sign != b.sign || a.digits.size() != b.digits.size()) {
        return false;
    }
    for (int i = 0; i < a.digits.size(); i++) {
        if (a.digits[i] != b.digits[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(big_integer const &a, big_integer const &b) {
    return !(a == b);
}

bool operator<(big_integer const &a, big_integer const &b) {
    if (a.sign != b.sign) {
        return a.sign < b.sign;
    }
    if (a.sign == 0) {
        return false;
    }
    if (a.digits.size() != b.digits.size()) {
        return (a.digits.size() < b.digits.size()) ^ (a.sign == -1);
    }
    for (ptrdiff_t i = a.digits.size() - 1; i >= 0; i--) {
        if (a.digits[i] < b.digits[i]) {
            return true;
        }
        if (a.digits[i] > b.digits[i]) {
            return false;
        }
    }
    return false;
}

bool operator<=(big_integer const &a, big_integer const &b) {
    return (a < b || a == b);
}

bool operator>(big_integer const &a, big_integer const &b) {
    return b < a;
}

bool operator>=(big_integer const &a, big_integer const &b) {
    return b <= a;
}

big_integer &big_integer::operator+=(big_integer const &rhs) {
    return *this = *this + rhs;
}

big_integer &big_integer::operator-=(big_integer const &rhs) {
    return *this = *this - rhs;
}

big_integer &big_integer::operator*=(big_integer const &rhs) {
    return *this = *this * rhs;
}

big_integer &big_integer::operator/=(big_integer const &rhs) {
    return *this = *this / rhs;
}

uint32_t big_integer::get_ind(uint32_t ind) const {
    return (ind < digits.size()) ? digits[ind] : 0;
}

uint32_t big_integer::get_bitwise_ind(uint32_t ind) const {
    return static_cast<uint32_t>(sign == -1 ? (get_ind(ind) ^ big_integer::max_digit) : get_ind(ind));
}

big_integer big_integer::to_bitwise() const {
    return (sign == -1) ? *this + 1 : *this;
}

big_integer big_integer::from_bitwise() const {
    if (sign != -1) {
        return *this;
    } else {
        big_integer res = (*this);
        for (ptrdiff_t i = 0; i < digits.size(); i++) {
            res.digits[i] = ~digits[i];
        }
        res.sign = -1;
        res--;
        return res;
    }
}

template <class FunctorT>
big_integer doOps(big_integer a, big_integer const &b,FunctorT f) {
    big_integer res; res.digits.pop_back();
    vector <uint32_t> new_digits;
    new_digits.resize(std::max(a.digits.size(), b.digits.size()));
    //res.digits.resize(std::max(a.digits.size(), b.digits.size()));
    big_integer first = a.to_bitwise();
    first.sign = a.sign;
    big_integer second = b.to_bitwise();
    second.sign = b.sign;
    for (uint32_t i = 0; i < new_digits.size(); i++) {
        new_digits[i] = f(first.get_bitwise_ind(i), second.get_bitwise_ind(i));
    }
    res = big_integer(shared_vector(new_digits), 0);
    res.sign = (f(first.sign == -1, second.sign == -1)) == 1 ? -1 : 1;
    res = res.from_bitwise();
    res.norm();
    return res;

}

big_integer operator&(big_integer a, big_integer const &b) {
    return doOps(a, b, [](uint32_t a, uint32_t b) -> uint32_t {return a & b; });
}

big_integer operator|(big_integer a, big_integer const &b) {
    return doOps(a, b, [](uint32_t a, uint32_t b) -> uint32_t {return a | b; });
}

big_integer operator^(big_integer a, big_integer const &b) {
    return doOps(a, b, [](uint32_t a, uint32_t b) -> uint32_t {return a ^ b; });
}

big_integer big_integer::operator~() const {
    return -*this-1;
}

big_integer &big_integer::operator&=(big_integer const &rhs) {
    return *this = *this & rhs;
}

big_integer &big_integer::operator|=(big_integer const &rhs) {
    return *this = *this | rhs;
}


big_integer &big_integer::operator^=(big_integer const &rhs) {
    return *this = *this ^ rhs;
}

big_integer &big_integer::shl_32(size_t shift) {
    size_t old_size = digits.size();
    vector <uint32_t > new_digits;
    new_digits.resize(old_size + shift, 0);
    for (int i = 0; i < old_size; i++) {
        new_digits[i] = digits[i];
    }
    //digits.resize(old_size + shift, 0);

    for (ptrdiff_t i = old_size - 1; i >= 0; i--) {
        new_digits[i + shift] = new_digits[i];
    }
    for (ptrdiff_t i = shift - 1; i >= 0; i--) {
        new_digits[i] = 0;
    }
    digits = shared_vector(new_digits);
    return (*this);
}

big_integer operator<<(big_integer a, int shift) {
    big_integer res(a);
    res.shl_32(static_cast<size_t>(shift / 32));
    shift %= 32;
    uint32_t carry = 0;
    uint32_t next_carry = 0;

    for (ptrdiff_t ind = 0; ind < res.digits.size(); ind++) {
        uint32_t i = res.digits[ind];
        next_carry = (i >> (32 - shift));
        res.digits[ind] = static_cast<uint32_t >((i << shift) + carry);
        carry = next_carry;
    }

    if (carry != 0) {
        res.digits.push_back(carry);
    }

    return res;
}

big_integer &big_integer::operator<<=(int rhs) {
    return (*this = *this << rhs);
}

big_integer &big_integer::shr_32(size_t shift) {
    vector <uint32_t > new_digits;
    new_digits.resize(digits.size(), 0);
    for (int i = 0; i < digits.size(); i++) {
        new_digits[i] = digits[i];
    }
    for (ptrdiff_t i = shift; i < digits.size(); i++) {
        new_digits[i - shift] = new_digits[i];
    }
    new_digits.resize(digits.size() - shift);
    digits = shared_vector(new_digits);
    //digits.resize(digits.size() - shift);
    return (*this);
}

big_integer operator>>(big_integer a, int shift) {
    big_integer res(a);
    res.shr_32(static_cast<size_t>(shift / 32));
    shift %= 32;
    uint32_t carry = 0;
    uint32_t next_carry = 0;
    res.sign = -1;

    for (ptrdiff_t i = res.digits.size() - 1; i >= 0; i--) {
        next_carry = (res.digits[i] << (32 - shift));
        res.digits[i] = static_cast<uint32_t >((res.digits[i] >> shift) + carry);
        carry = next_carry;
    }
    res.norm();
    if (a.sign < 0) {
        res -= 1;
    } else {
        res = -res;
    }

    return res;
}

big_integer &big_integer::operator>>=(int rhs) {
    return (*this = *this >> rhs);
}


void big_integer::norm() {
    while (digits[digits.size() - 1] == 0 && digits.size() > 1) {
        digits.pop_back();
    }
    if (digits.size() == 1 && digits[0] == 0) {
        sign = 0;
    }
}

big_integer &big_integer::operator++() {
    return (*this = *this + 1);
}

const big_integer big_integer::operator++(int) {
    big_integer ans = *this;
    *this = *this + 1;
    return ans;
}

big_integer &big_integer::operator--() {
    return (*this = *this - 1);
}

const big_integer big_integer::operator--(int) {
    big_integer ans = *this;
    *this = *this - 1;
    return ans;
}

std::string to_string(big_integer const &a) {
    string ans;
    if (a.sign == 0) {
        return ("0");
    }
    big_integer b = a;
    while (b != 0) {
        auto tmp = b.div_short(10);
        ans.push_back('0' + (char) tmp.second);
        b = tmp.first;
    }
    if (a.sign == -1) {
        ans.push_back('-');
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}


std::ostream &operator<<(std::ostream &s, big_integer const &a) {
    s << to_string(a);
    return s;
}
