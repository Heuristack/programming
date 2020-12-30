#include <istream>
#include <string>
#include <vector>
#include <utility>
#include <cassert>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
using std::pair;

enum class Color { kWhite, kBlack };

struct Coordinate
{
  Coordinate(int x, int y) : x(x), y(y) {}
  bool operator==(const Coordinate& that) const { return x == that.x && y == that.y; }
  int x, y;
};

template <typename return_type = vector<pair<int,int>>>
auto generate(int i, int j, int m, int n) -> return_type
{
  return_type adjancets;
  for (auto [p,q] : return_type{{i-1,j},{i+1,j},{i,j-1},{i,j+1}}) {
    if ((0 <= p) && (p < m) && (0 <= q) && (q < n)) {
      adjancets.emplace_back(p,q);
    }
  }
  return adjancets;
}

bool Search(vector<vector<Color>> & maze, vector<Coordinate> & path, const Coordinate & s, const Coordinate & e)
{
  if (s == e) return true;
  for (auto [p,q] : generate(s.x,s.y,maze.size(),maze[s.x].size())) {
    if (maze[p][q] == Color::kWhite) {
      Coordinate n(p,q);
      maze[p][q] = Color::kBlack;
      path.push_back(n);
      if (Search(maze,path,n,e)) {
          return true;
      }
      path.pop_back();
    }
  }
  return false;
}

vector<Coordinate> SearchMaze(vector<vector<Color>> maze, const Coordinate & s, const Coordinate & e)
{
  if (maze.empty()) return {};
  for (int i = 1; i < maze.size(); i++) { assert(maze[i].size() == maze[i-1].size()); }
  vector<Coordinate> path;
  maze[s.x][s.y] = Color::kBlack;
  path.push_back(s);
  if (!Search(maze,path,s,e)) {
    path.pop_back();
  }
  return path;
}

namespace test_framework {
template <>
struct SerializationTrait<Color> : SerializationTrait<int> {
  using serialization_type = Color;

  static serialization_type Parse(const json& json_object) {
    return static_cast<serialization_type>(
        SerializationTrait<int>::Parse(json_object));
  }
};
}  // namespace test_framework

namespace test_framework {
template <>
struct SerializationTrait<Coordinate> : UserSerTrait<Coordinate, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {};
  }

  static std::vector<int> GetMetrics(const Coordinate& x) { return {}; }
};
}  // namespace test_framework

bool PathElementIsFeasible(const vector<vector<Color>>& maze,
                           const Coordinate& prev, const Coordinate& cur) {
  if (!(0 <= cur.x && cur.x < maze.size() && 0 <= cur.y &&
        cur.y < maze[cur.x].size() && maze[cur.x][cur.y] == Color::kWhite)) {
    return false;
  }
  return cur == Coordinate{prev.x + 1, prev.y} ||
         cur == Coordinate{prev.x - 1, prev.y} ||
         cur == Coordinate{prev.x, prev.y + 1} ||
         cur == Coordinate{prev.x, prev.y - 1};
}

bool SearchMazeWrapper(TimedExecutor& executor,
                       const vector<vector<Color>>& maze, const Coordinate& s,
                       const Coordinate& e) {
  vector<vector<Color>> copy = maze;

  auto path = executor.Run([&] { return SearchMaze(copy, s, e); });

  if (path.empty()) {
    return s == e;
  }

  if (!(path.front() == s) || !(path.back() == e)) {
    throw TestFailure("Path doesn't lay between start and end points");
  }

  for (size_t i = 1; i < path.size(); i++) {
    if (!PathElementIsFeasible(maze, path[i - 1], path[i])) {
      throw TestFailure("Path contains invalid segments");
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "maze", "s", "e"};
  return GenericTestMain(args, "search_maze.cc", "search_maze.tsv",
                         &SearchMazeWrapper, DefaultComparator{}, param_names);
}
