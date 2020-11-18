#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_map;

bool IsLetterConstructibleFromMagazine(const string& letter_text, const string& magazine_text)
{
  unordered_map<char,int> m;
  for (auto const & c : letter_text) {
      m[c]++;
  }
  for (auto const & c : magazine_text) {
      if (m.find(c) != m.end()) {
          m[c]--;
          if (m[c] == 0) {
              m.erase(c);
              if (m.empty()) {
                  return 1;
              }
          }
      }
  }
  return m.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
