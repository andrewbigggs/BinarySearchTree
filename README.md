# BinarySearchTree

This is a program that builds a Binary Search Tree by reading and storing 
data from a comma separated values file according to the BST ordering property. 
It can perform inorder, post-order, and pre-order tree traversals. It can 
determine if a specific data point exists in the tree and remove specific 
data points and reorder the tree according to the BST ordering property.

​In developing this program, I ran into several roadblocks. One of them was 
ensuring that the input in the main() while loop was good. At first, 
bad input created an infinite loop. I tried to use cin.bad() but some of 
the time it wasn’t registering as true even when cin.fail() was true. 
I ended up creating an if statement that was a catch-all for input that 
either wasn’t a menu option or caused a failbit. There was also an issue 
with the removal operation deleting too many nodes. I spent hours thinking 
about the recursive logic in the binary search tree. I ended up adding
a couple more methods for holding onto parent nodes and using that recursive 
logic.