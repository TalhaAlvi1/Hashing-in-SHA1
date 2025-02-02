#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <bitset>
#include <cstdint>  // Include this header for uint32_t, uint64_t, and uint8_t

using namespace std;

uint32_t leftRotate(uint32_t value, uint32_t bits) {
    return (value << bits) | (value >> (32 - bits));
}

string sha1(const string &input) {
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    uint64_t inputBits = input.size() * 8;
    string paddedInput = input + char(0x80);
    while ((paddedInput.size() * 8) % 512 != 448) {
        paddedInput += char(0x00);
    }

    for (int i = 7; i >= 0; --i) {
        paddedInput += char((inputBits >> (i * 8)) & 0xFF);
    }

    for (size_t chunk = 0; chunk < paddedInput.size(); chunk += 64) {
        uint32_t words[80] = {0};

        for (int i = 0; i < 16; ++i) {
            words[i] = (uint8_t(paddedInput[chunk + i * 4 + 0]) << 24) |
                       (uint8_t(paddedInput[chunk + i * 4 + 1]) << 16) |
                       (uint8_t(paddedInput[chunk + i * 4 + 2]) << 8) |
                       (uint8_t(paddedInput[chunk + i * 4 + 3]));
        }

        for (int i = 16; i < 80; ++i) {
            words[i] = leftRotate(words[i - 3] ^ words[i - 8] ^ words[i - 14] ^ words[i - 16], 1);
        }

        uint32_t a = h0, b = h1, c = h2, d = h3, e = h4;

        for (int i = 0; i < 80; ++i) {
            uint32_t f, k;
            if (i < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (i < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (i < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }
            uint32_t temp = leftRotate(a, 5) + f + e + k + words[i];
            e = d;
            d = c;
            c = leftRotate(b, 30);
            b = a;
            a = temp;
        }
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }
    stringstream ss;
    ss << hex << setw(8) << setfill('0') << h0
       << setw(8) << setfill('0') << h1
       << setw(8) << setfill('0') << h2
       << setw(8) << setfill('0') << h3
       << setw(8) << setfill('0') << h4;
    return ss.str();
}

int main() {
    string input;
    cout << "Enter the string to hash: ";
    getline(cin, input);

    string hash = sha1(input);
    cout << "SHA-1 Hash: " << hash << endl;

    return 0;
}