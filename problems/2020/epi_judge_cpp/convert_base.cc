#include <string>
#include <iostream>

#include "test_framework/generic_test.h"
using std::string;

int to_num(char c)
{
  if (c >= '0' && c <= '9') return c - '0';
  else if (c >= 'A') return c - 'A' + 10;
  return 0;
}

char to_char(int d)
{
  if (d >= 0 && d <= 9) return '0' + d;
  else if (d >= 10) return 'A' + d - 10;
  return 0;
}

string ConvertBase(const string& num_as_string, int b1, int b2)
{
  auto is_negative = false;
  if (!num_as_string.empty() && num_as_string[0] == '-') {
    is_negative = true;
  }
  int n = 0;
  for (auto c : num_as_string) {
    n = n * b1 + to_num(c);
  }
  if (!n) return "0";
  string s;
  while (n) {
    auto q = n % b2;
    n = n / b2;
    s.push_back(to_char(abs(q)));
  }
  if (is_negative) s.push_back('-');
  return string(rbegin(s),rend(s));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
