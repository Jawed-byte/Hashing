#include <bits/stdc++.h>

using namespace std;

int main() {
    int test_cases;
    cin >> test_cases;
    
    for (int t = 0; t < test_cases; t++) {
        int n;
        cin >> n;

        map<long long, string> A;
        for (int i = 0; i < n; i++) {
            int type;
            long long qi;
            cin >> type >> qi;
            if (type) {
                bool contains = A.count(qi);
                if (contains) {
                    cout << A[qi] << '\n';
                } else {
                    cout << "0\n";
                }
            } else {
                string s;
                cin >> s;
                A[qi] = s;
            }
        }
    }

    return 0;
}