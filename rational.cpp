#include "rational.h"

Rational GetRational(int64_t& numerator, int64_t& denominator) {
    if (numerator == 0) {
        return Rational(0, 1);
    }

    if (denominator < 0) {
        numerator *= -1;
        denominator *= -1;
    }

    int64_t gcd = std::gcd(numerator, denominator);

    return Rational(static_cast<int>(numerator / gcd), static_cast<int>(denominator / gcd));
}

Rational::Rational() {
    numer_ = 0;
    denom_ = 1;
}

Rational::Rational(int val) {
    numer_ = val;
    denom_ = 1;
}

Rational::Rational(int numer, int denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }

    Set(static_cast<int64_t>(numer), static_cast<int64_t>(denom));
}

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {
    Set(static_cast<int64_t>(value), static_cast<int64_t>(denom_));
}

void Rational::SetDenominator(int value) {
    Set(static_cast<int64_t>(numer_), static_cast<int64_t>(value));
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int64_t numerator = static_cast<int64_t>(lhs.GetNumerator()) * (rhs.GetDenominator());
    numerator += static_cast<int64_t>(lhs.GetDenominator()) * rhs.GetNumerator();
    int64_t denominator = static_cast<int64_t>(lhs.GetDenominator()) * rhs.GetDenominator();

    return GetRational(numerator, denominator);
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    int64_t numerator = static_cast<int64_t>(lhs.GetNumerator()) * rhs.GetDenominator();
    numerator -= static_cast<int64_t>(lhs.GetDenominator()) * rhs.GetNumerator();
    int64_t denominator = static_cast<int64_t>(lhs.GetDenominator()) * rhs.GetDenominator();

    return GetRational(numerator, denominator);
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    int64_t numerator = static_cast<int64_t>(lhs.GetNumerator()) * static_cast<int64_t>(rhs.GetNumerator());
    int64_t denominator = static_cast<int64_t>(lhs.GetDenominator()) * static_cast<int64_t>(rhs.GetDenominator());

    return GetRational(numerator, denominator);
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    if (rhs.GetNumerator() == 0) {
        throw RationalDivisionByZero{};
    }

    int64_t numerator = static_cast<int64_t>(lhs.GetNumerator()) * static_cast<int64_t>(rhs.GetDenominator());
    int64_t denominator = static_cast<int64_t>(lhs.GetDenominator()) * static_cast<int64_t>(rhs.GetNumerator());

    return GetRational(numerator, denominator);
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int64_t numerator = static_cast<int64_t>(lhs.GetNumerator()) * (rhs.GetDenominator());
    numerator += static_cast<int64_t>(lhs.GetDenominator()) * rhs.GetNumerator();
    int64_t denominator = static_cast<int64_t>(lhs.GetDenominator()) * rhs.GetDenominator();

    lhs.Set(numerator, denominator);
    return lhs;
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    lhs += (-rhs);
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs = lhs * rhs;
    return lhs;
}

Rational& operator++(Rational& ratio) {
    ratio.numer_ += ratio.denom_;
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio.numer_ -= ratio.denom_;
    return ratio;
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    int64_t numerator = 0;
    int64_t denominator = 1;
    is >> numerator;
    if (is.peek() == '/') {
        char division_symbol = '/';
        is >> division_symbol >> denominator;
        ratio.Set(numerator, denominator);
    } else {
        ratio.Set(numerator, denominator);
    }

    return is;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    if (rhs.GetNumerator() == 0) {
        throw RationalDivisionByZero{};
    }
    lhs = lhs / rhs;
    return lhs;
}

Rational operator++(Rational& ratio, int) {
    Rational old_ratio(ratio.GetNumerator(), ratio.GetDenominator());
    ratio.SetNumerator(ratio.GetNumerator() + ratio.GetDenominator());

    return old_ratio;
}

Rational operator--(Rational& ratio, int) {
    Rational old_ratio(ratio.GetNumerator(), ratio.GetDenominator());
    ratio.SetNumerator(ratio.GetNumerator() - ratio.GetDenominator());

    return old_ratio;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return static_cast<int64_t>(lhs.GetNumerator()) * static_cast<int64_t>(rhs.GetDenominator()) <
           static_cast<int64_t>(rhs.GetNumerator()) * static_cast<int64_t>(lhs.GetDenominator());
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return rhs < lhs;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs.GetNumerator() == rhs.GetNumerator() && lhs.GetDenominator() == rhs.GetDenominator());
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return (lhs < rhs || lhs == rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return (lhs > rhs || lhs == rhs);
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    if (ratio.GetDenominator() == 1) {
        os << ratio.GetNumerator();
    } else {
        os << ratio.GetNumerator() << "/" << ratio.GetDenominator();
    }
    return os;
}

Rational operator+(const Rational& ratio) {
    return ratio;
}

Rational operator-(const Rational& ratio) {
    if (ratio.GetNumerator() == 0) {
        return ratio;
    } else {
        return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
    }
}

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }

    if (numer == 0) {
        numer_ = 0;
        denom_ = 1;
    } else {
        if (denom < 0) {
            denom *= -1;
            numer *= -1;
        }
        int64_t gcd = std::gcd(numer, denom);
        numer_ = static_cast<int>(numer / gcd);
        denom_ = static_cast<int>(denom / gcd);
    }
}
