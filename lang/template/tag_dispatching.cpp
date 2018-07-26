#include <iostream>
using namespace std;

int tag_dispatch(int i, enum class tag1){ return i + 1; }
int tag_dispatch(int i, enum class tag2){ return i + 2; }

template<typename tag>
int tag_dispatch(int i) { return tag_dispatch(i, tag()); }

int main()
{
    std::cout << tag_dispatch<tag1>(6) << std::endl;
    std::cout << tag_dispatch<tag2>(6) << std::endl;
}

