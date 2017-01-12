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

#ifndef __VRV_RATIONALNUMBER_H__
#define __VRV_RATIONALNUMBER_H__

#include <iostream>
#include <vector>

using namespace std;

namespace vrv {

class RationalNumber {
public:
    RationalNumber(void);
    RationalNumber(int value);
    RationalNumber(int numerator, int denominator);
    RationalNumber(const RationalNumber &rat);
    RationalNumber(const string &ratstring);
    RationalNumber(const char *ratstring);
    ~RationalNumber();

    bool isNegative(void) const;
    bool isPositive(void) const;
    bool isZero(void) const;
    bool isNonZero(void) const;
    bool isNonNegative(void) const;
    bool isNonPositive(void) const;
    bool isInfinite(void) const;
    bool isFinite(void) const;
    bool isNaN(void) const;
    bool isInteger(void) const;
    bool isPowerOfTwo(void) const;
    double getFloat(void) const;
    double toFloat(void) const { return getFloat(); }
    int getInteger(double round = 0.0) const;
    int toInteger(double round = 0.0) const { return getInteger(round); }
    int getNumerator(void) const;
    int getDenominator(void) const;
    RationalNumber getRemainder(void) const;
    void setValue(int numerator);
    void setValue(int numerator, int denominator);
    void setValue(const string &ratstring);
    void setValue(const char *ratstring);
    RationalNumber getAbs(void) const;
    RationalNumber &makeAbs(void);
    RationalNumber &operator=(const RationalNumber &value);
    RationalNumber &operator=(int value);
    RationalNumber &operator+=(const RationalNumber &value);
    RationalNumber &operator+=(int value);
    RationalNumber &operator-=(const RationalNumber &value);
    RationalNumber &operator-=(int value);
    RationalNumber &operator*=(const RationalNumber &value);
    RationalNumber &operator*=(int value);
    RationalNumber &operator/=(const RationalNumber &value);
    RationalNumber &operator/=(int value);
    RationalNumber operator-(void) const;
    RationalNumber operator+(const RationalNumber &value) const;
    RationalNumber operator+(int value) const;
    RationalNumber operator-(const RationalNumber &value) const;
    RationalNumber operator-(int value) const;
    RationalNumber operator*(const RationalNumber &value) const;
    RationalNumber operator*(int value) const;
    RationalNumber operator/(const RationalNumber &value) const;
    RationalNumber operator/(int value) const;
    bool operator==(const RationalNumber &value) const;
    bool operator==(double value) const;
    bool operator==(int value) const;
    bool operator!=(const RationalNumber &value) const;
    bool operator!=(double value) const;
    bool operator!=(int value) const;
    bool operator<(const RationalNumber &value) const;
    bool operator<(double value) const;
    bool operator<(int value) const;
    bool operator<=(const RationalNumber &value) const;
    bool operator<=(double value) const;
    bool operator<=(int value) const;
    bool operator>(const RationalNumber &value) const;
    bool operator>(double value) const;
    bool operator>(int value) const;
    bool operator>=(const RationalNumber &value) const;
    bool operator>=(double value) const;
    bool operator>=(int value) const;
    ostream &printFraction(ostream & = cout) const;
    ostream &printMixedFraction(ostream &out = cout, string separator = "_") const;
    ostream &printList(ostream &out) const;

protected:
    void reduce(void);
    int gcdIterative(int a, int b);
    int gcdRecursive(int a, int b);

private:
    int top;
    int bot;
};

ostream &operator<<(ostream &out, const RationalNumber &number);

template <typename A> ostream &operator<<(ostream &out, const vector<A> &v);

} // end namespace vrv

#endif
