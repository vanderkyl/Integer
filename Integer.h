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
    int size1 = e1 - b1;
    int size2 = e2 - b2;
    if (size2 > size1)
        x = plus_digits(b2, e2, b1, e1, x);
    else {
        int num1 = 0;
        int num2 = 0;
        int result = 0;
        int size = 0;
        int digit = 1; 
        while (size2 != 0) {
            --e1;
            --e2;
            num1 += digit * *e1;
            num2 += digit * *e2;
            digit *= 10;
            --size1;
            --size2;
        }
        while (size1 != 0) {
            --e1;
            num1 += digit * *e1;
            digit *= 10;
            --size1;
        }
        result = num1 + num2;
        while (result != 0) {
            *x = result % 10;
            result /= 10;
            ++x;
            ++size;
        }
        
        int i = 1;
        int half_size = size / 2;
        while (half_size != 0) {
            std::swap(*(x - size), *(x - i));
            --half_size;
            --size;
            ++i;
        }

        
    }
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
    if (size2 > size1)
        x = minus_digits(b2, e2, b1, e1, x);
    else {
        int num1 = 0;
        int num2 = 0;
        int result = 0;
        int size = 0;
        int digit = 1; 
        while (size2 != 0) {
            --e1;
            --e2;
            num1 += digit * *e1;
            num2 += digit * *e2;
            digit *= 10;
            --size1;
            --size2;
        }
        while (size1 != 0) {
            --e1;
            num1 += digit * *e1;
            digit *= 10;
            --size1;
        }
        result = num1 - num2;
        while (result != 0) {
            *x = result % 10;
            result /= 10;
            ++x;
            ++size;
        }
        
        int i = 1;
        int half_size = size / 2;
        while (half_size != 0) {
            std::swap(*(x - size), *(x - i));
            --half_size;
            --size;
            ++i;
        }

        
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
    if (size2 > size1)
        x = multiplies_digits(b2, e2, b1, e1, x);
    else {
        int num1 = 0;
        int num2 = 0;
        int result = 0;
        int size = 0;
        int digit = 1; 
        while (size2 != 0) {
            --e1;
            --e2;
            num1 += digit * *e1;
            num2 += digit * *e2;
            digit *= 10;
            --size1;
            --size2;
        }
        while (size1 != 0) {
            --e1;
            num1 += digit * *e1;
            digit *= 10;
            --size1;
        }
        result = num1 * num2;
        while (result != 0) {
            *x = result % 10;
            result /= 10;
            ++x;
            ++size;
        }
      
        int i = 1;
        int half_size = size / 2;
        while (half_size != 0) {
            std::swap(*(x - size), *(x - i));
            --half_size;
            --size;
            ++i;
        }

        
    }
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
    int size1 = e1 - b1;
    int size2 = e2 - b2;
    if (size2 > size1)
        x = divides_digits(b2, e2, b1, e1, x);
    else {
        int num1 = 0;
        int num2 = 0;
        int result = 0;
        int size = 0;
        int digit = 1; 
        while (size2 != 0) {
            --e1;
            --e2;
            num1 += digit * *e1;
            num2 += digit * *e2;
            digit *= 10;
            --size1;
            --size2;
        }
        while (size1 != 0) {
            --e1;
            num1 += digit * *e1;
            digit *= 10;
            --size1;
        }
        if (num1 > num2)
            result = num1 / num2;
        else
            result = num2 / num1;
        while (result != 0) {
            *x = result % 10;
            result /= 10;
            ++x;
            ++size;
        }
        
        int i = 1;
        int half_size = size / 2;
        while (half_size != 0) {
            std::swap(*(x - size), *(x - i));
            --half_size;
            --size;
            ++i;
        }

    }
    return x;}

