---
title: Theory Quiz III, 2025
---

# Theory Quiz III, 2025

<PaperHeader :rows="[
  ['Course', 'Data Structures, CTN301 / AIN301 / DTN301, batch 25261 (last year)'],
  ['Format', '10 questions, 1 mark each, 10 minutes'],
  ['Covers', 'Binary trees (Unit 5) and BST, AVL, B-tree (Unit 6)'],
]" />

<QuizTimer :minutes="10" label="Theory Quiz III" />

::: info Likely shape of your Theory Quiz 3
Last year's third quiz came after trees, BSTs, AVL and B-trees. Q5–Q8 are **Unit 5** and in your mid-semester syllabus; the rest are Unit 6 (after the mid-semester).
:::

<Q id="QA3.Q1">

A Binary Search Tree (BST) contains the value 5, 6, 7, 8, 9, 10, 11 and 12. Which of the following sequences is a valid preorder traversal of the BST?

<Mcq :options="['9,7,5,6,8,11,12,10', '9,4,5,6,8,11,10,12', '9,7,5,6,10,8,12,11', '9,7,5,6,8,11,10,12']" answer="d">

Root 9: left subtree {5…8}, right {10…12}. (d): 9 | 7, 5, 6, 8 | 11, 10, 12: 7 with 5 (and 6 as 5's right child) on the left and 8 on the right; 11 with 10 and 12. Valid. (a) lists 12 before 10, but 10 is in 11's left subtree and must come first; (b) contains 4, which isn't in the tree; (c) puts 10 inside 9's left subtree.

</Mcq>

</Q>

<Q id="QA3.Q2">

The following numbers are inserted into an empty BST in the given order: 11, 2, 4, 6, 16, 13, 17. What is the height of the BST, if height of leaf node is 0?

<FillIn q="Height:" answer="3">

11 → 2 → 4 → 6 is the longest path: 3 edges. The right side (16 with 13 and 17) has height 2.

</FillIn>

</Q>

<Q id="QA3.Q3">

In delete operation of BST, we need inorder successor (or predecessor) of a node when the node to be deleted has both left and right child as non-empty. Which of the following is true about inorder successor needed in delete operation?

<Mcq :options="['Inorder Successor is always a leaf node', 'Inorder successor may be an ancestor of the node', 'Inorder successor is always either a leaf node or a node with empty left child', 'Inorder successor is always either a leaf node or a node with empty right child']" answer="c">

With two children, the successor is the **leftmost node of the right subtree**: it has no left child (it may have a right child), so it is a leaf or a node with an empty left child. It is never an ancestor, because the right subtree exists.

</Mcq>

</Q>

<Q id="QA3.Q4">

Which of the following statements is/are true? S1: BST is Subset of AVL. S2: B-tree may suffer from skewness.

<Mcq :options="['Only S1', 'Only S2', 'Both S1 and S2', 'Neither S1 nor S2']" answer="d">

S1 is backwards: every AVL tree is a BST, not the other way round. S2 is false: a B-tree keeps all leaves at the same depth, so it never skews. The sheet's "both" lost the mark.

</Mcq>

</Q>

<Q id="QA3.Q5">

What is the maximum number of nodes a BST can have if preorder and postorder traversal of the BST are identical?

<FillIn q="Answer:" answer="1">

Preorder starts with the root; postorder ends with it. They can be equal only if the root is the whole tree.

</FillIn>

</Q>

<Q id="QA3.Q6">

How many distinct binary trees can be made with three nodes (A, B, C)?

<FillIn q="Answer:" answer="30">

There are Catalan(3) = 5 shapes, and each can be labelled in 3! = 6 ways: **30**. The sheet's 15 lost the mark.

</FillIn>

</Q>

<Q id="QA3.Q7">

How many distinct BST can be made with three nodes (A, B, C) where A &lt; B ≤ C?

<FillIn q="Answer:" answer="5|five">

For a BST the keys decide the labels, so only the shapes count: Catalan(3) = 5.

</FillIn>

</Q>

<Q id="QA3.Q8">

If the inorder and preorder traversals of a binary tree are same, which statement is true?

<Mcq :options="['Tree has only one node', 'Tree is skewed to the right', 'Tree is skewed to the left', 'All nodes have two children']" answer="b">

Root-Left-Right equals Left-Root-Right only if there are no left children at all: a right-skewed tree. A single node is a special case of it, but (a) is not *necessarily* true.

</Mcq>

</Q>

<Q id="QA3.Q9">

In a B-tree of order m and total keys stored is n, the maximum number of key comparisons during search is:

<Mcq :options="['O(log m)', 'O(m logₘ n)', 'O(logₘ n)', 'O(n/m)']" answer="b">

The height is O(logₘ n) levels, and at each node a linear scan may compare with up to m − 1 keys: O(m logₘ n). (O(logₘ n) counts nodes visited, not comparisons, which is why the sheet's (c) was marked wrong.)

</Mcq>

</Q>

<Q id="QA3.Q10">

A BST stores values in the range 37 to 573. Suppose the BST has been unsuccessfully searched for key 273. Which among below sequences list nodes in the order in which we could have encountered them while searching?

<Mcq :options="['81, 537, 102, 439, 285, 376, 305', '52, 97, 121, 195, 242, 381, 472', '142, 248, 520, 386, 345, 270, 307', '550, 149, 507, 395, 463, 402, 270']" answer="c">

Keep a window that each node narrows. (c): 142 (go right: > 142), 248 (> 248), 520 (go left: &lt; 520), 386 (&lt; 386), 345 (&lt; 345), 270 (> 270), 307 (inside (270, 345)) ✓. (a) breaks at 376 (after 285 we must stay below 285); (b) at 472 (after 381, below 381); (d) at 463 (after 395, below 395).

</Mcq>

</Q>
