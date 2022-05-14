# Implementation of Kruskal's Algorithm

## About
This was created by Brad Campbell and Edward Dan in the spring of 2022.
The program implements Kruskal's algorithm for finding a minimum weight spanning tree (MST).

## Limits
This program is designed to run on randomized graphs. It works by utilizing our derived equations of probabilities of edge inclusion to cut out edges which most likely are not necessary to create an MST. 

Of course, there remains a small probability that the pruned edges are actually necessary to create an MST. However, our experimental data proved this to be much less than 1%. 

## Compiling
1. Compile using `make randmst`
2. ```./randmst.o <flag> <numpoints> <numtrials> <dimension>```