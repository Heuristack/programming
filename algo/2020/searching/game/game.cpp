#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

using namespace std;

class player
{
public:
    player(string const & n): name(n) {}

public:
    string name;
};

class game
{
public:
    game(initializer_list<player> const & players) : players(players) {}

public:
    vector<player> players;
};

int main()
{
    cout << "game: playing!" << endl;
}

