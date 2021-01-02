#include <stdexcept>
#include <string>
#include <vector>
#include <utility>
#include <iostream>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;
using std::pair;
using std::cout;
using std::endl;

template <typename return_type = vector<pair<int,int>>>
auto generate(int i, int j, vector<vector<char>> * board_ptr, int m, int n) -> return_type
{
  return_type v;
  for (auto [p,q] : return_type{{i-1,j},{i+1,j},{i,j-1},{i,j+1}}) {
    if ((0 <= p) && (p < m) && (0 <= q) && (q < n)) {
      if ((*board_ptr)[p][q] == 'W') {
        v.emplace_back(p,q);
      }
    }
  }
  return v;
}

template <typename return_type = vector<pair<int,int>>>
auto boundaries(vector<vector<char>> * board_ptr, int m, int n) -> return_type
{
  return_type v;
  auto add_if = [&v,board_ptr](int i, int j) {
    if ((*board_ptr)[i][j] == 'W') {
      v.emplace_back(i,j);
    }
  };
  for (int i = 0; i < m; i++) { add_if(i,0); add_if(i,n-1); }
  for (int j = 0; j < n; j++) { add_if(0,j); add_if(m-1,j); }
  return v;
}

auto explore(int i, int j, vector<vector<char>> * board_ptr, int m, int n) -> void
{
  if ((*board_ptr)[i][j] == 'W') (*board_ptr)[i][j] = 'G';
  for (auto [p,q] : generate(i,j,board_ptr,m,n)) {
    explore(p,q,board_ptr,m,n);
  }
}

void FillSurroundedRegions(vector<vector<char>>* board_ptr)
{
  if (!board_ptr || board_ptr->empty()) return;
  int m = board_ptr->size(); assert(m > 0);
  int n = board_ptr->operator[](0).size();
  for (int i = 0; i < m; i++) { assert((*board_ptr)[i].size() == n); }
  for (auto [i,j] : boundaries(board_ptr,m,n)) {
//  cout << "(" << i << "," << j << "): " << (*board_ptr)[i][j] << endl;
    explore(i,j,board_ptr,m,n);
  }
  for (int i = 0; i < m; i++) {
  for (int j = 0; j < n; j++) {
    if ((*board_ptr)[i][j] == 'W') (*board_ptr)[i][j] = 'B';
    if ((*board_ptr)[i][j] == 'G') (*board_ptr)[i][j] = 'W';
  }
  }
  return;
}

vector<vector<string>> FillSurroundedRegionsWrapper(
    TimedExecutor& executor, vector<vector<string>> board) {
  vector<vector<char>> char_vector;
  char_vector.resize(board.size());
  for (int i = 0; i < board.size(); i++) {
    for (const string& s : board[i]) {
      if (s.size() != 1) {
        throw std::runtime_error("String size is not 1");
      }
      char_vector[i].push_back(s[0]);
    }
  }

  executor.Run([&] { FillSurroundedRegions(&char_vector); });

  board.clear();
  board.resize(char_vector.size(), {});
  for (int i = 0; i < board.size(); i++) {
    for (char c : char_vector[i]) {
      board[i].emplace_back(1, c);
    }
  }

  return board;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "board"};
  return GenericTestMain(
      args, "matrix_enclosed_regions.cc", "matrix_enclosed_regions.tsv",
      &FillSurroundedRegionsWrapper, DefaultComparator{}, param_names);
}
