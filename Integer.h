// --------------------------
// projects/integer/Integer.h
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------

#ifndef Integer_h
#define Integer_h

// --------
// includes
// --------

#include <cassert> // assert
#include <iostream> // ostream
#include <stdexcept> // invalid_argument
#include <string> // string
#include <vector> // vector
#include <deque> // deque

using namespace std;

// -----------------
// shift_left_digits
// ----------------- 

/**
 * @param b an iterator to the beginning of an input sequence (inclusive)
 * @param e an iterator to the end of an input sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return an iterator to the end of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift left of the input sequence into the output sequence
 * ([b, e) << n) => x
 */
template <typename II, typename OI>
OI shift_left_digits (II b, II e, int n, OI x) {
    // <your code>
    while (b != e) {
        *x = *b;
        ++b;
        ++x;
    }
    while (n != 0) {
        *x = 0;
        ++x;
        --n;
    }
    return x;}

// ------------------
// shift_right_digits
// ------------------

/**
 * @param b an iterator to the beginning of an input sequence (inclusive)
 * @param e an iterator to the end of an input sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return an iterator to the end of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift right of the input sequence into the output sequence
 * ([b, e) >> n) => x
 */
template <typename II, typename OI>
OI shift_right_digits (II b, II e, int n, OI x) {
    // <your code>
    int size = e - b;
    n = size - n;
    if (n > 0) {
        while (n != 0) {
            *x = *b;
            ++b;
            ++x;
            --n;
        }
    }
    else
        *x = 0; 

    return x;}

// -----------
// plus_digits
// -----------

