# AVL Tree Based Map Implementation

## Overview

This project implements a generic `Map` class template in C++ using an **AVL tree** as the underlying data structure. The `Map` stores key-value pairs and supports efficient insertion, deletion, and search operations, all with guaranteed **O(log n)** time complexity due to self-balancing.

---

## Core Concepts

### Node Structure

- Each node contains:
  - A **key** of generic type `K`
  - A **value** of generic type `V`
  - Pointers to left and right child nodes
  - A `height` attribute to track the height of the node’s subtree

### AVL Tree Balancing

- The AVL tree maintains the property that the difference in height between left and right subtrees of any node (called the **balance factor**) is at most 1.
- After every insertion or deletion, the tree checks the balance factor of affected nodes.
- If unbalanced, the tree is rebalanced using **rotations**.

### Rotations

- **Left Rotation** and **Right Rotation** are used to restore balance.
- Rotations adjust the tree structure while maintaining the binary search tree property.
- Heights of affected nodes are updated accordingly.

---

## Operations

### Insertion

- Recursively traverse the tree to find the correct spot for the new key.
- If the key exists, update its associated value.
- Otherwise, create a new node.
- After insertion, update heights and perform rotations as needed to maintain balance.

### Deletion

- Recursively locate the node with the specified key.
- Handle three cases:
  - Node with two children: Replace with the inorder successor, then delete successor.
  - Node with one child: Replace node with its child.
  - Leaf node: Remove directly.
- After deletion, update heights and rebalance the tree.

### Search

- Standard binary search tree lookup by key.
- Used by methods such as `contains()` and `operator[]`.

---

## Additional Features

- `operator[]`: Access or insert a value by key, inserting a default value if key is not present.
- `empty()` and `size()`: Query the map state.
- `keys()`: Retrieve all keys in sorted order via inorder traversal.
- `clear()`: Remove all nodes.
- `lower_bound()` and `upper_bound()`: Return the smallest key greater or equal to, or strictly greater than, a given key.

---

## Summary

This implementation provides a balanced, ordered map structure supporting fast, reliable insertions, deletions, and lookups with guaranteed logarithmic complexity. It mimics many behaviors of standard map containers by leveraging an AVL tree for self-balancing.


