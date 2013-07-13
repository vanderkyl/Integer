// --------------------------------
// projects/integer/TestInteger.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program:
% ls /usr/include/cppunit/
...
TestFixture.h
...
% locate libcppunit.a
/usr/lib/libcppunit.a
% g++ -pedantic -std=c++0x -Wall Integer.c++ TestInteger.c++ -o TestInteger -lcppunit -ldl
% valgrind TestInteger > TestInteger.out
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring> // strcmp
#include <sstream> // ostringstream
#include <stdexcept> // invalid_argument
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "Integer.h"

// -----------
// TestInteger
// -----------

struct TestInteger : CppUnit::TestFixture {
    // -----------------
    // shift_left_digits
    // -----------------

    void test_shift_left_digits1 () {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4, 0, 0};
              int x[10];
        const int* p = shift_left_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT((p - x) == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

    void test_shift_left_digits2 () {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4,};
              int x[10];
        const int* p = shift_left_digits(a, a + 3, 0, x);
        CPPUNIT_ASSERT((p - x) == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}
   
    // ------------------
    // shift_right_digits
    // ------------------

    void test_shift_right_digits1 () {
        const int a[] = {2, 3, 4};
        const int b[] = {2};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT((p - x) == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}

    void test_shift_right_digits2 () {
        const int a[] = {2, 3, 4};
        const int b[] = {0};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, 3, x);
        CPPUNIT_ASSERT((p - x) == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));}


    // -----------
    // plus_digits
    // -----------

