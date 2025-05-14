#include <iostream>
#include <string>
#include <unordered_set>

int main() {
    int test_cases;
    std::cin >> test_cases;
    for (int t = 1; t <= test_cases; t++) {
        int n;
        std::cin >> n;

        std::unordered_set<std::string> set;
        for (int i = 0; i < n; i++) {
            int type;
            std::string str;
            std::cin >> type >> str;

            switch (type) {
                case 0: {
                    std::cout << set.count(str) << '\n';
                    set.insert(str);
                    break;
                }
                case 1: {
                    std::cout << set.count(str) << '\n';
                    break;
                }
                case 2: {
                    std::cout << set.count(str) << '\n';
                    set.erase(str);
                    break;
                }
            }
        }
    }


    return 0;
}