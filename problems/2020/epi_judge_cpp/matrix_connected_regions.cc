#include <utility>
#include <deque>
#include <vector>
#include <iostream>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"

using std::pair;
using std::deque;
using std::vector;
using std::cout;
using std::endl;

auto generate_adjacents(int i, int j, int m, int n) -> vector<pair<int,int>>
{
  vector<pair<int,int>> v;
  for (auto [p,q] : vector<pair<int,int>>{{i-1,j},{i+1,j},{i,j-1},{i,j+1}}) {
    if ((0 <= p) && (p < m) && (0 <= q) && (q < n)) {
      v.emplace_back(p,q);
//    cout << "(" << p << "," << q << ")" << endl;
    }
  }
  return v;
}

void FlipColor(int x, int y, vector<deque<bool>> * image_ptr)
{
  if (image_ptr->empty()) return;
  int n = image_ptr->size();
  for (int i = 0; i < n; i++) {
    assert((*image_ptr)[i].size() == n);
  }
  bool color = (*image_ptr)[x][y];
  (*image_ptr)[x][y] = !color;
  for (auto [p,q] : generate_adjacents(x,y,n,n)) {
      if ((*image_ptr)[p][q] == color) {
          FlipColor(p,q,image_ptr);
      }
  }
  return;
}

vector<vector<int>> FlipColorWrapper(TimedExecutor& executor, int x, int y,
                                     vector<vector<int>> image) {
  vector<deque<bool>> b;
  b.reserve(image.size());
  for (const vector<int>& row : image) {
    deque<bool> tmp;
    tmp.resize(row.size());
    for (int i = 0; i < row.size(); ++i) {
      tmp[i] = static_cast<bool>(row[i]);
    }
    b.push_back(tmp);
  }

  executor.Run([&] { FlipColor(x, y, &b); });

  image.resize(b.size());

  for (int i = 0; i < image.size(); ++i) {
    image[i].resize(b.size());
    for (int j = 0; j < image[i].size(); ++j) {
      image[i][j] = b[i][j];
    }
  }
  return image;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "x", "y", "image"};
  return GenericTestMain(args, "matrix_connected_regions.cc", "painting.tsv",
                         &FlipColorWrapper, DefaultComparator{}, param_names);
}

