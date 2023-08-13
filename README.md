# CO222-PROJECT
**Crossword-Puzzle-Solver**

A project developed under the module "CO222-Programming Methodology". The aim of the project was to develop a program using C programming language to solve a crossword puzzle. The program should read a partially filled puzzle grid and a set of words from standard input and print the solved puzzle to standard output.

In phase 1 of the project, the group used static memory allocation for arrays. This involved declaring arrays with a fixed size at compile time. However, in phase 2, the group was required to use dynamic memory allocation. This involves allocating memory at runtime using functions such as malloc() and calloc().

The input puzzle grid included stars, hashes, and letters. Stars indicated blocked cells that cannot be filled, while hashes indicated vacant cells that needed to be filled with letters. The words to be used in the crossword puzzle were also included in the input, one per line, in random order.

If the program found out that filling the crossword puzzle was impossible with the given words, it was required to print IMPOSSIBLE.
