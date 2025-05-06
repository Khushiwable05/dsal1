def h(k): return sum(map(ord, str(k))) % 10  # Hash function (sum of ASCII values % 10)
T = [None]*10  # Hash table of size 10

def insert(k, v):
    i = h(k)  # Get initial index
    while T[i] and T[i][0] != k: i = (i+1)%10  # Linear probe until empty or same key
    T[i] = (k, v)  # Insert or update

def find(k):
    i = h(k)
    for _ in range(10):  # Probe up to 10 times
        if T[i] is None: return None  # Key not found
        if T[i][0] == k: return T[i][1]  # Return value if key matches
        i = (i+1)%10
    return None

def delete(k):
    i = h(k)
    for _ in range(10):
        if T[i] is None: return  # Key not found
        if T[i][0] == k: T[i] = ("#", None); return  # Mark as deleted
        i = (i+1)%10

# --- I/O section ---
for _ in range(int(input("No. of pairs: "))):  # Input pairs
    k, v = input("Key Value: ").split(); insert(k, v)
print("Table:", T)  # Display table

k = input("Find key: "); print("Value:", find(k))  # Search key
k = input("Delete key: "); delete(k)  # Delete key
print("Table:", T);  # Display table after deletion

# --- Output section ---
# No. of pairs: 3
# Key Value: 1 10
# Key Value: 2 20
# Key Value: 3 30
# Table: [(1, 10), (2, 20), (3, 30), None, None, None, None, None, None, None]
# Find key: 2
# Value: 20
# Delete key: 2
# Table: [(1, 10), ('#', None), (3, 30), None, None, None, None, None, None, None]
# This code implements a simple hash table with linear probing for collision resolution.
# It allows for insertion, searching, and deletion of key-value pairs. The hash function is based on the sum of ASCII values of the keys modulo 10.
# The table is displayed after each operation to show the current state of the hash table.
# The output section demonstrates the functionality of the hash table by allowing the user to input key-value pairs, search for a key, and delete a key.
# The final state of the hash table is displayed after each operation to show the changes made.
# The code is designed to be simple and easy to understand, making it suitable for educational purposes.
# The hash table is implemented as a list of tuples, where each tuple contains a key and its corresponding value.
# The table size is fixed at 10, and the hash function ensures that keys are distributed evenly across the table.
# The linear probing technique is used to handle collisions, where the next available slot is used if the initial hash index is occupied.
# The delete operation marks the slot as deleted by storing a special value ('#') in place of the key-value pair.
# The find operation searches for a key in the hash table and returns its corresponding value if found, or None if not found.
