#define BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED
#include <boost/stacktrace.hpp>
#include <iostream>

using namespace std;

int main()
{
    cout << boost::stacktrace::stacktrace() << endl;
}

