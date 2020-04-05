//
// Created by Joshua2018 on 2020/4/2.
//

#include "BigInt.h"

#include <algorithm>
#include <stdexcept>
#include <iostream>

namespace ben_birdland {
BigInt::BigInt() {
    positive_ = true;
    digits_ = "0";
}

BigInt::BigInt(int integer) {
    positive_ = integer >= 0;
    digits_ = std::to_string(std::abs(integer));
    std::reverse(digits_.begin(), digits_.end());
}

BigInt::BigInt(const std::string &big_int_string) {
    if (big_int_string.empty()) {
        throw std::runtime_error("BigInt string cannot be empty");
    }
    positive_ = big_int_string[0] != '-';
    for (int i_digit = (positive_ ? 0 : 1); i_digit < big_int_string.size(); ++i_digit) {
        if (big_int_string[i_digit] < '0' or big_int_string[i_digit] > '9') {
            throw std::runtime_error("BigInt string contains invalid character");
        }
    }
    digits_ = (positive_ ? big_int_string : big_int_string.substr(1));
    std::reverse(digits_.begin(), digits_.end());
}

BigInt::BigInt(const BigInt &other) {
    this->positive_ = other.positive_;
    this->digits_ = other.digits_;
}

BigInt &BigInt::operator=(const BigInt &other) {
    if (&other != this) {
        this->positive_ = other.positive_;
        this->digits_ = other.digits_;
    }

    return *this;
}

BigInt &BigInt::operator=(int other_int) {
    positive_ = other_int >= 0;
    digits_ = std::to_string(std::abs(other_int));
    std::reverse(digits_.begin(), digits_.end());
    return *this;
}

BigInt operator-(const BigInt &other) {
    BigInt new_big_int;
    new_big_int.positive_ = !other.positive_;
    new_big_int.digits_ = other.digits_;

    return new_big_int;
}

BigInt abs(const BigInt &other) {
    BigInt new_big_int(other);
    new_big_int.positive_ = true;
    return new_big_int;
}

std::ostream &operator<<(std::ostream &ostream, const BigInt &big_int) {
    std::string negative_sign = "-";
    if (!big_int.positive_) {
        ostream << negative_sign;
    }

    std::string digits = big_int.digits_;
    std::reverse(digits.begin(), digits.end());
    ostream << digits;

    return ostream;
}

bool operator==(const BigInt &lhs, const BigInt &rhs) {
    return lhs.positive_ == rhs.positive_ and lhs.digits_ == rhs.digits_;
}

bool operator==(const BigInt &lhs, const int &rhs) {
    BigInt rhs_big_int(rhs);
    return lhs == rhs_big_int;
}

bool operator==(const int &lhs, const BigInt &rhs) {
    BigInt lhs_big_int(lhs);
    return lhs_big_int == rhs;
}

bool operator!=(const BigInt &lhs, const BigInt &rhs) {
    return !(lhs == rhs);
}

bool operator!=(const BigInt &lhs, const int &rhs) {
    return !(lhs == rhs);
}

bool operator!=(const int &lhs, const BigInt &rhs) {
    return !(lhs == rhs);
}

bool operator<(const BigInt &lhs, const BigInt &rhs) {
    if (!lhs.positive_ and rhs.positive_) {
        return true;
    } else if (lhs.positive_ and !rhs.positive_) {
        return false;
    }

    bool is_abs_less = true;

    if (lhs.digits_.size() < rhs.digits_.size()) {
        is_abs_less = true;
    } else if (lhs.digits_.size() > rhs.digits_.size() or
        lhs.digits_ == rhs.digits_) {
        is_abs_less = false;
    } else {
        for (int i_digit = static_cast<int>(lhs.digits_.size() - 1); i_digit >= 0; --i_digit) {
            if (lhs.digits_[i_digit] > rhs.digits_[i_digit]) {
                is_abs_less = false;
            }
            if (lhs.digits_[i_digit] != rhs.digits_[i_digit]) {
                break;
            }
        }
    }

    return lhs.positive_ == is_abs_less;
}

bool operator<(const BigInt &lhs, const int &rhs) {
    BigInt rhs_big_int(rhs);
    return lhs < rhs_big_int;
}

bool operator<(const int &lhs, const BigInt &rhs) {
    BigInt lhs_big_int(lhs);
    return lhs_big_int < rhs;
}

bool operator>(const BigInt &lhs, const BigInt &rhs) {
    return !(lhs <= rhs);
}

bool operator>(const BigInt &lhs, const int &rhs) {
    BigInt rhs_big_int(rhs);
    return lhs > rhs_big_int;
}

bool operator>(const int &lhs, const BigInt &rhs) {
    BigInt lhs_big_int(lhs);
    return lhs_big_int > rhs;
}

bool operator<=(const BigInt &lhs, const BigInt &rhs) {
    return lhs < rhs or lhs == rhs;
}

bool operator<=(const BigInt &lhs, const int &rhs) {
    BigInt rhs_big_int(rhs);
    return lhs <= rhs_big_int;
}

bool operator<=(const int &lhs, const BigInt &rhs) {
    BigInt lhs_big_int(lhs);
    return lhs_big_int < rhs;
}

bool operator>=(const BigInt &lhs, const BigInt &rhs) {
    return !(lhs < rhs);
}

bool operator>=(const BigInt &lhs, const int &rhs) {
    BigInt rhs_big_int(rhs);
    return lhs >= rhs_big_int;
}

bool operator>=(const int &lhs, const BigInt &rhs) {
    BigInt lhs_big_int(lhs);
    return lhs_big_int >= rhs;
}

BigInt operator+(const BigInt &lhs, const BigInt &rhs) {
    if (lhs.positive_ != rhs.positive_) {
        return lhs - -rhs;
    }

    int max_size = std::max(lhs.digits_.size(), rhs.digits_.size());
    std::string digits(max_size + 1, '0');

    for (int i_digit = 0; i_digit < max_size; ++i_digit) {
        if (i_digit < lhs.digits_.size()) {
            digits[i_digit] += lhs.digits_[i_digit] - '0';
        }
        if (i_digit < rhs.digits_.size()) {
            digits[i_digit] += rhs.digits_[i_digit] - '0';
        }

        if (digits[i_digit] > '9') {
            ++digits[i_digit + 1];
            digits[i_digit] -= 10;
        }
    }

    BigInt sum;
    sum.positive_ = lhs.positive_;
    sum.digits_ = digits;
    while (sum.digits_.size() > 1) {
        if (sum.digits_.back() == '0') {
            sum.digits_.pop_back();
        } else {
            break;
        }
    }
    if (digits == "0") {
        sum.positive_ = true;
    }

    return sum;
}

BigInt operator+(const BigInt &lhs, const int &rhs) {
    BigInt rhs_big_int(rhs);
    return lhs + rhs_big_int;
}

BigInt operator+(const int &lhs, const BigInt &rhs) {
    BigInt lhs_big_int(lhs);
    return lhs_big_int + rhs;
}

BigInt &operator+=(BigInt &lhs, const BigInt &rhs) {
    lhs = lhs + rhs;
    return lhs;
}

BigInt &operator+=(BigInt &lhs, const int &rhs) {
    lhs = lhs + rhs;
    return lhs;
}

BigInt operator-(const BigInt &lhs, const BigInt &rhs) {
    if (lhs.positive_ != rhs.positive_) {
        return lhs + -rhs;
    } else if (abs(lhs) < abs(rhs)) {
        return -(rhs - lhs);
    }

    int max_size = std::max(lhs.digits_.size(), rhs.digits_.size());
    std::string digits(max_size, '0');

    for (int i_digit = 0; i_digit < max_size; ++i_digit) {
        if (i_digit < lhs.digits_.size()) {
            digits[i_digit] += lhs.digits_[i_digit] - '0';
        }
        if (i_digit < rhs.digits_.size()) {
            digits[i_digit] -= rhs.digits_[i_digit] - '0';
        }

        if (digits[i_digit] < '0') {
            --digits[i_digit + 1];
            digits[i_digit] += 10;
        }
    }

    BigInt difference;
    difference.positive_ = lhs.positive_;
    difference.digits_ = digits;
    while (difference.digits_.size() > 1) {
        if (difference.digits_.back() == '0') {
            difference.digits_.pop_back();
        } else {
            break;
        }
    }
    if (difference.digits_ == "0") {
        difference.positive_ = true;
    }

    return difference;
}

BigInt operator-(const BigInt &lhs, const int &rhs) {
    BigInt rhs_big_int(rhs);
    return lhs + rhs_big_int;
}

BigInt operator-(const int &lhs, const BigInt &rhs) {
    BigInt lhs_big_int(lhs);
    return lhs_big_int - rhs;
}

BigInt &operator-=(BigInt &lhs, const BigInt &rhs) {
    lhs = lhs - rhs;
    return lhs;
}

BigInt &operator-=(BigInt &lhs, const int &rhs) {
    lhs = lhs - rhs;
    return lhs;
}

BigInt operator*(const BigInt &lhs, const BigInt &rhs) {
    if (rhs.digits_.size() > lhs.digits_.size()) {
        return rhs * lhs;
    } else if (rhs == 0) {
        return BigInt(0);
    }


    if (rhs.digits_.size() == 1) {
        std::string digits(lhs.digits_.size() + 1, '0');
        int rhs_int = rhs.digits_[0] - '0';

        for (int i_digit = 0; i_digit < lhs.digits_.size(); ++i_digit) {
            int temp_digit = digits[i_digit] - '0'
                + (lhs.digits_[i_digit] - '0') * rhs_int;
            digits[i_digit + 1] += temp_digit / 10;
            digits[i_digit] = temp_digit % 10 + '0';
        }

        BigInt product;
        product.positive_ = lhs.positive_ == rhs.positive_;
        product.digits_ = digits;
        while (product.digits_.size() > 1) {
            if (product.digits_.back() == '0') {
                product.digits_.pop_back();
            } else {
                break;
            }
        }
        if (product.digits_ == "0") {
            product.positive_ = true;
        }

        return product;
    } else {
        BigInt product(0);
        for (int i_digit = 0; i_digit < rhs.digits_.size(); ++i_digit) {
            BigInt unit_product = lhs * (rhs.digits_[i_digit] - '0');
            unit_product.digits_ =
                std::string(i_digit, '0') + unit_product.digits_;
            product += abs(unit_product);
        }
        if (lhs.positive_ != rhs.positive_) {
            product = -product;
        }

        return product;
    }
}

BigInt operator*(const BigInt &lhs, const int &rhs) {
    BigInt rhs_big_int(rhs);
    return lhs * rhs_big_int;
}

BigInt operator*(const int &lhs, const BigInt &rhs) {
    BigInt lhs_big_int(lhs);
    return lhs_big_int * rhs;
}

BigInt &operator*=(BigInt &lhs, const BigInt &rhs) {
    lhs = lhs * rhs;
    return lhs;
}

BigInt &operator*=(BigInt &lhs, const int &rhs) {
    lhs = lhs * rhs;
    return lhs;
}

BigInt operator/(const BigInt &lhs, const BigInt &rhs) {
    if (rhs == 0) {
        throw std::runtime_error("Cannot divide a BigInt by 0");
    }

    BigInt remainder = abs(lhs);
    BigInt quotient(0);
    int n_zeros(static_cast<int>(lhs.digits_.size() - rhs.digits_.size()));

    while (remainder >= abs(rhs)) {
        BigInt temp_lhs = remainder;
        std::string temp_digits = temp_lhs.digits_;
        temp_lhs.digits_ =
            temp_digits.substr(n_zeros, temp_digits.size());
        for (int i = 0; i < 10; ++i) {
            if (abs(rhs) * (i + 1) > temp_lhs) {
                BigInt temp_quotient;
                temp_quotient.digits_ = std::string(n_zeros, '0');
                temp_quotient.digits_.push_back(i + '0');

                while (temp_quotient.digits_.size() > 1) {
                    if (temp_quotient.digits_.back() == '0') {
                        temp_quotient.digits_.pop_back();
                    } else {
                        break;
                    }
                }
                if (temp_quotient.digits_ == "0") {
                    temp_quotient.positive_ = true;
                }

                quotient += temp_quotient;
                remainder -= temp_quotient * abs(rhs);

                break;
            }
        }
        --n_zeros;
    }
    quotient.positive_ = lhs.positive_ == rhs.positive_ or quotient == 0;

    return quotient;
}

BigInt operator/(const BigInt &lhs, const int &rhs) {
    BigInt rhs_big_int(rhs);
    return lhs / rhs_big_int;
}

BigInt operator/(const int &lhs, const BigInt &rhs) {
    BigInt lhs_big_int(lhs);
    return lhs_big_int / rhs;
}

BigInt operator%(const BigInt &lhs, const BigInt &rhs) {
    return (lhs - lhs / rhs * rhs)
        * (lhs.positive_ == rhs.positive_ ? 1 : -1);
}

BigInt operator%(const BigInt &lhs, const int &rhs) {
    BigInt rhs_big_int(rhs);
    return lhs % rhs_big_int;
}

BigInt operator%(const int &lhs, const BigInt &rhs) {
    BigInt lhs_big_int(lhs);
    return lhs_big_int % rhs;
}
}