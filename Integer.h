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
 
// -----------
// reverse_num
// -----------

/**
 * @param b an iterator to the beginning of an input sequence (inclusive)
 * @param e an iterator to the end of an input sequence (exclusive)
 * reverse a sequence of decimal digits
 */
template <typename II>
void reverse_num (II b, II e) {
    while ((b != e) && (b != --e)) {
        std::swap(*b, *e);
        ++b;
    }
}

/**
 * @param b an iterator to the beginning of an input sequence (inclusive)
 * @param e an iterator to the end of an input sequence (exclusive)
 * @return x an output iterator
 * copy and reverse a sequence of decimal digits
 */
template <typename II, typename OI>
OI copy_reverse (II b, II e, OI x) {
    int size = e - b;
    assert(size >= 0);
    while (b != e) {
        --size;
        *(x + size) = *b;
        ++b;
    }
    return x;
}


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
    assert(n >= 0);
    // Copy the digits into the output iterator
    while (b != e) {
        *x = *b;
        ++b;
        ++x;
    }
    // Put n 0's into the output iterator
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
    int size = e - b;
    assert(size > 0);
    assert(n >= 0);
    int num = size - n;
    // If num is 0 or negative the result will automatically be 0;
    if (num > 0) {
        // Copy the digits into the output till num is 0.
        while (num != 0) {
            *x = *b;
            ++b;
            ++x;
            --num;
        }
    }
    else {
        *x = 0;
        ++x;
    } 
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
    int size1 = e1 - b1;
    int size2 = e2 - b2;
    assert(size1 > 0);
    assert(size2 > 0);
    if (size2 > size1)
        x = plus_digits(b2, e2, b1, e1, x);
    else {
        int sum = 0; 
        int size = 0;
        while (size2 != 0) {
            --size1;
            --size2;
            // Add the least significant numbers first.
            sum += *(b1 + size1) + *(b2 + size2);
            // Put the mod of the sum into the output.
            *x = sum % 10;
            // Have sum contain the remainder.
            sum /= 10;
            ++x;
            ++size;
            
        }
        // Add left over digits from the larger number.
        while (size1 != 0) {
            --size1;
            sum += *(b1 + size1);
            *x = sum % 10;
            sum /= 10;
            ++x;
            ++size;
        }
        // Add left over remainder.
        if (sum != 0) {
            *x = sum;
            ++x;
            ++size;
        }
        // The digits are placed into x backwards; reverse list.
        reverse_num(x - size, x);
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
    // Assume the first number is greater than or equal to the second
    int size1 = e1 - b1;
    int size2 = e2 - b2;
    assert(size1 > 0);
    assert(size2 > 0);
    if (*b2 == 0 && size2 == 1) {
        while (b1 != e1) {
            *x = *b1;
            ++x;
            ++b1;
        }
    }
    else if (size2 > size1)
        x = minus_digits(b2, e2, b1, e1, x);
    else {
        int temp1[20000];
        int temp2[20000];
        copy_reverse(b1, e1, temp1);
        copy_reverse(b2, e2, temp2);
        int i1 = 0;
        int i2 = 0;
        int diff = 0; 
        int size = 0;
        int num1 = 0;
        int num2 = 0;
        bool zero_remainder = false;

        while (i2 < size2) {
            num1 += temp1[i1];
            num2 = temp2[i2];
            // If the sum of num1 is negative, roll over to 9
            if (num1 == -1) {
                num1 = 9;
                zero_remainder = true;
            }
            // If num1 is less than num2 add 10 to num1
            if (num1 < num2)
                num1 += 10;
            diff = num1 - num2;
            // If the last number diff is 0 don't copy it to x
            if (diff == 0 && i1 == (size1 - 1)) 
                --size;
            else {
                *x = diff % 10;
                ++x;
            }
            // Account for negative diff
            if (num1 >= 10 || zero_remainder) {
                num1 = -1;
                zero_remainder = false;
            }
            else 
                num1 = 0; 
            ++i1;
            ++i2;
            ++size;
        }
        // Minus extra digits from the first number
        while (i1 < size1) {
            num1 += temp1[i1];
            // If the last number diff is 0 don't copy it to x.
            if (num1 == 0 && i1 == (size1 - 1)) {
            }
            else {
                *x = num1;
                ++size;
                ++x;
            } 
            num1 = 0;
            ++i1;
        }
        // The digits are placed into x backwards; reverse list.
        reverse_num(x - size, x);
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
    int size1 = e1 - b1;
    int size2 = e2 - b2;
    assert(size1 > 0);
    assert(size2 > 0);
    int size_x = 0;
    // If either number is 0 the result is 0;
    if ((*b2 == 0 && size2 == 1)) {
        *x = 0;
        ++x;
    }
    else if (size2 > size1)
        x = multiplies_digits(b2, e2, b1, e1, x);
    else {
        int temp1[20000];
        int temp2[20000];
        copy_reverse(b1, e1, temp1);
        copy_reverse(b2, e2, temp2);
        OI temp_x;
        int pos;       // Position that is being added on the output list.
        int product;  
        int sum = 0;
        int start = 0; // Position to start adding.
        int i1 = 0;
        int i2 = 0;
        while (i2 < size2){
            product = 0;
            temp_x = x + start; // Start adding here.
            i1 = 0;
            pos = start;
            // Multiply each digit of the second number with every digit of the first.
            while (i1 < size1){
                // Multiply the digits the numbers.
                product += temp1[i1] * temp2[i2];
                // If placing product into a new output slot, just place it.
                // If placing product into pre-existing slot, add the two numbers.
                if (pos >= size_x){
                    *temp_x = product % 10;
                    ++size_x;
                } 
                else {
                    sum += *temp_x + (product % 10);
                    // If sum is greater than 9 hold remainder in sum.
                    if (sum > 9) {
                        *temp_x = sum % 10;
                        product = sum; 
                        sum /= 10;
                    }
                    else { 
                        *temp_x = sum;
                        sum = 0;
                    }
                }
                // Hold remainder of product.
                product /= 10;
                ++temp_x;
                ++pos;
                ++i1;
            }
            // If there is a product remainder place or add it to x.
            if (product != 0) {
                if (pos >= size_x){
                    *temp_x = product;
                    ++size_x;
                } 
                else {
                    sum = *temp_x + product;
                    if (sum > 9) {
                        *temp_x = sum % 10;
                        product = sum;  
                    }
                    else
                        *temp_x = sum;
                }
                ++temp_x;
                ++pos;
            }
            ++i2;
            ++start;
        }
        // The digits are placed into x backwards; reverse list.
        reverse_num(x, x + size_x);
        x = x + size_x;
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
    int size1 = e1 - b1;
    int size2 = e2 - b2;
    assert(size1 > 0);
    assert(size2 > 0);
    if (size2 <= size1) {
        int size1 = e1 - b1;
        int size2 = e2 - b2;
        int num1 = 0;
        int num2 = 0;
        int result = 0;
        int size_x = 0;
        int digit = 1;
        // Convert lists into ints. 
        while (size2 != 0) {
            --e1;
            --e2;
            // Add digit to each num.
            num1 += digit * *e1;
            num2 += digit * *e2;
            digit *= 10;
            --size1;
            --size2;
        }
        // If more digits keep converting.
        while (size1 != 0) {
            --e1;
            num1 += digit * *e1;
            digit *= 10;
            --size1;
        }
        // Divide the two numbers
        result = num1 / num2;
        // Copy the result into x.
        while (result != 0) {
            *x = result % 10;
            result /= 10;
            ++x;
            ++size_x;
        }
        // The digits are placed into x backwards; reverse list.
        reverse_num(x - size_x, x);
    }
    else {
        *x = 0;
        ++x;
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
    int size1 = e1 - b1;
    int size2 = e2 - b2;
    assert(size1 > 0);
    assert(size2 > 0);
    int num1 = 0;
    int num2 = 0;
    int result = 0;
    int size_x = 0;
    int digit = 1;
    // Convert lists into ints. 
    while (size2 != 0) {
        --e1;
        --e2;
        // Add digit to each num.
        num1 += digit * *e1;
        num2 += digit * *e2;
        digit *= 10;
        --size1;
        --size2;
    }
    // If more digits keep converting.
    while (size1 != 0) {
        --e1;
        num1 += digit * *e1;
        digit *= 10;
        --size1;
    }
    // Mod the two numbers
    if (num1 > num2)
        result = num1 % num2;
    else
        result = num2 % num1;
    // Copy the result into x.
    while (result != 0) {
        *x = result % 10;
        result /= 10;
        ++x;
        ++size_x;
    }
    // The digits are placed into x backwards; reverse list.
    reverse_num(x - size_x, x);
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
        if (lhs.size == 1 && rhs.size == 1 && lhs.digits[0] == rhs.digits[0])
            return true;
        // Check the two Integers if the sizes and negativity are equal.
        if (lhs.size == rhs.size && lhs.is_negative == rhs.is_negative) {
            for (int i = 0; i < lhs.size; i++) {
                // If the corresponding digits are not equal return false.
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
        bool lsign = lhs.is_negative;
        bool rsign = rhs.is_negative;
        int lsize = lhs.size;
        int rsize = rhs.size;
        // If lhs is negative and rhs is positive return true. 
        if (lsign && !rsign)
            return true;
        // If lhs is positive and rhs is negative return false.
        else if (!lsign && rsign)
            return false;
        // If both are positive
        else if (!lsign && !rsign) {
            // If lhs is smaller return true.
            if (lsize < rsize)
                return true;
            // If rhs is smaller return false.
            else if (lsize > rsize)
                return false;
            // If equal check digits.
            else {
                for (int i = 0; i < lsize; ++i) {
                    int diff = lhs.digits[i] - rhs.digits[i];
                    if (diff > 0)
                        return false;
                    if (diff < 0)
                        return true;
                }
                return false;
            }
        }
        // If both are negative
        else {
            // If lhs is bigger return true.
            if (lsize > rsize)
                return true;
            // If rhs is bigger return false.
            else if (lsize < rsize)
                return false;
            // If equal check digits.
            else {
                for (int i = 0; i < lsize; ++i) {
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
     * @param lhs an Integer on the left hand side of operator
     * @param rhs an Integer on the right hand side of operator
     * @return true if less than or equal or false if greater
     * (lhs <= rhs) => true or false
     */
    friend bool operator <= (const Integer& lhs, const Integer& rhs) {
        return !(rhs < lhs);}

    // ----------
    // operator >
    // ----------

    /**
     * @param lhs an Integer on the left hand side of operator
     * @param rhs an Integer on the right hand side of operator
     * @return true if greater than or false if less than or equal
     * (lhs > rhs) => true or false
     */
    friend bool operator > (const Integer& lhs, const Integer& rhs) {
        return (rhs < lhs);}

    // -----------
    // operator >=
    // -----------

    /**
     * @param lhs an Integer on the left hand side of operator
     * @param rhs an Integer on the right hand side of operator
     * @return true if greater than or equal or false if less than
     * (lhs >= rhs) => true or false
     */
    friend bool operator >= (const Integer& lhs, const Integer& rhs) {
        return !(lhs < rhs);}

    // ----------
    // operator +
    // ----------

    /**
     * @param lhs an Integer on the left hand side of operator
     * @param rhs an Integer on the right hand side of operator
     * @return lhs = lhs + rhs
     * (lhs + rhs) => Integer
     */   
    friend Integer operator + (Integer lhs, const Integer& rhs) {
        return lhs += rhs;}

    // ----------
    // operator -
    // ----------

    /**
     * @param lhs an Integer on the left hand side of operator
     * @param rhs an Integer on the right hand side of operator
     * @return lhs = lhs - rhs
     * (lhs - rhs) => Integer
     */ 
    friend Integer operator - (Integer lhs, const Integer& rhs) {
        return lhs -= rhs;}

    // ----------
    // operator *
    // ----------

    /**
     * @param lhs an Integer on the left hand side of operator
     * @param rhs an Integer on the right hand side of operator
     * @return lhs = lhs * rhs
     * (lhs * rhs) => Integer
     */ 
    friend Integer operator * (Integer lhs, const Integer& rhs) {
        return lhs *= rhs;}

    // ----------
    // operator /
    // ----------

    /**
     * @param lhs an Integer on the left hand side of operator
     * @param rhs an Integer on the right hand side of operator
     * @return lhs = lhs / rhs
     * (lhs / rhs) => Integer
     * @throws invalid_argument if (rhs == 0)
     */
    friend Integer operator / (Integer lhs, const Integer& rhs) {
        return lhs /= rhs;}

    // ----------
    // operator %
    // ----------

    /**
     * @param lhs an Integer on the left hand side of operator
     * @param rhs an Integer on the right hand side of operator
     * @return lhs = lhs % rhs
     * (lhs % rhs) => Integer
     * @throws invalid_argument if (rhs <= 0)
     */
    friend Integer operator % (Integer lhs, const Integer& rhs) {
        return lhs %= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * @param lhs an Integer on the left hand side of operator
     * @param rhs an int that equals the number of shifts
     * @return lhs = lhs << rhs
     * (lhs << rhs) => Integer
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator << (Integer lhs, int rhs) {
        return lhs <<= rhs;}

    // -----------
    // operator >>
    // -----------

    /**
     * @param lhs an Integer on the left hand side of operator
     * @param rhs an int that equals the number of shifts
     * @return lhs = lhs >> rhs
     * (lhs >> rhs) => Integer
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator >> (Integer lhs, int rhs) {
        return lhs >>= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * @param lhs an ostream on the left hand side of operator
     * @param rhs an Integer on the right hand side of operator
     * @return lhs
     * (lhs << rhs) => ostream
     * Allow printing of Integer
     */
    friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
        int i = 0;
        // If the Integer is negative, append a negative sign
        if (rhs.is_negative && (rhs.digits[0] != 0 && rhs.size != 0))
            lhs << "-";
        while (i < rhs.size) {
            lhs << rhs.digits[i];
            ++i;
        }
        return lhs;}

    // ---
    // abs
    // ---

    /**
     * absolute value
     * does NOT modify the argument
     * @param x an Integer
     * @return Integer by calling the method abs
     */
    friend Integer abs (Integer x) {
        return x.abs();}

    // ---
    // pow
    // ---

    /**
     * power
     * does NOT modify the argument
     * @param x an Integer
     * @param e an int: x^e
     * @return Integer by calling the method pow
     * @throws invalid_argument if (x == 0) && (e == 0)
     * @throws invalid_argument if (e < 0)
     */
    friend Integer pow (Integer x, int e) {
        return x.pow(e);}

    private:
        // ----
        // data
        // ----

        int size;          // Number of digits in deque
        bool is_valid;     // If the Integer is valid
        bool is_negative;  // If the Integer is negative
        deque<int> digits; // Container of digits.

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            return is_valid;}

    public:
        // ------------
        // constructors
        // ------------
        
        /**
         * @param value an int that is constructed into an Integer
         * Mod the value for the digits and divide to get to the next digit
         */
        Integer (int value) {
            size = 0;
            is_valid = true;
            is_negative = false;
            if (value == 0) {
                digits.push_back(value);
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
         * @param value a string that is trying to be constructed
         * Check ascii values for validity. Construct valid Integer if it checks out.
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            std::string temp = value;
            is_valid = true;
            // Check if there are any non-number characters in the string
            for (char& c : temp) {
                int ascii = (int) c;
                if (ascii < 48 || ascii > 57) {
                    is_valid = false;
                    break;
                }

            }
            // Throw if invalid
            // Create a valid integer if valid string.
            if (!valid())
                throw std::invalid_argument("Integer::Integer()");
            else 
                *this = Integer(std::stoi(value));
        }

        // Default copy, destructor, and copy assignment.
        // Integer (const Integer&);
        // ~Integer ();
        // Integer& operator = (const Integer&);

        // ----------
        // operator -
        // ----------

        /**
         * Do not modify this
         * @return an Integer
         * Negate the Integer given 
         */
        Integer operator - () const {
            Integer x = *this;
            if (x.is_negative == true)
                x.is_negative = false;
            else
                x.is_negative = true;
            return x;}
            

        // -----------
        // operator ++
        // -----------

        /**
         * @return an Integer which is this
         * Increment the Integer given
         */
        Integer& operator ++ () {
            *this += 1;
            return *this;}

        /**
         * @return an Integer which is this
         * Increment the Integer given
         */
        Integer operator ++ (int) {
            Integer x = *this;
            ++(*this);
            return x;}

        // -----------
        // operator --
        // -----------

        /**
         * @return an copy of given Integer before calculation
         * Decrement the Integer given
         */
        Integer& operator -- () {
            *this -= 1;
            return *this;}

        /**
         * @return an copy of given Integer before calculation
         * Decrement the Integer give
         */
        Integer operator -- (int) {
            Integer x = *this;
            --(*this);
            return x;}

        // -----------
        // operator +=
        // -----------

        /**
         * @param rhs an Integer on the right hand side of operator
         * @return this = this + rhs
         * (this + rhs) => this
         */
        Integer& operator += (const Integer& rhs) {
            // The 30th Mersenne prime has 39,751 digits
            int result[40000];
            int* end;
            // If this is positive and rhs is negative
            if (!this->is_negative && rhs.is_negative) {
                this->is_negative = true;
                if (*this < rhs) { 
                    this->is_negative = false;
                    end = minus_digits(this->digits.begin(), this->digits.end(), rhs.digits.begin(), rhs.digits.end(), result);
                }
                else {
                    end = minus_digits(rhs.digits.begin(), rhs.digits.end(), this->digits.begin(), this->digits.end(), result);
                }
            }
            // If this is negative and rhs is positive
            else if (this->is_negative && !rhs.is_negative) {
                this->is_negative = false;
                if (*this > rhs) { 
                    this->is_negative = true;
                    end = minus_digits(this->digits.begin(), this->digits.end(), rhs.digits.begin(), rhs.digits.end(), result);
                }
                else {
                    end = minus_digits(rhs.digits.begin(), rhs.digits.end(), this->digits.begin(), this->digits.end(), result);
                }
            }
            // If the negativity of both are equal
            else {
                end = plus_digits(this->digits.begin(), this->digits.end(), rhs.digits.begin(), rhs.digits.end(), result);
            }
            int result_size = end - result;
            // Copy digits from result into this->digits
            for (int i = 0; i < result_size; ++i) {
                if (i < size)
                    this->digits[i] = result[i];
                else
                    this->digits.push_back(result[i]);
            }    
            this->size = result_size;
            return *this;}

        // -----------
        // operator -=
        // -----------

        /**
         * @param rhs an Integer on the right hand side of operator
         * @return this = this - rhs
         * (this - rhs) => this
         */
        Integer& operator -= (const Integer& rhs) {
            // The 30th Mersenne prime has 39,751 digits
            int result[40000];
            int* end;
            // If this is positive and rhs is positive
            
            if (!this->is_negative && !rhs.is_negative) {
                if (*this < rhs) { 
                    this->is_negative = true;
                    end = minus_digits(rhs.digits.begin(), rhs.digits.end(), this->digits.begin(), this->digits.end(), result);
                }
                else {
                    end = minus_digits(this->digits.begin(), this->digits.end(), rhs.digits.begin(), rhs.digits.end(), result);   
                }
            }
            // If this is negative and rhs is negative
            else if (this->is_negative && rhs.is_negative) {
                if (*this >= rhs) { 
                    this->is_negative = false;
                    end = minus_digits(rhs.digits.begin(), rhs.digits.end(), this->digits.begin(), this->digits.end(), result);
                }
                else {
                    end = minus_digits(this->digits.begin(), this->digits.end(), rhs.digits.begin(), rhs.digits.end(), result);   
                }
            }
            // If the negativity of both are not equal
            else {
                end = plus_digits(this->digits.begin(), this->digits.end(), rhs.digits.begin(), rhs.digits.end(), result);
            }
            
            //end = minus_digits(this->digits.begin(), this->digits.end(), rhs.digits.begin(), rhs.digits.end(), result);
            int result_size = end - result;
            // Copy digits from result into this->digits
            for (int i = 0; i < result_size; ++i) {
                if (i < size)
                    this->digits[i] = result[i];
                else
                    this->digits.push_back(result[i]);
            }    
            this->size = result_size;
            return *this;}

        // -----------
        // operator *=
        // -----------

        /**
         * @param rhs an Integer on the right hand side of operator
         * @return this = this * rhs
         * (this * rhs) => this
         */
        Integer& operator *= (const Integer& rhs) {
            // The 30th Mersenne prime has 39,751 digits
            int result[40000];
            int* end = multiplies_digits(this->digits.begin(), this->digits.end(), rhs.digits.begin(), rhs.digits.end(), result);
            int result_size = end - result;
            // Copy digits from result into this->digits
            for (int i = 0; i < result_size; ++i) {
                if (i < size)
                    this->digits[i] = result[i];
                else
                    this->digits.push_back(result[i]);
            }  
            // Check negativity
            
            if (this->is_negative == rhs.is_negative)
                this->is_negative = false;
            else 
                this->is_negative = true;
            
            this->size = result_size;
            
            return *this;}

        // -----------
        // operator /=
        // -----------

        /**
         * @param rhs an Integer on the right hand side of operator
         * @return this = this / rhs
         * (this / rhs) => this
         * @throws invalid_argument if (rhs == 0)
         */
        Integer& operator /= (const Integer& rhs) {
            if ((rhs.size == 1 && rhs.digits[0] == 0))
                throw std::invalid_argument("Invalid parameter");
            // The 30th Mersenne prime has 39,751 digits
            if (rhs > *this && this->is_negative == rhs.is_negative) {
                this->digits[0] = 0;
                this->size =  1;
            }
            else {
                int result[40000];
                int* end = divides_digits(this->digits.begin(), this->digits.end(), rhs.digits.begin(), rhs.digits.end(), result);
                int result_size = end - result;
                // Copy digits from result into this->digits
                for (int i = 0; i < result_size; ++i) {
                    if (i < size)
                        this->digits[i] = result[i];
                    else
                        this->digits.push_back(result[i]);
                }    
                if (this->is_negative == rhs.is_negative)
                    this->is_negative = false;
                else
                    this->is_negative = true; 
                this->size = result_size;
            }
            return *this;}

        // -----------
        // operator %=
        // -----------

        /**
         * @param rhs an Integer on the right hand side of operator
         * @return this = this % rhs
         * (this % rhs) => this
         * @throws invalid_argument if (rhs <= 0)
         */
        Integer& operator %= (const Integer& rhs) {
            if ((rhs.size == 1 && rhs.digits[0] == 0) || rhs.is_negative)
                throw std::invalid_argument("Invalid parameter");
            // The 30th Mersenne prime has 39,751 digits
            int result[40000];
            int* end = mod_digits(this->digits.begin(), this->digits.end(), rhs.digits.begin(), rhs.digits.end(), result);
            int result_size = end - result;
            // Copy digits from result into this->digits
            for (int i = 0; i < result_size; ++i) {
                if (i < size)
                    this->digits[i] = result[i];
                else
                    this->digits.push_back(result[i]);
            }    
            this->size = result_size;
            return *this;}

        // ------------
        // operator <<=
        // ------------

        /**
         * @param n an int that is the number of left shifts
         * @return this = this << rhs
         * (this << rhs) => this
         */
        Integer& operator <<= (int n) {
            // The 30th Mersenne prime has 39,751 digits
            int result[40000];
            int* end = shift_left_digits(this->digits.begin(), this->digits.end(), n, result);
            int result_size = end - result;
            // Copy digits from result into this->digits
            for (int i = 0; i < result_size; ++i) {
                if (i < size)
                    this->digits[i] = result[i];
                else
                    this->digits.push_back(result[i]);
            }    
            this->size = result_size;
            return *this;}

        // ------------
        // operator >>=
        // ------------

        /**
         * @param n an int that is the number of left shifts
         * @return this = this >> rhs
         * (this >> rhs) => this
         */
        Integer& operator >>= (int n) {
            // The 30th Mersenne prime has 39,751 digits
            int result[40000];
            int* end = shift_right_digits(this->digits.begin(), this->digits.end(), n, result);
            int result_size = end - result;
            // Copy digits from result into this->digits
            for (int i = 0; i < result_size; ++i) {
                this->digits[i] = result[i];
            }    
            this->size = result_size;
            return *this;}

        // ---
        // abs
        // ---

        /**
         * absolute value
         * @return this
         * Change class member is_negative to false if true
         */
        Integer& abs () {
            if (this->is_negative)
                this->is_negative = false;
            return *this;}

        // ---
        // pow
        // ---

        /**
         * power
         * @param e an int that is the power: this^e
         * @return this = this^e = this.pow(e)
         * @throws invalid_argument if (this == 0) && (e == 0)
         * @throws invalid_argument if (e < 0)
         */
        Integer& pow (int e) {
            if ((this->digits[0] == 0 && this->size == 1) && (e == 0))
                throw std::invalid_argument("Invalid computation");
            if (e < 0)
                throw std::invalid_argument("Invalid power");
            // If e = 0 the result is 1
            else if (e == 0) {
                this->digits[0] = 1;
                this->size = 1;
            }
            else {
                // Keep multiplying this by a copy of its original until e = 1
                Integer x = *this;
                while (e != 1) {
                    *this *= x;
                    --e;
                }
            }   
            return *this;}};

#endif // Integer_h