// --------------
// mod_digits
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
OI mod_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    // <your code>
    int size1 = e1 - b1;
    int size2 = e2 - b2;
    if (size2 > size1)
        x = divides_digits(b2, e2, b1, e1, x);
    else {
        int num1 = 0;
        int num2 = 0;
        int result = 0;
        int size = 0;
        int digit = 1; 
        while (size2 != 0) {
            --e1;
            --e2;
            num1 += digit * *e1;
            num2 += digit * *e2;
            digit *= 10;
            --size1;
            --size2;
        }
        while (size1 != 0) {
            --e1;
            num1 += digit * *e1;
            digit *= 10;
            --size1;
        }
        if (num1 > num2)
            result = num1 % num2;
        else
            result = num2 % num1;
        
        while (result != 0) {
            *x = result % 10;
            result /= 10;
            ++x;
            ++size;
        }
        
        int i = 1;
        int half_size = size / 2;
        while (half_size != 0) {
            std::swap(*(x - size), *(x - i));
            --half_size;
            --size;
            ++i;
        }

        
    }
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
                if (lhs.digits[i] != rhs.digits[i])
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
        if ((lhs.is_negative == true) && (rhs.is_negative == false))
            return true;
        else if ((lhs.is_negative == false) && (rhs.is_negative == true))
            return false;
        else if ((lhs.is_negative == false) && (rhs.is_negative == false)) {
            if (lhs.size < rhs.size)
                return true;
            else if (lhs.size > rhs.size)
                return false;
            else {
                for (int i = 0; i < lhs.size(); ++i) {
                    int diff = lhs.digits[i] - rhs.digits[i];
                    if (diff > 0)
                        return false;
                    if (diff < 0)
                        return true;
                }
                return false;
            }
        }
        else {
            if (lhs.size > rhs.size)
                return true;
            else if (lhs.size < rhs.size)
                return false;
            else {
                for (int i = 0; i < lhs.size(); ++i) {
                    int diff = lhs.digits[i] - rhs.digits[i];
                    if (diff < 0)
                        return false;
                    if (diff > 0)
                        return true;
                }
                return false;
            }
        }
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
        int size = rhs.size;
        while (size > 0) {
            --size;
            lhs << rhs.digits[size];
        }
        return lhs;}

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

        int size;
        bool is_zero;
        bool is_negative;
        deque<int> digits;

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
            size = 0;
            is_zero = false;
            is_negative = false;
            if (value == 0) {
                is_zero = true;
                digits.push_front(value);
                ++size;
            }
            else if (value < 0) {
                is_negative = true;
                value = -value;
            }
            while (value != 0) {
                digits.push_front(value % 10);
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
            int size = this->size;
            int num = 0;
            int digit = 1;
            while (size != 0) {
                --size;
                num += digits[size] * digit;
                digit *= 10;
            }
            if (is_negative == true)
                return Integer(num);
            else
                return Integer(-num);}

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
            deque<int> temp1 = this->digits;
            deque<int> temp2 = rhs.digits;
            this->digits.begin() = plus_digits(temp1.begin(), temp1.end(), temp2.begin(), temp2.end(), this->digits.begin());
            return *this;}

        // -----------
        // operator -=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -= (const Integer& rhs) {
            // <your code>
            deque<int> temp1 = this->digits;
            deque<int> temp2 = rhs.digits;
            this->digits.begin() = minus_digits(temp1.begin(), temp1.end(), temp2.begin(), temp2.end(), this->digits.begin());
            return *this;}

        // -----------
        // operator *=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator *= (const Integer& rhs) {
            // <your code>
            deque<int> temp1 = this->digits;
            deque<int> temp2 = rhs.digits;
            this->digits.begin() = mulplies_digits(temp1.begin(), temp1.end(), temp2.begin(), temp2.end(), this->digit.begin());
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
            deque<int> temp1 = this->digits;
            deque<int> temp2 = rhs.digits;
            this->digits.begin() = divides_digits(temp1.begin(), temp1.end(), temp2.begin(), temp2.end(), this->digits.begin());
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
            deque<int> temp1 = this->digits;
            deque<int> temp2 = rhs.digits;
            this->digits.begin() = mod_digits(temp1.begin(), temp1.end(), temp2.begin(), temp2.end(), this->digits.begin());
            return *this;}

        // ------------
        // operator <<=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator <<= (int n) {
            // <your code>
            deque<int> temp1 = this->digits;
            this->digits.begin() = shift_left_digits(temp1.begin(), temp1.end(), n, this->digits.begin());
            return *this;}

        // ------------
        // operator >>=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator >>= (int n) {
            // <your code>
            deque<int> temp1 = this->digits;
            this->digits.begin() = shift_right_digits(temp1.begin(), temp1.end(), n, this->digits.begin());
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
            if (this->is_negative)
                this->is_negative = false;
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
            /*
            if (this->is_zero && (e == 0))
                throw std::invalid_argument("Invalid computation");
            if (e < 0)
                throw std::invalid_argument("Invalid power");
            if (e == 0) {
                this->digits[0] = 0;
                this->size = 1;
            }
            while (e != 0) {
                int size = this->size;
                while (size > 0) {
                    --size;
                }
            }
            */
            return *this;}};

#endif // Integer_h
