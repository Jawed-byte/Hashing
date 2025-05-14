#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;

    set<string> observed;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        bool present = observed.count(s);
        cout << present << '\n';
        if (!present) {
            observed.insert(s);
        }
    }

    return 0;
}
