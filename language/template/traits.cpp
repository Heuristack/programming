#include <iostream>
using namespace std;

/**
 *
 * Trait Class
 *
 * a class that encapsulates a set of types and functions necessary for
 * template classes and template functions to
 * manipulate objects of types for which they are instantiated
 *
 * The idea is that traits classes are instances of templates,
 * and are used to carry extra information
 * - especially information that other templates can use -
 * about the types on which the traits template is instantiated.
 *
 * The nice thing is that the traits class T<C> lets us
 * record such extra information about a class C,
 * without requiring any change at all to C.
 * - Herb Sutter
 *
 * The following example is from "An introduction to C++ Traits - Overload Journal #43 - Jun 2001"
 * - Thaddaeus Frogley
 *
 * In the example, trait class 'template<> struct supports_optimised_implementation<ObjectB>'
 * is an instance of template 'template <typename T> struct supports_optimised_implementation'
 * used to carry extra information "is 'optimised_implementation' is implemented"
 * - especially information that another template 'template <bool b> struct algorithm_selector' can use  -
 * about the type 'ObjectB' on which the traits template is instantiated.
 *
 *
 * Think of a trait as a small object whose main purpose is to carry information
 * used by another object or algorithm to determine "policy" or "implementation details".
 * - Bjarne Stroustrup
 *
**/

template <typename T>
struct supports_optimised_implementation
{
    static const bool value = false;
};

template <bool b>
struct algorithm_selector
{
    template <typename T>
    static void implementation(T & object)
    {
        cout << "implementation" << endl;
    }
};

template <>
struct algorithm_selector<true>
{
    template <typename T>
    static void implementation(T & object)
    {
        object.optimised_implementation();
    }
};

template <typename T>
void algorithm(T & object)
{
    algorithm_selector<supports_optimised_implementation<T>::value>::implementation(object);
}

class ObjectA
{};

class ObjectB
{
public:
    void optimised_implementation()
    {
        cout << "implementation - optimised" << endl;
    }
};

template <>
struct supports_optimised_implementation<ObjectB>
{
   static const bool value = true;
};

int main()
{
    ObjectA a;
    ObjectB b;

    algorithm(a);
    algorithm(b);
}

