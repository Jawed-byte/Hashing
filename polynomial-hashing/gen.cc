#include <iostream>
#include <string>
#include <random>

using namespace std;

string randstr(int length, mt19937& rng) {
    string s;
    uniform_int_distribution<char> dist('a', 'z');

    for (int i = 0; i < length; i++) {
        s += dist(rng);
    }
    return s;
}

int main() {
    int n = 100'000;
    cout << n << '\n';

    // Initialize the random number generator with a random seed
    random_device rd;
    mt19937 rng(rd());

    for (int i = 0; i < n; i++) {
        string s = randstr(600+rand()%400, rng);
        cout << s << '\n';
    }

    return 0;
}
