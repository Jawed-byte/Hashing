# Cuckoo Hashing

Cuckoo hashing is a collision resolution technique in hash tables that ensures **O(1) worst-case lookup time** by using multiple hash functions (typically two). The name comes from the behavior of cuckoo birds which push other eggs out of a nest—when an element is inserted into the hash table and its target position is occupied, it "kicks out" the existing element, which is then reinserted elsewhere.

---

## Key Ideas

- **Two hash functions:** each element has two possible positions.
- **Insertion:**  
  - If either of the two positions is empty, insert the element there.  
  - If both positions are occupied, evict the existing element at one position, and reinsert it using its alternative hash function.  
  - This eviction can trigger a chain of displacements.
- **Rehashing:**  
  - If the eviction chain becomes too long, the table is rehashed with new hash functions to reduce collisions.

---

## Implementation Steps

### Initialization

- Start with a fixed initial table size.
- Use two hash functions (with different primes) for computing two possible positions.
- Keep track of the current hash function index (`curr_hash`) to ensure hash function variability during rehashing.
- Set parameters such as:
  - Maximum eviction depth (`max_pushes`)
  - Load factor threshold (`load_upper_limit`)

### Hash Function Design

- Use **Polynomial Rolling Hash** for strings:  
- Choose primes `p` and `m` (from predefined arrays) to minimize collisions.

### Insertion

1. Check if the element already exists in either of the two candidate positions.
2. If an empty slot is found, insert directly.
3. If both positions are full:
 - Kick out the element from the first position.
 - Attempt to reinsert the evicted element into its alternate position.
4. Repeat the eviction process up to `max_pushes` times.
5. If insertion fails after many displacements, **rehash** the entire table.

### Lookup (Contains)

- Compute both hash positions.
- Check if the element exists at either position.

### Deletion

- Check both positions.
- If the element is found, remove it (set slot to empty) and decrement the size.

### Rehashing

Triggered when:

- Load factor exceeds the threshold after insertion.
- Insertion fails after too many displacements.

Process:

- Increase capacity (usually doubling + 1 to maintain prime size).
- Choose new hash functions (increment `curr_hash` to select next primes).
- Reinsert all existing elements into the new table.

---

## Advantages

- **Constant-time lookup** due to at most two probes.
- **Effective collision resolution** without chaining or open addressing.
- **Predictable performance**, useful in real-time systems.
- Handles hash collisions with a **bounded search**, ensuring consistent performance.

---

This approach is particularly useful when consistent and predictable hash table performance is critical.