    void test_plus_digits1 () {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {8, 0, 1};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 3, x); 
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_plus_digits2 () {
        const int a[] = {0};
        const int b[] = {5, 6, 7};
        const int c[] = {5, 6, 7};
              int x[10];
        const int* p = plus_digits(a, a + 1, b, b + 3, x); 
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_plus_digits3 () {
        const int a[] = {1, 5, 0, 0, 9};
        const int b[] = {1, 4, 3, 2};
        const int c[] = {1, 6, 4, 4, 1};
              int x[10];
        const int* p = plus_digits(a, a + 5, b, b + 4, x); 
        CPPUNIT_ASSERT(p - x == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    // ------------
    // minus_digits
    // ------------

    void test_minus_digits1 () {
        const int a[] = {8, 0, 1};
        const int b[] = {5, 6, 7};
        const int c[] = {2, 3, 4};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_minus_digits2 () {
        const int a[] = {2, 3, 4};
        const int b[] = {0};
        const int c[] = {2, 3, 4};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 1, x);

        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_minus_digits3 () {
        const int a[] = {1, 1, 9};
        const int b[] = {1, 0, 5};
        const int c[] = {1, 4};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 2);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
    // -----------------
    // multiplies_digits
    // -----------------

    void test_multiplies_digits1 () {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {1, 3, 2, 6, 7, 8};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_multiplies_digits2 () {
        const int a[] = {4};
        const int b[] = {3};
        const int c[] = {1, 2};
              int x[10];
        const int* p = multiplies_digits(a, a + 1, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 2);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}


    void test_multiplies_digits3 () {
        const int a[] = {9, 9, 9};
        const int b[] = {0};
        const int c[] = {0};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}
    
    // --------------
    // divides_digits
    // --------------

    void test_divides_digits1 () {
        const int a[] = {1, 3, 2, 6, 7, 8};
        const int b[] = {5, 6, 7};
        const int c[] = {2, 3, 4};
              int x[10];
        const int* p = divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_divides_digits2 () {
        const int a[] = {1, 0};
        const int b[] = {4};
        const int c[] = {2};
              int x[10];
        const int* p = divides_digits(a, a + 2, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}

    void test_divides_digits3 () {
        const int a[] = {9, 9, 9};
        const int b[] = {9, 9, 9};
        const int c[] = {1};
              int x[10];
        const int* p = divides_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));}


    // -----------
    // constructor
    // -----------

    void test_constructor_1 () {
        try {
            const Integer<int> x("abc");
            CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(strcmp(e.what(), "Integer()"));}}

    void test_constructor_2 () {
        try {
            const Integer<int> x("2");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_constructor_3 () {
        try {
            const Integer<int> x(2);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // abs
    // ---

    void test_abs_1 () {
        try {
            Integer<int> x = -98765;
            Integer<int>& y = x.abs();
            CPPUNIT_ASSERT( x == 98765);
            CPPUNIT_ASSERT(&x == &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_abs_2 () {
        try {
            const Integer<int> x = -98765;
            const Integer<int> y = abs(x);
            CPPUNIT_ASSERT(x == -98765);
            CPPUNIT_ASSERT(y == 98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // --------
    // equal_to
    // --------

    void test_equal_to () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = 98765;
            CPPUNIT_ASSERT( x == y);
            CPPUNIT_ASSERT( x == 98765);
            CPPUNIT_ASSERT( 98765 == x);
            CPPUNIT_ASSERT( !(x != y));
            CPPUNIT_ASSERT( !(x != 98765));
            CPPUNIT_ASSERT(!(98765 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // --------
    // negation
    // --------

    void test_negation () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == -98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // -------
    // compare
    // -------

        void test_comparision1 () {
        try {
            const Integer<int> x = 99999;
            const Integer<int> y = 999;
            CPPUNIT_ASSERT(x > y);
            CPPUNIT_ASSERT(x >= y);
            CPPUNIT_ASSERT(y < x);
            CPPUNIT_ASSERT(y <= x); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

        void test_comparision2 () {
        try {
            const Integer<int> x = 999;
            const Integer<int> y = 999;
            CPPUNIT_ASSERT(x >= y);
            CPPUNIT_ASSERT(y <= x); }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ------
    // output
    // ------

    void test_output1 () {
        try {
            const Integer<int> x = 98765;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "98765");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_output2 () {
        try {
            const Integer<int> x = -98765;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "-98765");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // -------------
    // plus_operator
    // -------------

    void test_plus_operator1 () {
        try {
            const Integer<int> x = 10;
            const Integer<int> y = -5;
            CPPUNIT_ASSERT(x + y == 5);
            CPPUNIT_ASSERT(y + x == 5);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_plus_operator2 () {
        try {
            const Integer<int> x = 0;
            const Integer<int> y = 5;
            CPPUNIT_ASSERT(x + y == 5);
            CPPUNIT_ASSERT(y + x == 5);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_plus_operator3 () {
        try {
            const Integer<int> x = -10;
            const Integer<int> y = 5;
            CPPUNIT_ASSERT(x + y == -5);
            CPPUNIT_ASSERT(y + x == -5);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // --------------
    // minus_operator
    // --------------

    void test_minus_operator1 () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = 0;
            CPPUNIT_ASSERT(x - y == 98765);
            CPPUNIT_ASSERT(y - x == -98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_minus_operator2 () {
        try {
            const Integer<int> x = 10;
            const Integer<int> y = 5;
            CPPUNIT_ASSERT(x - y == 5);
            CPPUNIT_ASSERT(y - x == -5);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_minus_operator3 () {
        try {
            const Integer<int> x = -10;
            const Integer<int> y = 5;
            CPPUNIT_ASSERT(x - y == -15);
            CPPUNIT_ASSERT(y - x == 15);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // -----------------
    // multiply_operator
    // -----------------

    void test_multiply_operator1 () {
        try {
            const Integer<int> x = 10;
            const Integer<int> y = -987;
            CPPUNIT_ASSERT(x * y == -9870);
            CPPUNIT_ASSERT(y * x == -9870);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_multiply_operator2 () {
        try {
            const Integer<int> x = -100;
            const Integer<int> y = -987;
            CPPUNIT_ASSERT(x * y == 98700);
            CPPUNIT_ASSERT(y * x == 98700);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_multiply_operator3 () {
        try {
            const Integer<int> x = 8;
            const Integer<int> y = 0;
            CPPUNIT_ASSERT(x * y == 0);
            CPPUNIT_ASSERT(y * x == 0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---------------
    // divide_operator
    // ---------------

    void test_divide_operator1 () {
        try {
            const Integer<int> x = 98;
            const Integer<int> y = 10;
            CPPUNIT_ASSERT(x / y == 9);
            CPPUNIT_ASSERT(y / x == 0);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_divide_operator2 () {
        try {
            const Integer<int> x = -10;
            const Integer<int> y = 1;
            CPPUNIT_ASSERT(x / y == -10);
            CPPUNIT_ASSERT(y / x == 0);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_divide_operator3 () {
        try {
            const Integer<int> x = 100;
            const Integer<int> y = -10;
            CPPUNIT_ASSERT(x / y == -10);
            CPPUNIT_ASSERT(y / x == 0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(true);}}

    // ---------------
    // mod_operator
    // ---------------

    void test_mod_operator1 () {
        try {
            const Integer<int> x = 100;
            const Integer<int> y = 3;
            CPPUNIT_ASSERT(x % y == 1);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_mod_operator2 () {
        try {
            const Integer<int> x = 10;
            const Integer<int> y = 3;
            CPPUNIT_ASSERT(x % y == 1);
            }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_mod_operator3 () {
        try {
            const Integer<int> x = -119;
            const Integer<int> y = -1;
            CPPUNIT_ASSERT(x % y == 0);
            }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(true);}}

    // -------------------
    // left_shift_operator
    // -------------------

    void test_left_shift_operator1 () {
        try {
            const Integer<int> x = 99;
            int y = 2;
            CPPUNIT_ASSERT(x << y == 9900);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_left_shift_operator2 () {
        try {
            const Integer<int> x = 987;
            int y = 0;
            CPPUNIT_ASSERT(x << y == 987);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // --------------------
    // right_shift_operator
    // --------------------

    void test_right_shift_operator1 () {
        try {
            const Integer<int> x = 999;
            int y = 2;
            CPPUNIT_ASSERT(x >> y == 9);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_right_shift_operator2 () {
        try {
            const Integer<int> x = 999;
            int y = 3;
            CPPUNIT_ASSERT(x >> y == 0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // pow
    // ---

    void test_pow_1 () {
        try {
            Integer<int> x = 98765;
            const int e = 1;
            Integer<int>& y = x.pow(e);
            CPPUNIT_ASSERT(e == 1);
            CPPUNIT_ASSERT(x == 98765);
            CPPUNIT_ASSERT(&x == &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_2 () {
        try {
            const Integer<int> x = 98765;
            const int e = 0;
            const Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(x == 98765);
            CPPUNIT_ASSERT(e == 0);
            CPPUNIT_ASSERT(y == 1);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_pow_3 () {
        try {
            const Integer<int> x = 4;
            const int e = 3;
            const Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(x == 4);
            CPPUNIT_ASSERT(e == 3);
            CPPUNIT_ASSERT(y == 64);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    void test_shift_right_equal1 () {
        Integer<int> a = 12345;
        a >>= 0;
        CPPUNIT_ASSERT(a == 12345);}
    
    void test_shift_right2 () {
        Integer<int> a = 12345;
        a >>= 1;
        CPPUNIT_ASSERT(a == 1234);}
    
    void test_shift_right3 () {
        Integer<int> a = -12345;
        a >>= 2;
        CPPUNIT_ASSERT(a == -123);}

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestInteger);
    CPPUNIT_TEST(test_shift_left_digits1);
    CPPUNIT_TEST(test_shift_left_digits2);
    CPPUNIT_TEST(test_shift_right_digits1);
    CPPUNIT_TEST(test_shift_right_digits2);
    CPPUNIT_TEST(test_plus_digits1);
    CPPUNIT_TEST(test_plus_digits2);
    CPPUNIT_TEST(test_plus_digits3);
    CPPUNIT_TEST(test_minus_digits1);
    CPPUNIT_TEST(test_minus_digits2);
    CPPUNIT_TEST(test_minus_digits3);
    CPPUNIT_TEST(test_multiplies_digits1);
    CPPUNIT_TEST(test_multiplies_digits2);
    CPPUNIT_TEST(test_multiplies_digits3);
    CPPUNIT_TEST(test_divides_digits1);
    CPPUNIT_TEST(test_divides_digits2);
    CPPUNIT_TEST(test_divides_digits3);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_abs_1);
    CPPUNIT_TEST(test_abs_2);
    CPPUNIT_TEST(test_negation);
    CPPUNIT_TEST(test_comparision1);
    CPPUNIT_TEST(test_comparision2);
    CPPUNIT_TEST(test_output1);
    CPPUNIT_TEST(test_output2);
    CPPUNIT_TEST(test_plus_operator1);
    CPPUNIT_TEST(test_plus_operator2);
    CPPUNIT_TEST(test_plus_operator3);
    CPPUNIT_TEST(test_minus_operator1);
    CPPUNIT_TEST(test_minus_operator2);
    CPPUNIT_TEST(test_minus_operator3);
    CPPUNIT_TEST(test_multiply_operator1);
    CPPUNIT_TEST(test_multiply_operator2);
    CPPUNIT_TEST(test_multiply_operator3);
    CPPUNIT_TEST(test_divide_operator1);
    CPPUNIT_TEST(test_divide_operator2);
    CPPUNIT_TEST(test_divide_operator3);
    CPPUNIT_TEST(test_mod_operator1);
    CPPUNIT_TEST(test_mod_operator2);
    CPPUNIT_TEST(test_mod_operator3);
    CPPUNIT_TEST(test_left_shift_operator1);
    CPPUNIT_TEST(test_left_shift_operator2);
    CPPUNIT_TEST(test_right_shift_operator1);
    CPPUNIT_TEST(test_right_shift_operator2);
    CPPUNIT_TEST(test_negation);
    CPPUNIT_TEST(test_pow_1);
    CPPUNIT_TEST(test_pow_2);
    CPPUNIT_TEST(test_pow_3);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    cout << "TestInteger.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestInteger::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}