# Bloom Filter – Concept and Implementation

## Concept of Bloom Filters

A **Bloom Filter** is a space-efficient probabilistic data structure used to test whether an element is a member of a set.

- It can tell you if an element is **definitely not** in the set or **might be** in the set.
- It **allows false positives** but **never false negatives**.

**In other words:**
- If the filter says an element is _not present_, it's **definitely not present** 
- If it says an element _is present_, it **might or might not be** (i.e., could be a false positive)

---

## Use Cases

- Web caches (to check if a URL is in cache)
- Database query optimization
- Networking (to avoid repeated transmission of the same data)
- Security and blockchain systems

---

## Key Parameters

When initializing a Bloom filter, we typically know:

- `n`: number of elements we expect to insert
- `ε` (epsilon): acceptable false positive probability

From these, we derive:

- `m`: number of bits in the bit array  
  Formula:  


- `k`: number of hash functions  
Formula:  


---

## Bloom Filter: Implementation Steps

### 1. Bit Table Initialization
- Create a boolean vector `table` of size `m`, initialized to `false`
- This table represents the Bloom filter’s bit array

### 2. Hash Functions
- Simulate `k` different hash functions using different combinations of:
- Prime numbers `p[i]`
- Moduli `m[i]`
- Each hash maps the input string to an index in the range `[0, m-1]`

### 3. Insert Operation
To insert a string `s`:
- Compute `k` different hashes using the chosen primes and moduli
- For each hash value:
- Compute the index
- Set the corresponding bit in the `table` to `true`

### 4. Contains Operation
To check whether a string `s` is possibly in the set:
- Compute the same `k` hash positions
- If **any** of the bits at those positions is `false`, the element is **definitely not present**
- If **all** are `true`, the element **might be present** (could be a false positive)

---

## Efficiency and Trade-off

- Bloom filters offer:
- **Constant time** insert and query operations
- **Very low space** usage compared to sets
- Trade-off:
- Allowance of **false positives**
- False positive rate can be minimized by tuning `m` and `k`

---

## In the Given Implementation

- A large list of prime numbers is used to simulate independent hash functions
- For each test case:
- A Bloom filter is initialized with `n` and a very small error probability (`1e-15`)
- Each input string is:
  - Checked for presence
  - Printed (`0` for new, `1` for seen before)
  - Inserted if not already present

This approach ensures a **scalable** and **memory-efficient** way to track large volumes of data with **low false positives**, which is the primary advantage of Bloom filters.

