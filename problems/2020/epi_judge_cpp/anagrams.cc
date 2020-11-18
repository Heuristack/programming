#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

#include "test_framework/generic_test.h"
using std::unordered_map;
using std::string;
using std::vector;

vector<vector<string>> FindAnagrams(vector<string> const & dictionary)
{
  unordered_map<string,vector<string>> m;
  for (auto const & w : dictionary) {
    string s(w);
    sort(begin(s),end(s));
    m[s].emplace_back(w);
  }
  vector<vector<string>> g;
  for (auto const & [p,v] : m) {
    if (v.size() >= 2) {
      g.emplace_back(v);
    }
  }
  return g;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"dictionary"};
  return GenericTestMain(args, "anagrams.cc", "anagrams.tsv", &FindAnagrams,
                         UnorderedComparator{}, param_names);
}
