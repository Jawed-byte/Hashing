# Concept of Polynomial Hashing

Polynomial hashing is a method to convert a string into a numeric value (hash) by treating the string like the coefficients of a polynomial evaluated at a certain base `p`. Each character is mapped to an integer, and the hash is computed as:

$$
\text{hash}(s) = \sum_{i=0}^{L-1} (s[i] - 'a' + 1) \times p^i \mod m
$$


- `p` is a chosen base, usually a small prime (e.g., 31, 127), which serves as the polynomial base.
- `m` is a large prime modulus that keeps the hash value within integer limits and reduces collisions.
- The polynomial representation helps distribute hash values uniformly over the possible range.
- Using modulo arithmetic ensures the hash fits in a fixed size integer and prevents overflow.

By computing the hash in this way, strings that differ even by a single character tend to have very different hash values, minimizing collisions.

---

# Implementation Steps

1. **Choose parameters:**
   - Select one or more pairs of primes `(p, m)` for the base and modulus.
   - Using multiple `(p, m)` pairs improves collision resistance by generating multiple independent hashes.

2. **Convert characters to integers:**
   - Map each character in the string to an integer (commonly `c - 'a' + 1` for lowercase alphabets).

3. **Compute the polynomial hash:**
   - Initialize the hash value to zero and `p_pow` to 1.
   - Iterate over the string characters from left to right.
   - For each character, multiply its integer value by `p_pow` and add it to the hash.
   - Update `p_pow` by multiplying by `p` (mod `m`).
   - Take modulo `m` at each step to keep values within bounds.

4. **Combine multiple hashes:**
   - Compute hashes using different `(p, m)` pairs to create a tuple of hash values.
   - This tuple represents the string’s final hash, reducing false positives due to collisions.

5. **Use the hashes:**
   - Store computed hash tuples to quickly detect duplicates or compare strings without direct string comparison.
   - Because the hash is numeric, lookups and comparisons are efficient.

---

This approach provides a fast and reliable way to hash strings, widely used in text algorithms, substring search, and duplicate detection.
