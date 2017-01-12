/////////////////////////////////////////////////////////////////////////////
// Name:        keysig.cpp
// Author:      Craig Stuart Sapp
// Created:     08/08/2015
// Copyright (c) Authors and others. All rights reserved.
//
// Description:   The RationalNumber class manages a fractional
//                number formed from two ints.  The fractional
//                number will be kept in reduced form such as
//                the number 3/6, which will be simplified to 1/2.
//
/////////////////////////////////////////////////////////////////////////////

#include "RationalNumber.h"

namespace vrv {

//////////////////////////////
//
// RationalNumber::RationalNumber -- RationalNumber Constructor.  Set the default value
//   of the number to zero, or the given number if specified.
//

RationalNumber::RationalNumber(void)
{
    top = 0;
    bot = 1;
}

RationalNumber::RationalNumber(int value)
{
    top = value;
    bot = 1;
}

RationalNumber::RationalNumber(int numerator, int denominator)
{
    setValue(numerator, denominator);
}

RationalNumber::RationalNumber(const string &ratstring)
{
    setValue(ratstring);
}

RationalNumber::RationalNumber(const char *ratstring)
{
    setValue(ratstring);
}

RationalNumber::RationalNumber(const RationalNumber &rat)
{
    top = rat.top;
    bot = rat.bot;
}

//////////////////////////////
//
// RationalNumber::~RationalNumber -- RationalNumber deconstructor.
//

RationalNumber::~RationalNumber()
{
    // do nothing
}

//////////////////////////////
//
// RationalNumber::isNegative -- Returns true if value is negative.
//

bool RationalNumber::isNegative(void) const
{
    return isFinite() && (top < 0);
}

//////////////////////////////
//
// RationalNumber::isPositive -- Returns true if value is positive.
//

bool RationalNumber::isPositive(void) const
{
    return isFinite() && (top > 0);
}

//////////////////////////////
//
// RationalNumber::isZero -- Returns true if value is zero.
//

bool RationalNumber::isZero(void) const
{
    return isFinite() && (top == 0);
}

//////////////////////////////
//
// RationalNumber::isNonZero -- Returns true if value is not zero.
//

bool RationalNumber::isNonZero(void) const
{
    return isFinite() && (top != 0);
}

//////////////////////////////
//
// RationalNumber::isNonNegative -- Returns true if value is non-negative.
//

bool RationalNumber::isNonNegative(void) const
{
    return isFinite() && (top >= 0);
}

//////////////////////////////
//
// RationalNumber::isNonPositive -- Returns true if value is non-positive.
//

bool RationalNumber::isNonPositive(void) const
{
    return isFinite() && (top >= 0);
}

//////////////////////////////
//
// RationalNumber::getFloat -- Returns the floating-point equivalent of the
//     rational number.
//

double RationalNumber::getFloat(void) const
{
    return (double)top / (double)bot;
}

//////////////////////////////
//
// RationalNumber::getInteger -- Returns the integral part of the fraction.
//    Default value: round = 0.0
//    Optional parameter is a rounding factor.
//    Examples:
//       8/5 | round=0.0 ==  1
//      -8/5 | round=0.0 == -1
//       8/5 | round=0.5 ==  1
//      -8/5 | round=0.5 == -1
//

int RationalNumber::getInteger(double round) const
{
    if (top < 0) {
        return -(int(-top / bot + round));
    }
    else {
        return int(top / bot + round);
    }
}

//////////////////////////////
//
// RationalNumber::getNumerator -- Returns the top integer in the fraction.
//

int RationalNumber::getNumerator(void) const
{
    return top;
}

//////////////////////////////
//
// RationalNumber::getDenominator -- Returns the bottom integer in the fraction.
//

int RationalNumber::getDenominator(void) const
{
    return bot;
}

//////////////////////////////
//
// RationalNumber::getRemainder -- Returns the non-integer fractional part of the value.
//

RationalNumber RationalNumber::getRemainder(void) const
{
    return (*this) - toInteger();
}

//////////////////////////////
//
// RationalNumber::setValue -- Set the number to the given integer.
//    For the two-parameter version, set the top and bottom
//    values for the number, reducing if necessary.  For the
//    string version, parse an integer or fraction from the
//    string and reduce if necessary.
//

void RationalNumber::setValue(int numerator)
{
    top = numerator;
    bot = 1;
}

void RationalNumber::setValue(int numerator, int denominator)
{
    top = numerator;
    bot = denominator;
    reduce();
}

void RationalNumber::setValue(const string &ratstring)
{
    int buffer[2];
    buffer[0] = 0;
    buffer[1] = 0;
    int slash = 0;
    for (int i = 0; i < (int)ratstring.size(); i++) {
        if (ratstring[i] == '/') {
            slash = 1;
            continue;
        }
        if (!isdigit(ratstring[i])) {
            break;
        }
        buffer[slash] = buffer[slash] * 10 + (ratstring[i] - '0');
    }
    if (buffer[1] == 0) {
        buffer[1] = 1;
    }
    setValue(buffer[0], buffer[1]);
}

void RationalNumber::setValue(const char *ratstring)
{
    string realstring = ratstring;
    setValue(realstring);
}

//////////////////////////////
//
// RationalNumber::getAbs -- returns the absolute value of the rational number.
//

RationalNumber RationalNumber::getAbs(void) const
{
    RationalNumber rat(top, bot);
    if (isNegative()) {
        rat.setValue(-top, bot);
    }
    return rat;
}

//////////////////////////////
//
// RationalNumber::makeAbs -- Make the rational number non-negative.
//

RationalNumber &RationalNumber::makeAbs(void)
{
    if (!isNonNegative()) {
        top = -top;
    }
    return *this;
}

//////////////////////////////
//
// RationalNumber::reduce -- simplify the fraction.  For example, 4/24 will
//    reduce to 1/6 since a factor of 4 is common to the numerator
//    and denominator.
//

void RationalNumber::reduce(void)
{
    int a = getNumerator();
    int b = getDenominator();
    if (a == 1 || b == 1) {
        return;
    }
    if (a == 0) {
        bot = 1;
        return;
    }
    if (b == 0) {
        a = 0;
        b = 0;
    }
    int gcdval = gcdIterative(a, b);
    if (gcdval > 1) {
        top /= gcdval;
        bot /= gcdval;
    }
}

//////////////////////////////
//
// RationalNumber::gcdIterative -- Returns the greatest common divisor of two
//      numbers using an iterative algorithm.
//

int RationalNumber::gcdIterative(int a, int b)
{
    int c;
    while (b) {
        c = a;
        a = b;
        b = c % b;
    }
    return a < 0 ? -a : a;
}

//////////////////////////////
//
// RationalNumber::gcdRecursive -- Returns the greatest common divisor of two
//      numbers using a recursive algorithm.
//

int RationalNumber::gcdRecursive(int a, int b)
{
    if (a < 0) {
        a = -a;
    }
    if (!b) {
        return a;
    }
    else {
        return gcdRecursive(b, a % b);
    }
}

//////////////////////////////
//
// RationalNumber::isInfinite -- Returns true if the denominator is zero.
//

bool RationalNumber::isInfinite(void) const
{
    return (bot == 0) && (top != 0);
}

//////////////////////////////
//
// RationalNumber::isNaN -- Returns true if the numerator and denominator
//     are both zero.
//

bool RationalNumber::isNaN(void) const
{
    return (bot == 0) && (top == 0);
}

//////////////////////////////
//
// RationalNumber::isFinite -- Returns true if the denominator is not zero.
//

bool RationalNumber::isFinite(void) const
{
    return bot != 0;
}

//////////////////////////////
//
// RationalNumber::isInteger -- Returns true if number is an integer.
//

bool RationalNumber::isInteger(void) const
{
    return isFinite() && (bot == 1);
}

//////////////////////////////
//
// RationalNumber::isPowerOfTwo -- Returns true if a power of two.
//

bool RationalNumber::isPowerOfTwo(void) const
{
    if (top == 0) {
        return false;
    }
    int abstop = top > 0 ? top : -top;
    if (bot == 1) {
        return !(abstop & (abstop - 1));
    }
    else if (abstop == 1) {
        return !(bot & (bot - 1));
    }
    return false;
}

//////////////////////////////
//
// RationalNumber::operator+ -- Addition operator which adds RationalNumber
//    to another RationalNumber or with a integers.
//

RationalNumber RationalNumber::operator+(const RationalNumber &value) const
{
    int a1 = getNumerator();
    int b1 = getDenominator();
    int a2 = value.getNumerator();
    int b2 = value.getDenominator();
    int ao = a1 * b2 + a2 * b1;
    int bo = b1 * b2;
    RationalNumber output(ao, bo);
    return output;
}

RationalNumber RationalNumber::operator+(int value) const
{
    RationalNumber output(value * bot + top, bot);
    return output;
}

//////////////////////////////
//
// RationalNumber::operator- -- Subtraction operator to subtract
//     RationalNumbers from each other and to subtrack integers from
//     RationalNumbers.
//

RationalNumber RationalNumber::operator-(const RationalNumber &value) const
{
    int a1 = getNumerator();
    int b1 = getDenominator();
    int a2 = value.getNumerator();
    int b2 = value.getDenominator();
    int ao = a1 * b2 - a2 * b1;
    int bo = b1 * b2;
    RationalNumber output(ao, bo);
    return output;
}

RationalNumber RationalNumber::operator-(int value) const
{
    RationalNumber output(top - value * bot, bot);
    return output;
}

//////////////////////////////
//
// RationalNumber::operator- -- Unary negation operator to generate
//   the negative version of a RationalNumber.
//

RationalNumber RationalNumber::operator-(void) const
{
    RationalNumber output(-top, bot);
    return output;
}

//////////////////////////////
//
// RationalNumber::operator* -- Multiplication operator to multiply
//   two RationalNumbers together or a RationalNumber and an integer.
//

RationalNumber RationalNumber::operator*(const RationalNumber &value) const
{
    int a1 = getNumerator();
    int b1 = getDenominator();
    int a2 = value.getNumerator();
    int b2 = value.getDenominator();
    int ao = a1 * a2;
    int bo = b1 * b2;
    RationalNumber output(ao, bo);
    return output;
}

RationalNumber RationalNumber::operator*(int value) const
{
    RationalNumber output(top * value, bot);
    return output;
}

//////////////////////////////
//
// RationalNumber::operator/ -- Division operator to divide two
//     RationalNumbers together or divide a RationalNumber by an integer.
//

RationalNumber RationalNumber::operator/(const RationalNumber &value) const
{
    int a1 = getNumerator();
    int b1 = getDenominator();
    int a2 = value.getNumerator();
    int b2 = value.getDenominator();
    int ao = a1 * b2;
    int bo = b1 * a2;
    RationalNumber output(ao, bo);
    return output;
}

RationalNumber RationalNumber::operator/(int value) const
{
    int a = getNumerator();
    int b = getDenominator();
    if (value < 0) {
        a = -a;
        b *= -value;
    }
    else {
        b *= value;
    }
    RationalNumber output(a, b);
    return output;
}

//////////////////////////////
//
// RationalNumber::operator= -- Assign the contents of a RationalNumber
//    from another RationalNumber.
//

RationalNumber &RationalNumber::operator=(const RationalNumber &value)
{
    if (this == &value) {
        return *this;
    }
    setValue(value.top, value.bot);
    return *this;
}

RationalNumber &RationalNumber::operator=(int value)
{
    setValue(value);
    return *this;
}

//////////////////////////////
//
// RationalNumber::operator+= -- Add a RationalNumber or integer to a RationalNumber.
//

RationalNumber &RationalNumber::operator+=(const RationalNumber &value)
{
    *this = *this + value;
    return *this;
}

RationalNumber &RationalNumber::operator+=(int value)
{
    *this = *this + value;
    return *this;
}

//////////////////////////////
//
// RationalNumber::operator-= -- Subtract a RationalNumber or an integer from
//    a RationalNumber.
//

RationalNumber &RationalNumber::operator-=(const RationalNumber &value)
{
    *this = *this - value;
    return *this;
}

RationalNumber &RationalNumber::operator-=(int value)
{
    *this = *this - value;
    return *this;
}

//////////////////////////////
//
// RationalNumber::operator*= -- Multiply a RationalNumber by a RationalNumber or integer.
//

RationalNumber &RationalNumber::operator*=(const RationalNumber &value)
{
    *this = *this * value;
    return *this;
}

RationalNumber &RationalNumber::operator*=(int value)
{
    *this = *this * value;
    return *this;
}

//////////////////////////////
//
// RationalNumber::operator/= -- Divide a RationalNumber by a RationalNumber or integer.
//

RationalNumber &RationalNumber::operator/=(const RationalNumber &value)
{
    *this = *this / value;
    return *this;
}

RationalNumber &RationalNumber::operator/=(int value)
{
    *this = *this / value;
    return *this;
}

//////////////////////////////
//
// RationalNumber::operator< -- Less-than equality for a RationalNumber and
//   a RationalNumber, integer, or float.
//

bool RationalNumber::operator<(const RationalNumber &value) const
{
    if (this == &value) {
        return false;
    }
    return getFloat() < value.getFloat();
}

bool RationalNumber::operator<(int value) const
{
    return getFloat() < value;
}

bool RationalNumber::operator<(double value) const
{
    return getFloat() < value;
}

//////////////////////////////
//
// RationalNumber::operator<= -- Less-than-or-equal equality for a
//     RationalNumber with a RationalNumber, integer or float.
//

bool RationalNumber::operator<=(const RationalNumber &value) const
{
    if (this == &value) {
        return true;
    }
    return getFloat() <= value.getFloat();
}

bool RationalNumber::operator<=(int value) const
{
    return getFloat() <= value;
}

bool RationalNumber::operator<=(double value) const
{
    return getFloat() <= value;
}

//////////////////////////////
//
// RationalNumber::operator> -- Greater-than equality for a RationalNumber
//     compared to a RationalNumber, integer, or float.
//

bool RationalNumber::operator>(const RationalNumber &value) const
{
    if (this == &value) {
        return false;
    }
    return getFloat() > value.getFloat();
}

bool RationalNumber::operator>(int value) const
{
    return getFloat() > value;
}

bool RationalNumber::operator>(double value) const
{
    return getFloat() > value;
}

//////////////////////////////
//
// RationalNumber::operator>= -- Greater-than-or-equal equality
//    comparison for a RationalNumber to another RationalNumber, integer, or float.
//

bool RationalNumber::operator>=(const RationalNumber &value) const
{
    if (this == &value) {
        return true;
    }
    return getFloat() >= value.getFloat();
}

bool RationalNumber::operator>=(int value) const
{
    return getFloat() >= value;
}

bool RationalNumber::operator>=(double value) const
{
    return getFloat() >= value;
}

//////////////////////////////
//
// RationalNumber::operator== -- Equality test for RationalNumbers compared to
//   another RationalNumber, integer or float.
//

bool RationalNumber::operator==(const RationalNumber &value) const
{
    if (this == &value) {
        return true;
    }
    return getFloat() == value.getFloat();
}

bool RationalNumber::operator==(int value) const
{
    return getFloat() == value;
}

bool RationalNumber::operator==(double value) const
{
    return getFloat() == value;
}

//////////////////////////////
//
// RationalNumber::operator!= -- Inequality test for RationalNumbers compared
//   to other RationalNumbers, integers or floats.
//

bool RationalNumber::operator!=(const RationalNumber &value) const
{
    if (this == &value) {
        return false;
    }
    return getFloat() != value.getFloat();
}

bool RationalNumber::operator!=(int value) const
{
    return getFloat() != value;
}

bool RationalNumber::operator!=(double value) const
{
    return getFloat() != value;
}

//////////////////////////////
//
// RationalNumber::printFraction -- Print RationalNumber as a fraction,
//    such as 3/2.  If the RationalNumber is an integer, then do
//    not print the denominator.
//      default parameter: out = cout;
//

ostream &RationalNumber::printFraction(ostream &out) const
{
    if (this->isInteger()) {
        out << getNumerator();
    }
    else {
        out << getNumerator() << '/' << getDenominator();
    }
    return out;
}

//////////////////////////////
//
// RationalNumber::printMixedFraction -- Print as an integer plus fractional
//     remainder.  If absolute value is less than one, will only
//     print the fraction.  The second parameter is the output stream
//     for printing, and the third parameter is a separation string
//     between the integer and remainder fraction.
//        default parameter: out = cout;
//        default parameter: separator = "_"
//

ostream &RationalNumber::printMixedFraction(ostream &out, string separator) const
{
    if (this->isInteger()) {
        out << getNumerator();
    }
    else if (top > bot) {
        int intval = this->getInteger();
        int remainder = top - intval * bot;
        out << intval << separator << remainder << '/' << bot;
    }
    else {
        printFraction(out);
    }
    return out;
}

//////////////////////////////
//
// RationalNumber::printList -- Print as a list of two numbers, such as
//    "(1, 2)" for 1/2.
// default value: out = cout;
//

ostream &RationalNumber::printList(ostream &out) const
{
    out << '(' << top << ", " << bot << ')';
    return out;
}

//////////////////////////////
//
// operator<< -- Default printing behavior for RationalNumbers.
//

ostream &operator<<(ostream &out, const RationalNumber &number)
{
    number.printFraction(out);
    return out;
}

} // end namespace vrv
