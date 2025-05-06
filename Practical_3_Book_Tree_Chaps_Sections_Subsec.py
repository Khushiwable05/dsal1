class Node:
    def __init__(self, name): self.name = name; self.children = []
    def add(self, child): self.children.append(child)
    def print_tree(self, level=0):
        print("  " * level + self.name)
        for c in self.children: c.print_tree(level + 1)

book = Node("Book: Computer Science")

# Chapter, Section, and Subsection data
structure = {
    "Chapter 1: Introduction": {
        "Section 1.1: What is CS?": [
            "Subsection 1.1.1: Definition",
            "Subsection 1.1.2: Applications"
        ],
        "Section 1.2: History": []
    },
    "Chapter 2: Data Structures": {
        "Section 2.1: Arrays": [],
        "Section 2.2: Linked Lists": []
    }
}

# Build tree
for ch_title, sections in structure.items():
    ch = Node(ch_title)
    for sec_title, subsecs in sections.items():
        sec = Node(sec_title)
        for sub in subsecs: sec.add(Node(sub))
        ch.add(sec)
    book.add(ch)

book.print_tree()

# Output:
# Book: Computer Science
#   Chapter 1: Introduction
#     Section 1.1: What is CS?
#       Subsection 1.1.1: Definition
#       Subsection 1.1.2: Applications
#     Section 1.2: History
#   Chapter 2: Data Structures
#     Section 2.1: Arrays
#     Section 2.2: Linked Lists
# This code creates a tree structure representing a book with chapters, sections, and subsections.
# Each node in the tree represents a chapter, section, or subsection, and the tree is printed in a hierarchical format.
# The tree structure is built using a dictionary to represent the hierarchy of chapters, sections, and subsections.
# The `Node` class is used to create nodes for the tree, and the `print_tree` method is used to display the tree structure.
# The output shows the hierarchical structure of the book, with indentation indicating the level of each node in the tree.
