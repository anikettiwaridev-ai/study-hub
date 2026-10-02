---
title: Unit 5 · Trees
---

# Unit 5 · Trees

Terminology, the four ways to store a tree, binary-tree types and their formulas, BFS and the three DFS traversals, building a tree from two traversals, counting trees, and the recursive code the lab quiz blanks out. <span class="hl-legend">Highlighted lines</span> are the likely blanks.

::: info How this unit is examined
- **Mid-semester:** **new this year.** No past mid-semester paper had a tree question, because Unit 5 used to come after the mid-semester. Expect the end-semester's tree questions to move forward: traversals of a given tree, building a tree from inorder + postorder and giving its preorder ([Dec 2024 Q3d](../papers/endsem-2024#q3d)), BFS vs DFS sets ([Dec 2024 Q3c](../papers/endsem-2024#q3c)), a recursive count or height function. The [mock paper](../mock-mst#q5) has one.
- **Theory quiz:** counting distinct trees, which traversals coincide, heights, valid traversal sequences (last year's Quiz III).
- **Lab quiz:** countLeaves, height, traversals (last year's Lab Quiz II, which also had BST and AVL parts from Unit 6).
:::

## 1. The toolkit: terminology on one tree {#toolkit}

The slides' tree:

```text
              A
          /   |   \
         B    C    D
        / \  / \
       E   F G  H
         / | \
        I  J  K
```

| Term | Meaning | On this tree |
|---|---|---|
| root | the node with no parent | A |
| parent / child | directly above / below | B is the parent of E; B is a child of A |
| siblings | same parent | E and F; G and H |
| leaf | no children | E, I, J, K, G, H, D |
| internal node | not a leaf | A, B, C, F |
| ancestors | parent, its parent, … up to the root | of K: F, B, A |
| descendants | children, their children, … | of B: E, F, I, J, K |
| subtree | a node and all its descendants | |
| degree of a node | its number of children | degree(A) = 3, degree(B) = 2 |
| degree of the tree | the largest node degree | 3 |
| level | 1 + edges from the root (the slides) | level(A) = 1, level(F) = 3 |
| depth of a node | edges from the root | depth(K) = 3 |
| height of a node | edges on the longest path down to a leaf | height(B) = 2, height(leaf) = 0 |
| height of the tree | height of the root | 3 |

::: danger Two conventions; the question will pick one
The slides count **level** from 1 at the root but **depth and height** in edges (leaf height 0). Last year's Quiz III said "if the height of a leaf is 0"; Lab Quiz II's code returned **−1 for an empty tree**, so one node has height 0. If a question doesn't say, state your convention in one line.
:::

A tree is non-linear and hierarchical: file systems, organisation charts, syntax trees. It can also be defined recursively: a node plus a list of child trees, which is why most tree code is recursive.

## 2. Storing a tree {#representation}

1. **Node with child pointers**: data plus a pointer per child (and optionally a parent pointer). Fine when the number of children is fixed (a **k-ary tree**: at most k children; binary is k = 2).
2. **Left-child, right-sibling**: every node has exactly two pointers, to its **first child** and to its **next sibling**, so any tree becomes binary-shaped. In the slides' example A's left-child pointer goes to B, and B's right-sibling chain is B → C → D.
3. **Binary node**: data, `left`, `right`.
4. **Array** (binary trees): root at index 0; the children of index i are at **2i + 1** and **2i + 2**; the parent of i is at **(i − 1) / 2**. A missing child leaves its cell empty; an index past the array means no child.

The slides' array example, checked by running it:

```text
index:  0 1 2 3 4 5 6 7 8 9 10 11 12
value:  A B C D E F G - - H I  -  J          (- = empty cell)
```

::: code-group
<<< @/../code/ds/notes/u5-array-tree.cpp [Program]
<<< @/../code/ds/notes/u5-array-tree.out{txt} [Output]
:::

::: tip When the array is a good idea
A complete tree fills the array with no gaps, which is why heaps use it. A skewed tree of n nodes needs up to 2ⁿ − 1 cells. Index arithmetic is O(1); finding a parent from a node pointer needs an extra field.
:::

## 3. Kinds of binary tree, and the formulas {#types}

| Kind | Definition |
|---|---|
| **Full** (strict) | every node has 0 or 2 children |
| **Perfect** | full, and all leaves on the same level |
| **Complete** | every level full except possibly the last, which is filled **from the left** |
| **Skewed** | every node has at most one child (a linked list in disguise) |

Some books call a perfect tree "complete" and a complete tree "almost complete" (the slides mention this). A perfect tree is a special complete tree; a complete tree need not be full, and a full tree need not be complete.

**Formulas** (root at depth 0, height h in edges):

| Fact | Formula |
|---|---|
| most nodes at depth i | 2ⁱ |
| perfect tree of height h | 2ʰ leaves, 2ʰ − 1 internal nodes, **2ʰ⁺¹ − 1** nodes |
| perfect tree with n nodes | (n + 1)/2 leaves, height log₂(n + 1) − 1 |
| any full binary tree | leaves = internal nodes + 1 |
| n nodes, minimum height | ⌈log₂(n + 1)⌉ − 1, i.e. O(log n) |
| n nodes, maximum height | n − 1 (every internal node has one child) |

The slides write the perfect-tree height as "log₂(n+1)/2", which is meant as log₂((n + 1)/2).

## 4. Traversals {#traversals}

### Breadth-first (level order) uses a queue

Enqueue the root. Repeat: dequeue a node, visit it, enqueue its left then right child. The slides' tree:

```text
          A
        /   \
       B     C
      / \   / \
     D   E F   G
        / \
       H   I
```

| Visit | Queue afterwards (front → rear) |
|---|---|
| A | B C |
| B | C D E |
| C | D E F G |
| D | E F G |
| E | F G H I |
| F, G, H, I | (empties) |

BFS: **A B C D E F G H I**.

### Depth-first: preorder, inorder, postorder

| Order | Visit the root… | This tree |
|---|---|---|
| **Pre**order | **before** the subtrees: Root, Left, Right | A B D E H I C F G |
| **In**order | **between** them: Left, Root, Right | D B H E I A F C G |
| **Post**order | **after** them: Left, Right, Root | D H I E B F G C A |

::: tip The hand trick: walk around the tree
Trace a line around the outside of the tree, starting left of the root and keeping the tree on your right. Each node is passed three times: on its **left side** (that is the preorder moment), **underneath** it (inorder) and on its **right side** (postorder). List the nodes in the order you pass the side you need.
:::

::: code-group
<<< @/../code/ds/notes/u5-binary-tree.cpp#traversals [the three DFS orders]
<<< @/../code/ds/notes/u5-binary-tree.cpp#bfs{4,6,8,9} [BFS with a queue]
<<< @/../code/ds/notes/u5-binary-tree.cpp [Whole program]
<<< @/../code/ds/notes/u5-binary-tree.out{txt} [Output]
:::

The slides' exercise tree (a BST):

```text
               20
           /        \
         17          53
        /  \        /  \
      11    19    23    64
     /  \   /       \   /  \
    6   16 18       44 61  66
```

| Traversal | Order |
|---|---|
| BFS | 20 17 53 11 19 23 64 6 16 18 44 61 66 |
| Preorder | 20 17 11 6 16 19 18 53 23 44 64 61 66 |
| Inorder | 6 11 16 17 18 19 20 23 44 53 61 64 66 (sorted: it is a BST) |
| Postorder | 6 16 11 18 19 17 44 23 61 66 64 53 20 |

**Without recursion**, a stack replaces the call stack (a stack and a tree in one question is a natural exam combination):

::: code-group
<<< @/../code/ds/notes/u5-iterative.cpp#iterPre{8,9} [iterative preorder]
<<< @/../code/ds/notes/u5-iterative.cpp#iterIn{5,8} [iterative inorder]
<<< @/../code/ds/notes/u5-iterative.out{txt} [Output]
:::

All traversals are O(n) time. Recursive DFS uses O(h) stack space (h = height, up to n for a skewed tree); BFS's queue holds up to a whole level.

## 5. Building a tree from two traversals {#build}

**Inorder plus preorder, or inorder plus postorder, fixes the tree uniquely** (when the values are distinct). The root is the **first** preorder element or the **last** postorder element; it splits the inorder into the left subtree | root | right subtree. Recurse on each side, using the same number of elements from the other traversal.

Dec 2024 Q3d: postorder 8, 9, 6, 7, 4, 5, 2, 3, 1 and inorder 8, 6, 9, 4, 7, 2, 5, 1, 3.

| Step | Root (last of postorder part) | Inorder split | Postorder parts |
|---|---|---|---|
| 1 | **1** | [8 6 9 4 7 2 5] · 1 · [3] | left 8 9 6 7 4 5 2, right 3 |
| 2 | **2** (left of 1) | [8 6 9 4 7] · 2 · [5] | left 8 9 6 7 4, right 5 |
| 3 | **4** (left of 2) | [8 6 9] · 4 · [7] | left 8 9 6, right 7 |
| 4 | **6** (left of 4) | [8] · 6 · [9] | 8 and 9 are its children |

```text
            1
          /   \
         2     3
        / \
       4   5
      / \
     6   7
    / \
   8   9
```

Preorder: **1 2 4 6 8 9 7 5 3**. Checked by running both builders (the second is the mock paper's preorder + inorder):

::: code-group
<<< @/../code/ds/notes/u5-build-tree.cpp#fromPostIn [from postorder + inorder]
<<< @/../code/ds/notes/u5-build-tree.cpp#fromPreIn [from preorder + inorder]
<<< @/../code/ds/notes/u5-build-tree.out{txt} [Output]
:::

::: danger Preorder plus postorder is not enough
Preorder A B and postorder B A fit both "B is A's left child" and "B is A's right child". Without the inorder you cannot tell left from right. (It does work for a **full** binary tree, where no node has only one child.)
:::

## 6. Counting trees, and when traversals coincide {#counting}

| Question | Answer | For n = 3 |
|---|---|---|
| distinct binary tree **shapes** with n nodes | Catalan(n) = C(2n, n)/(n + 1) | 5 |
| distinct binary trees on n **labelled** nodes | Catalan(n) × n! | 5 × 6 = **30** |
| distinct **BSTs** on n distinct keys | Catalan(n) (the keys fix the labels) | **5** |
| possible pop orders of 1…n through a stack | Catalan(n) | 5 |

Catalan numbers: 1, 2, 5, 14, 42, 132. Last year's Quiz III: 15 was the class's wrong answer for the labelled count; 30 is right.

| If… | then the tree… |
|---|---|
| preorder = inorder | has no left children (right-skewed, or a single node) |
| inorder = postorder | has no right children (left-skewed) |
| preorder = postorder | has exactly **one** node |

**BFS vs DFS** (Dec 2024 Q3c): in a complete binary tree of 7 nodes, the first 3 by BFS are root, left child, right child; the first 3 by DFS (preorder) are root, left child, left-left grandchild. A − B = {right child}, so **|A − B| = 1**. (If DFS meant inorder, the first three would be the left-left grandchild, the left child and the left-right grandchild, and |A − B| = 2. Say which DFS you assume.)

## 7. Expression trees {#expression-trees}

Operators are internal nodes and operands are leaves. `((6+16)*19)+(23+(61-66))`:

```text
              +
          /       \
         *         +
        / \       / \
       +   19   23   -
      / \           / \
     6   16       61   66
```

**Inorder gives the infix (with brackets), preorder the prefix, postorder the postfix.** Postfix here: 6 16 + 19 * 23 61 66 − + +. This is why operands keep their order across all three notations ([Unit 3](./unit-3#mcq-tricks)).

## 8. Recursive tree functions (lab-quiz style) {#code}

::: tip One pattern for almost every tree function
Handle the **empty tree** (and sometimes the leaf), then combine the answers of the two subtrees: `f(root) = combine(root, f(root->left), f(root->right))`.
:::

::: code-group
<<< @/../code/ds/notes/u5-binary-tree.cpp#counts{5,6,10,11} [count nodes, count leaves, height]
<<< @/../code/ds/notes/u5-binary-tree.cpp#search [search]
<<< @/../code/ds/notes/u5-binary-tree.cpp#mirror [mirror]
:::

| Function | Empty tree | Leaf | Otherwise |
|---|---|---|---|
| countNodes | 0 | (covered) | 1 + left + right |
| countLeaves | 0 | **1** | left + right |
| height (edges) | **−1** | (gives 0) | 1 + max(left, right) |
| height (levels) | 0 | (gives 1) | 1 + max(left, right) |
| search (any binary tree) | false | | data == key, or left, or right: **O(n)** |
| mirror | nothing | | swap the children, then mirror both |

::: danger The blanks people miss
- countLeaves returns **1** for a leaf, not `root->data`.
- The height of an empty tree is **−1** when height counts edges, so a single node gets 0. Returning 0 there makes every height one too big.
- Searching a plain binary tree is O(n): there is no order to follow. A **binary search tree** (Unit 6, after the mid-semester) makes it O(h). The BST, AVL and LCA blanks are [on the Lab Quiz II page](../quizzes/2025-lab-2).
:::

## Traps and the 5-minute checklist {#traps}

| # | Trap | Correct version |
|---|---|---|
| 1 | mixing level (from 1) and depth/height (in edges) | state the convention |
| 2 | height of an empty tree = 0 in edge-counting code | −1 |
| 3 | preorder + postorder "builds the tree" | only with inorder (or for a full tree) |
| 4 | labelled trees on 3 nodes = 5 | 5 shapes × 3! = 30; BSTs on 3 keys = 5 |
| 5 | BFS with a stack | BFS uses a queue; iterative DFS uses a stack |
| 6 | iterative preorder pushes left first | push **right** first so left pops first |
| 7 | complete = full | complete: filled level by level from the left; full: 0 or 2 children |
| 8 | array children at 2i and 2i + 1 | with the root at 0: 2i + 1 and 2i + 2; parent (i − 1)/2 |

**The checklist:** draw the tree before answering · write the traversal order rule at the top (Root-Left-Right…) · for building, take the root from pre/post and split the inorder · for code, empty tree first.

## Quick check {#quick-check}

<Drill n="1" tag="Traversal">

<FillIn q="Postorder of the slides' tree (A; B, C; D, E under B; F, G under C; H, I under E)? Letters with spaces." answer="D H I E B F G C A">

Left, right, root: the left subtree of A gives D H I E B, the right gives F G C, then A.

</FillIn>

</Drill>

<Drill n="2" tag="Build">

<FillIn q="Postorder 8 9 6 7 4 5 2 3 1, inorder 8 6 9 4 7 2 5 1 3. Preorder? Numbers with spaces." answer="1 2 4 6 8 9 7 5 3">

Root 1 (last of postorder); left part 8 6 9 4 7 2 5 has root 2, then 4, then 6. Dec 2024 Q3d.

</FillIn>

</Drill>

<Drill n="3" tag="Counting">

How many distinct binary trees can be made with three labelled nodes A, B, C?

<Mcq :options="['5', '6', '15', '30']" answer="d">

5 shapes, each labelled in 3! = 6 ways: 30. (BSTs on A &lt; B &lt; C: only 5, because the order fixes the labels.)

</Mcq>

</Drill>

<Drill n="4" tag="Concept">

If the inorder and preorder traversals of a binary tree are the same, which is true?

<Mcq :options="['The tree has only one node', 'The tree is skewed to the right', 'The tree is skewed to the left', 'All nodes have two children']" answer="b">

Root-Left-Right equals Left-Root-Right only if no node has a left child: a right-skewed tree (a single node is the smallest case).

</Mcq>

</Drill>

<Drill n="5" tag="Formula">

<FillIn q="How many nodes does a perfect binary tree of height 3 (in edges) have?" answer="15">

2ʰ⁺¹ − 1 = 2⁴ − 1 = 15: 8 leaves and 7 internal nodes.

</FillIn>

</Drill>

<Drill n="6" tag="Array">

<FillIn q="A binary tree is stored in an array with the root at index 0. Index of the right child of the node at index 5?" answer="12">

2i + 2 = 12. In the slides' example that cell holds J, the right child of F.

</FillIn>

</Drill>

<Drill n="7" tag="Lab blank">

<FillIn q="`int countLeaves(Node* root) { if (root == nullptr) return 0; if (root->left == nullptr && root->right == nullptr) return ____; return countLeaves(root->left) + countLeaves(root->right); }`" answer="1">

A leaf counts as one leaf.

</FillIn>

</Drill>

<Drill n="8" tag="Lab blank">

<FillIn q="Height in edges: `if (root == nullptr) return -1; int l = findHeight(root->left); int r = findHeight(root->right); return ____;`" answer="1 + max(l, r)|1+max(l,r)|max(l, r) + 1|max(l,r)+1|1 + max(l,r)">

One edge down to the taller subtree. With −1 for the empty tree, a leaf gets 1 + max(−1, −1) = 0.

</FillIn>

</Drill>
