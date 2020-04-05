//
// Created by Joshua2018 on 2020/4/2.
//

#ifndef HW_1__BIGINT_H_
#define HW_1__BIGINT_H_

#include <string>

namespace ben_birdland {
class BigInt {
public:
    BigInt();
    explicit BigInt(int integer);
    explicit BigInt(const std::string &big_int_string);
    BigInt(const BigInt &other);

    BigInt &operator=(const BigInt &other);
    BigInt &operator=(int other_int);
    friend BigInt operator-(const BigInt &other);
    friend BigInt abs(const BigInt &other);

    friend std::ostream &operator<<(std::ostream &ostream, const BigInt &big_int);

    friend bool operator==(const BigInt &lhs, const BigInt &rhs);
    friend bool operator==(const BigInt &lhs, const int &rhs);
    friend bool operator==(const int &lhs, const BigInt &rhs);

    friend bool operator!=(const BigInt &lhs, const BigInt &rhs);
    friend bool operator!=(const BigInt &lhs, const int &rhs);
    friend bool operator!=(const int &lhs, const BigInt &rhs);

    friend bool operator<(const BigInt &lhs, const BigInt &rhs);
    friend bool operator<(const BigInt &lhs, const int &rhs);
    friend bool operator<(const int &lhs, const BigInt &rhs);

    friend bool operator>(const BigInt &lhs, const BigInt &rhs);
    friend bool operator>(const BigInt &lhs, const int &rhs);
    friend bool operator>(const int &lhs, const BigInt &rhs);

    friend bool operator<=(const BigInt &lhs, const BigInt &rhs);
    friend bool operator<=(const BigInt &lhs, const int &rhs);
    friend bool operator<=(const int &lhs, const BigInt &rhs);

    friend bool operator>=(const BigInt &lhs, const BigInt &rhs);
    friend bool operator>=(const BigInt &lhs, const int &rhs);
    friend bool operator>=(const int &lhs, const BigInt &rhs);

    friend BigInt operator+(const BigInt &lhs, const BigInt &rhs);
    friend BigInt operator+(const BigInt &lhs, const int &rhs);
    friend BigInt operator+(const int &lhs, const BigInt &rhs);

    friend BigInt &operator+=(BigInt &lhs, const BigInt &rhs);
    friend BigInt &operator+=(BigInt &lhs, const int &rhs);

    friend BigInt operator-(const BigInt &lhs, const BigInt &rhs);
    friend BigInt operator-(const BigInt &lhs, const int &rhs);
    friend BigInt operator-(const int &lhs, const BigInt &rhs);

    friend BigInt &operator-=(BigInt &lhs, const BigInt &rhs);
    friend BigInt &operator-=(BigInt &lhs, const int &rhs);

    friend BigInt operator*(const BigInt &lhs, const BigInt &rhs);
    friend BigInt operator*(const BigInt &lhs, const int &rhs);
    friend BigInt operator*(const int &lhs, const BigInt &rhs);

    friend BigInt &operator*=(BigInt &lhs, const BigInt &rhs);
    friend BigInt &operator*=(BigInt &lhs, const int &rhs);

    friend BigInt operator/(const BigInt &lhs, const BigInt &rhs);
    friend BigInt operator/(const BigInt &lhs, const int &rhs);
    friend BigInt operator/(const int &lhs, const BigInt &rhs);

    friend BigInt operator%(const BigInt &lhs, const BigInt &rhs);
    friend BigInt operator%(const BigInt &lhs, const int &rhs);
    friend BigInt operator%(const int &lhs, const BigInt &rhs);

private:
    bool positive_;
    std::string digits_;
};
}
#endif //HW_1__BIGINT_H_
