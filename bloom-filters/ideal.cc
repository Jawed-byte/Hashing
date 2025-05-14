#include <iostream>
#include <string>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int test_cases;
    std::cin >> test_cases;
    for (int t = 0; t < test_cases; t++) {
        int n;
        std::cin >> n;

        std::set<std::string> observed;

        for (int i = 0; i < n; i++) {
            std::string s;
            std::cin >> s;
            bool present = observed.count(s);
            std::cout << present << '\n';
            if (!present) {
                observed.insert(s);
            }
        }
    }

    return 0;
}
