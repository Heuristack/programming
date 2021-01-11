#include <iostream>
#include <bitset>
#include <string>

using namespace std;

short count_bits(unsigned long x)
{
    short num_bits = 0;
    while (x) {
        num_bits += x & 1;
        x >>= 1;
    }
    return num_bits;
}

int main()
{
   string bit_string = "110010";
   bitset<8> bits(bit_string);
   cout << bits << ":" << bits.count() << "," << count_bits(bits.to_ulong()) << endl;
}