/**
 * @param b an iterator to the beginning of an input sequence (inclusive)
 * @param e an iterator to the end of an input sequence (exclusive)
 * @param b2 an iterator to the beginning of an input sequence (inclusive)
 * @param e2 an iterator to the end of an input sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return an iterator to the end of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the sum of the two input sequences into the output sequence
 * ([b1, e1) + [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI plus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    // <your code>
    *x = 0;
    int size1 = e1 - b1;
    int size2 = e2 - b2;
    int sum = 0;
    if (size2 > size1) 
        x = plus_digits(b2, e2, b1, e1, x);
    else {
        while (size2 != 0) {
            --e1;
            --e2;
            sum += *e1 + *e2;
            *(x + size1) = sum % 10;
            sum /= 10;
            --size1;
            --size2;
        }
        while (size1 != 0) {
            --e1;
            sum += *e1;
            *(x + size1) = sum % 10;
            sum /= 10;
            --size1;
        }
        *(x + size1) = sum % 10;
    }
    // Check if largest digit addition carried over.
    if (*x == 0) 
        x = x + 1;
    return x;}

// ------------
// minus_digits
// ------------

/**
 * @param b an iterator to the beginning of an input sequence (inclusive)
 * @param e an iterator to the end of an input sequence (exclusive)
 * @param b2 an iterator to the beginning of an input sequence (inclusive)
 * @param e2 an iterator to the end of an input sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return an iterator to the end of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the difference of the two input sequences into the output sequence
 * ([b1, e1) - [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    // <your code>
    // Assume the first number is greater than or equal to the second
    int size1 = e1 - b1;
    int size2 = e2 - b2;
    int size = size1;
    int diff = 0;
    while (size2 != 0) {
        --e1;
        --e2;
        --size1;
        --size2;
        if (*e1 < *e2) {
            *e1 += 10;
            *(e1 - 1) -= 1;
        }
        diff = *e1 - *e2;
        *(x + size1) = diff;
    } 
    while (size1 != 0) {
        --e1;
        --size1;
        *(x + size1) = *e1;
    }  
    int i = 0;
    while (i < size) {
        if (*x == 0)
            x = x + 1;
        ++i;
    }
    return x;}

// -----------------
// multiplies_digits
// -----------------

/**
 * @param b an iterator to the beginning of an input sequence (inclusive)
 * @param e an iterator to the end of an input sequence (exclusive)
 * @param b2 an iterator to the beginning of an input sequence (inclusive)
 * @param e2 an iterator to the end of an input sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return an iterator to the end of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the product of the two input sequences into the output sequence
 * ([b1, e1) * [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI multiplies_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    // <your code>
    int size1 = e1 - b1;
    int size2 = e2 - b2;
    int product = 0;
    while (size2 != 0)
    return x;}


// --------------
// divides_digits
// --------------

/**
 * @param b an iterator to the beginning of an input sequence (inclusive)
 * @param e an iterator to the end of an input sequence (exclusive)
 * @param b2 an iterator to the beginning of an input sequence (inclusive)
 * @param e2 an iterator to the end of an input sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return an iterator to the end of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the division of the two input sequences into the output sequence
 * ([b1, e1) / [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    // <your code>
    return x;}

// -------
// Integer
// -------

template < typename T, typename C = std::vector<T> >
class Integer {
    // -----------
    // operator ==
    // -----------

    /**
     * @param lhs an Integer on the left hand side of operator
     * @param rhs an Integer on the right hand side of operator
     * @return true if equal or false if not equal
     * (lhs == rhs) => true or false
     */
    friend bool operator == (const Integer& lhs, const Integer& rhs) {
        // <your code>
        if (lhs.size == rhs.size && lhs.is_negative == rhs.is_negative) {
            for (int i = 0; i < lhs.size; i++) {
                if (lhs.digit_deque[i] != rhs.digit_deque[i])
                    return false;
            }
            return true;
        } 
        return false;}

    // -----------
    // operator !=
    // -----------

    /**
     * @param lhs an Integer on the left hand side of operator
     * @param rhs an Integer on the right hand side of operator
     * @return true if not equal or true if equal
     * (lhs != rhs) => true or false
     */
    friend bool operator != (const Integer& lhs, const Integer& rhs) {
        return !(lhs == rhs);}

    // ----------
    // operator <
    // ----------

    /**
     * @param lhs an Integer on the left hand side of operator
     * @param rhs an Integer on the right hand side of operator
     * @return true if less than or false if greater or equal
     * (lhs < rhs) => true or false
     */
    friend bool operator < (const Integer& lhs, const Integer& rhs) {
        // <your code>
        
        return false;}

    // -----------
    // operator <=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator <= (const Integer& lhs, const Integer& rhs) {
        return !(rhs < lhs);}

    // ----------
    // operator >
    // ----------

    /**
     * <your documentation>
     */
    friend bool operator > (const Integer& lhs, const Integer& rhs) {
        return (rhs < lhs);}

    // -----------
    // operator >=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator >= (const Integer& lhs, const Integer& rhs) {
        return !(lhs < rhs);}

    // ----------
    // operator +
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator + (Integer lhs, const Integer& rhs) {
        return lhs += rhs;}

    // ----------
    // operator -
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator - (Integer lhs, const Integer& rhs) {
        return lhs -= rhs;}

    // ----------
    // operator *
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator * (Integer lhs, const Integer& rhs) {
        return lhs *= rhs;}

    // ----------
    // operator /
    // ----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs == 0)
     */
    friend Integer operator / (Integer lhs, const Integer& rhs) {
        return lhs /= rhs;}

    // ----------
    // operator %
    // ----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs <= 0)
     */
    friend Integer operator % (Integer lhs, const Integer& rhs) {
        return lhs %= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator << (Integer lhs, int rhs) {
        return lhs <<= rhs;}

    // -----------
    // operator >>
    // -----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator >> (Integer lhs, int rhs) {
        return lhs >>= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * <your documentation>
     */
    friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
        // <your code>
        return lhs << "0";}

    // ---
    // abs
    // ---

    /**
     * absolute value
     * does NOT modify the argument
     * <your documentation>
     */
    friend Integer abs (Integer x) {
        return x.abs();}

    // ---
    // pow
    // ---

    /**
     * power
     * does NOT modify the argument
     * <your documentation>
     * @throws invalid_argument if (x == 0) && (e == 0)
     * @throws invalid_argument if (e < 0)
     */
    friend Integer pow (Integer x, int e) {
        return x.pow(e);}

    private:
        // ----
        // data
        // ----

        // <your data>
        int size;
        bool is_negative;

	deque<int> digit_deque;

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------
        
        /**
         * <your documentation>
         */
        Integer (int value) {
            // <your code>
            size = 1;
            int digit;
            if (value == 0)
                digit_deque.push_front(value);
            if (value < 0)
                is_negative = true;
            while (value != 0) {
	            digit = value % 10;
                digit_deque.push_front(digit);
                value /= 10;
                ++size;
            }
            assert(valid());}

        /**
         * <your documentation>
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            // <your code>
            if (!valid())
                throw std::invalid_argument("Integer::Integer()");}

        // Default copy, destructor, and copy assignment.
        // Integer (const Integer&);
        // ~Integer ();
        // Integer& operator = (const Integer&);

        // ----------
        // operator -
        // ----------

        /**
         * <your documentation>
         */
        Integer operator - () const {
            // <your code>
            return Integer(0);}

        // -----------
        // operator ++
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator ++ () {
            *this += 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator ++ (int) {
            Integer x = *this;
            ++(*this);
            return x;}

        // -----------
        // operator --
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -- () {
            *this -= 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator -- (int) {
            Integer x = *this;
            --(*this);
            return x;}

        // -----------
        // operator +=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator += (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator -=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator *=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator *= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator /=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs == 0)
         */
        Integer& operator /= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator %=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs <= 0)
         */
        Integer& operator %= (const Integer& rhs) {
            // <your code>
            return *this;}

        // ------------
        // operator <<=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator <<= (int n) {
            // <your code>
            return *this;}

        // ------------
        // operator >>=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator >>= (int n) {
            // <your code>
            return *this;}

        // ---
        // abs
        // ---

        /**
         * absolute value
         * <your documentation>
         */
        Integer& abs () {
            // <your code>
            return *this;}

        // ---
        // pow
        // ---

        /**
         * power
         * <your documentation>
         * @throws invalid_argument if (this == 0) && (e == 0)
         * @throws invalid_argument if (e < 0)
         */
        Integer& pow (int e) {
            // <your code>
            return *this;}};

#endif // Integer_h
