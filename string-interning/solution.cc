#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class StringPool {
private:
    std::unordered_map<std::string, size_t> index;
    std::unordered_map<size_t, std::string> invertedIndex;
public:
    size_t add(std::string const&);
    std::string const& get(size_t);
};

class PooledAssociateArray {
private:
    StringPool pool;
    std::unordered_map<long long, size_t> index;
public:
    void put(long long, std::string const&);
    std::string const& get(long long);
    PooledAssociateArray(std::string const& defaultValue);
};

int main() {
    int testCases;
    std::cin >> testCases;

    for (int tc = 0; tc < testCases; tc++) {
        int n;
        std::cin >> n;

        PooledAssociateArray arr("0");
        for (int q = 0; q < n; q++) {
            int type;
            long long qi;
            std::cin >> type >> qi;

            if (type) {
                std::string response = arr.get(qi);
                std::cout << response << '\n';
            } else {
                std::string s;
                std::cin >> s;
                arr.put(qi, s);
            }
        }
    }

    return 0;
}

size_t StringPool::add(std::string const& s) {
    index.try_emplace(s, index.size());
    size_t pos = index[s];
    invertedIndex.try_emplace(pos, s);
    return pos;
}

std::string const& StringPool::get(size_t pos) {
    return invertedIndex[pos];
}

PooledAssociateArray::PooledAssociateArray(std::string const& defaultValue) {
    pool.add(defaultValue);
}

void PooledAssociateArray::put(long long key, std::string const& value) {
    index[key] = pool.add(value);
}

std::string const& PooledAssociateArray::get(long long key) {
    size_t pos = index[key];
    return pool.get(pos);
}
