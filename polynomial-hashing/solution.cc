#include <iostream>
#include <set>
#include <tuple>
#include <string>

using namespace std;

const int p[] = {3, 7, 31, 127};
const int m[] = {998244353, 1000000007, 1000000009, 2147483647};

int compute_hash(string const& s, int p, int m) {
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return (int) hash_value;
}

tuple<int, int, int, int> compute_hashes(string const& s) {
    return {
        compute_hash(s, p[0], m[0]),
        compute_hash(s, p[1], m[1]),
        compute_hash(s, p[2], m[2]),
        compute_hash(s, p[3], m[3])
    };
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;

    set<tuple<int, int, int, int>> observed_hashes;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        auto hashes = compute_hashes(s);
        bool present = observed_hashes.count(hashes);
        cout << present << '\n';
        if (!present) {
            observed_hashes.insert(hashes);
        }
    }

    return 0;
}
