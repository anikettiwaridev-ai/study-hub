---
title: Theory Quiz IV, 2025
---

# Theory Quiz IV, 2025

<PaperHeader :rows="[
  ['Course', 'Data Structures, CTN301 / AIN301 / DSN301, batch 25261 (last year)'],
  ['Format', '10 questions, 1 mark each, 10 minutes'],
  ['Covers', 'Graphs, MSTs, Dijkstra, heaps, union-find (Units 7 and 8)'],
]" />

<QuizTimer :minutes="10" label="Theory Quiz IV" />

::: warning After the mid-semester
None of this is in the Units 1–5 mid-semester. Solved here for the end-semester and the fourth quiz.
:::

<Q id="QA4.Q1">

What is the time complexity for finding the total number of connected components in an undirected weighted graph?

<FillIn q="Answer (Big-O):" answer="O(V + E)|O(V+E)|O(n + m)|O(n+m)">

Run BFS or DFS from every unvisited vertex and count the starts: each vertex and edge is handled once, O(V + E) with adjacency lists. The weights don't matter. The sheet's O(V) forgot the edges.

</FillIn>

</Q>

<Q id="QA4.Q2">

An undirected not-connected graph have V vertices, E edges and K connected components. What is the minimum number of edges need to be added in the graph to make it a connected graph?

<FillIn q="Answer:" answer="K - 1|K-1|k-1|k - 1">

Each added edge can join two components; K components need K − 1 joins.

</FillIn>

</Q>

<Q id="QA4.Q3">

How many Minimum Spanning Tree (MST) are possible in an unweighted complete graph with n vertices?

<Mcq :options="['n', 'ⁿC₂', 'nⁿ⁻¹', 'nⁿ⁻²']" answer="d">

Unweighted: every spanning tree has the same weight, so all of them are minimum. A complete graph Kₙ has nⁿ⁻² spanning trees (Cayley's formula).

</Mcq>

</Q>

<Q id="QA4.Q4">

Which of the following statements is/are TRUE? S1: Dijkstra's Single Source Shortest Path (SSSP) algorithm works for graph with negative weight edges. S2: Dijkstra's SSSP algo doesn't work for graph with negative weight cycles.

<Mcq :options="['Only S1', 'Only S2', 'Both S1 and S2', 'Neither S1 nor S2']" answer="b">

Dijkstra finalises a vertex when it is picked and never revisits it; a negative edge found later could have given a shorter path, so S1 is false. With a negative cycle no shortest path even exists, so S2 is true.

</Mcq>

</Q>

<Q id="QA4.Q5">

A connected weighted graph has m edges. The relation between weights for edges e₁, e₂, e₃, …, eₘ is w₁ = w₂ &lt; w₃ &lt; … &lt; wₘ. What is the maximum number of different MSTs possible for the given graph?

<FillIn q="Answer:" answer="2|1">

**Write 2**: that is the answer marked correct on the scanned sheet. The intended reasoning is that only one pair of weights ties, so at most two choices exist.

Strictly, in a simple graph the answer is 1: the two lightest edges can never form a cycle together, so Kruskal takes both, and every other weight is distinct, so the MST is unique. A brute-force check over random simple graphs with these weights never found more than one MST. Two MSTs need e₁ and e₂ to be **parallel** edges between the same pair of vertices. If you have time, write "2 (if e₁ and e₂ join the same two vertices; otherwise 1)".

</FillIn>

</Q>

<Q id="QA4.Q6">

Which of the following statements is/are TRUE? S1: Kruskal's algorithm for finding MST will work for graph with negative weight edges. S2: Prim's algorithm for finding MST will work for graph with negative weight edges.

<Mcq :options="['Only S1', 'Only S2', 'Both S1 and S2', 'Neither S1 nor S2']" answer="c">

Both only compare edge weights to pick the cheapest safe edge; negative values don't break that. (Negative weights break Dijkstra, not MST algorithms.) The sheet's "only S1" lost the mark.

</Mcq>

</Q>

<Q id="QA4.Q7">

What are the time complexity of finding the minimum and maximum elements in a min-heap with n nodes?

<Mcq :options="['O(1), O(1)', 'O(n), O(1)', 'O(1), O(n)', 'O(n), O(n)']" answer="c">

The minimum is the root. The maximum is one of the leaves (about n/2 of them), so it needs a scan: O(n).

</Mcq>

</Q>

<Q id="QA4.Q8">

What will be the time complexity of the union operation if the representative of each element is updated to store the representative of that element?

<FillIn q="Answer (Big-O):" answer="O(n)">

This is "quick-find": every element stores its representative directly, so a union must relabel every element of one set, up to n. O(n) per union (and O(1) find).

</FillIn>

</Q>

<Q id="QA4.Q9">

What will be the time complexity of converting a min-heap to a max-heap? Assume the min-heap is already stored in an array.

<FillIn q="Answer (Big-O):" answer="O(n)">

Ignore the old order and run bottom-up build-heap (heapify from the last internal node up to the root): O(n).

</FillIn>

</Q>

<Q id="QA4.Q10">

In a priority queue, total n² insertions and n deletions are to be performed. Every n insertions are followed by one deletion. What is the total time complexity of performing these operations if heap is used to implement priority queue?

<FillIn q="Answer (Big-O):" answer="O(n^2 log n)|O(n² log n)|O(n2 log n)|O(n^2logn)">

The heap holds up to about n² elements, so each operation costs O(log n²) = O(2 log n) = O(log n). Insertions: n² × O(log n); deletions: n × O(log n). Total **O(n² log n)**.

</FillIn>

</Q>
