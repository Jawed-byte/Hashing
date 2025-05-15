# Custom Unordered Map Implementation in C++

## Overview

This repository contains a custom implementation of an **unordered map** (hash map) data structure in C++ using **separate chaining** for collision resolution. The implementation supports generic key-value pairs via templates and includes common map operations such as insertion, deletion, lookup, resizing, and more.

The `unorderedmap` class provides a hash table-based associative container that maps keys to values with average **O(1)** time complexity for insertions, deletions, and lookups.

---

## Implementation Details

### Data Structures

- **Vector class (template)**  
  A custom dynamic array implementation used to hold buckets.

- **Node class**  
  Represents a key-value pair node used in linked lists for separate chaining.

- **unorderedmap class (template)**  
  The main hash map class managing buckets, hashing, and core operations.

---

### Key Components

#### Vector

- Manages a dynamic array with:
  - Capacity management (doubling capacity on overflow).
  - Push back and pop back operations.
  - Operator overload for indexing.

#### Node

- Stores:
  - Key (`key`)
  - Value (`val`)
- Pointer to the next node in the linked list (for collision handling).

#### unorderedmap Class

##### Hash Function

- Uses a custom multiplicative hash based on the **string representation** of the key.
- Converts any key type to string via `ostringstream`.
- Mixes bits using bit shifts and XORs to distribute keys uniformly.
- Applies modulo operation with the number of buckets (`cap`) to map the hash to a bucket index.

---

### Core Methods

- **Constructor**  
  Initializes buckets with an initial capacity of 5.

- **insert(key, val)**  
  Inserts a key-value pair:  
  - Checks for duplicate keys.  
  - Inserts new nodes at the head of the bucket's linked list.  
  - Triggers rehashing (doubling bucket size) when load factor exceeds 1.

- **erase(key)**  
  Removes a key-value pair if present.

- **contains(key)**  
  Returns whether a key exists in the map.

- **operator[]**  
  Accesses value by key; inserts a default value if key does not exist.

- **clear()**  
  Clears the entire map.

- **size()**  
  Returns the number of key-value pairs stored.

- **empty()**  
  Returns whether the map is empty.

- **keys()**  
  Returns a vector containing all keys currently stored in the map.

---

### Rehashing

- Triggered when load factor (number of elements / buckets) exceeds threshold (default = 1).
- Doubles the capacity.
- Re-inserts all existing elements into new buckets.


