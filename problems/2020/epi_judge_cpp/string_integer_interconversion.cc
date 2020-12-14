#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x)
{
  if (!x) return "0";
  auto is_negative = (x < 0);
  string s;
  while (x) {
    auto r = x % 10;
    x = x / 10;
    s.push_back('0' + abs(r));
  }
  if (is_negative) s.push_back('-');
  return string(s.rbegin(),s.rend());
}

int StringToInt(const string& s)
{
  auto is_negative = false;
  auto has_sign = false;
  if (!s.empty() && s[0] == '-') {
      is_negative = true;
      has_sign = true;
  }
  if (!s.empty() && s[0] == '+') {
      is_negative = false;
      has_sign = true;
  }
  auto p = begin(s);
  auto r = end(s);
  if (has_sign) p = next(p);
  int i = 0;
  for (; p != r; p++) {
    i = i*10 + (*p) - '0';
  }
  if (is_negative) i = -i;
  return i;
}

void Wrapper(int x, const string& s)
{
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
