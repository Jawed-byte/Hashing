#include <iostream>
#include <string>
#include <vector>
#include <utility>

const int p[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1009,1013,1019,1021,1031,1033,1039,1049,1051,1061,1063,1069,1087,1091,1093,1097,1103,1109,1117,1123,1129,1151,1153,1163,1171,1181,1187,1193,1201,1213,1217,1223};
const int m[] = {100000007,100000037,100000039,100000049,100000073,100000081,100000123,100000127,100000193,100000213,100000217,100000223,100000231,100000237,100000259,100000267,100000279,100000357,100000379,100000393,100000399,100000421,100000429,100000463,100000469,100000471,100000493,100000541,100000543,100000561,100000567,100000577,100000609,100000627,100000643,100000651,100000661,100000669,100000673,100000687,100000717,100000721,100000793,100000799,100000801,100000837,100000841,100000853,100000891,100000921,100000937,100000939,100000963,100000969,100001029,100001053,100001059,100001081,100001087,100001107,100001119,100001131,100001147,100001159,100001177,100001183,100001203,100001207,100001219,100001227,100001303,100001329,100001333,100001347,100001357,100001399,100001431,100001449,100001467,100001507,100001533,100001537,100001569,100001581,100001591,100001611,100001623,100001651,100001653,100001687,100001689,100001719,100001761,100001767,100001777,100001791,100001801,100001809,100001813,100001819,100001821,100001827,100001843,100001887,100001893,100001903,100001927,100001929,100001983,100001987,100002011,100002013,100002017,100002031,100002037,100002059,100002103,100002113,100002127,100002139,100002163,100002167,100002169,100002173,100002181,100002223,100002233,100002251,100002271,100002283,100002289,100002337,100002349,100002389,100002421,100002431,100002437,100002493,100002499,100002503,100002509,100002541,100002569,100002571,100002589,100002593,100002611,100002613,100002629,100002641,100002647,100002671,100002673,100002677,100002737,100002751,100002769,100002797,100002839,100002863,100002899,100002937,100002941,100002943,100002961,100002967,100002979,100003021,100003037,100003063,100003091,100003151,100003153,100003157,100003181,100003219,100003243,100003247,100003259,100003273,100003279,100003283,100003291,100003301,100003313,100003331,100003349,100003361,100003381,100003417,100003447,100003481,100003499,100003549,100003559,100003573,100003601,100003619,100003621,100003679};

// TODO: Add shrinkage on erasure basis load-factor
class CuckooHash {
private:
    int compute_hash(std::string const& s, int p, int m) {
        long long hash_value = 0;
        long long p_pow = 1;
        for (char c : s) {
            hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return (int) hash_value;
    }

    int compute_first_hash(std::string const& s) {
        int pi = p[curr_hash];
        int mi = m[curr_hash];
        return compute_hash(s, pi, mi);
    }

    int compute_second_hash(std::string const& s) {
        int pi = p[curr_hash + 1];
        int mi = m[curr_hash + 1];
        return compute_hash(s, pi, mi);
    }

    void rehash(int new_capacity) {
        std::vector<std::string> old;
        for (std::string const& str : table) {
            if (str != "") {
                old.push_back(str);
            }
        }

        curr_hash++;
        capacity = new_capacity;
        table.clear();
        table.resize(capacity, "");
        for (std::string const& str : old) {
            insert(str);
        }
    }

    size_t size, capacity, curr_hash, max_pushes;
    double load_upper_limit;
    std::vector<std::string> table;

public:
    CuckooHash() : size(0), capacity(15), curr_hash(0), max_pushes(25), load_upper_limit(0.5), table(capacity, "") {}

    bool contains(std::string const& s) {
        int first_pos = compute_first_hash(s) % capacity;
        if (table[first_pos] == s) {
            return true;
        }

        int second_pos = compute_second_hash(s) % capacity;
        return table[second_pos] == s;
    }

    bool erase(std::string const& s) {
        int first_pos = compute_first_hash(s) % capacity;
        if (table[first_pos] == s) {
            table[first_pos] = "";
            size--;
            return true;
        }

        int second_pos = compute_second_hash(s) % capacity;
        if (table[second_pos] == s) {
            table[second_pos] = "";
            size--;
            return true;
        }
        return false;
    }

    bool insert(std::string const& s) {
        if (contains(s)) {
            return true;
        }

        int first_pos = compute_first_hash(s) % capacity;
        if (table[first_pos] == "") {
            table[first_pos] = s;
            size++;

            double load = (double) size / capacity;
            if (load > load_upper_limit) {
                rehash(capacity << 1 | 1);
            }
            return false;
        }

        std::string curr = table[first_pos];
        table[first_pos] = s;
        for (int i = 0; i < max_pushes; i++) {
            int second_pos = compute_second_hash(curr) % capacity;
            if (table[second_pos] == "") {
                table[second_pos] = curr;
                size++;

                double load = (double) size / capacity;
                if (load > load_upper_limit) {
                    rehash(capacity << 1 | 1);
                }
                return false;
            }
            std::swap(curr, table[second_pos]);
        }

        rehash(capacity);
        insert(curr);
        return false;
    }
};

int main() {
    int test_cases;
    std::cin >> test_cases;

    for (int t = 0; t < test_cases; t++) {
        int n;
        std::cin >> n;

        CuckooHash set;
        for (int i = 0; i < n; i++) {
            int type;
            std::string str;
            std::cin >> type >> str;

            switch (type) {
                case 0: {
                    std::cout << set.contains(str) << '\n';
                    set.insert(str);
                    break;
                }
                case 1: {
                    std::cout << set.contains(str) << '\n';
                    break;
                }
                case 2: {
                    std::cout << set.contains(str) << '\n';
                    set.erase(str);
                    break;
                }
            }
        }
    }

    return 0;
}