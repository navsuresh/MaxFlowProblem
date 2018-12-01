# MaxFlowProblem (UE16CS311 Project)
Our project involved implementing the following algorithms to solve the max flow problem:
	-Ford-Fulkerson Algorithm (Specifically, Edmond Karp's Implementation)
	-Dinic's Algorithm
	-Push-Relabel Algorithm
	-Relabel-to-Front Algorithm (Active node selection procedure in Push-Relabel Algorithm)

For demo purposes, there exists a Demo folder, with small graph input files. The input files follow the DIMACS format, as follows:

p max no_vertices no_edges
n 1 s
n no_vertices t
a vertice_i vertice_j cap_ij
.
.
.

*----------------*---------------------*-------------------*---------------------*--------------------------*

To change the input to the demo file, change file name in main to needed input file's names.

Compiling Instructions:

g++ algo_name.cpp -o algo_name

./algo_name.out

where algo_name is in {"E-K", "dinic", "pushrelabel", "relabeltofront"}

*----------------*---------------------*-------------------*---------------------*--------------------------*

The Final folder contains all the final codes:
	-GraphGen contains code to create the skeleton of random graphs for the purpose of solving the max flow problem based on certain specifications (no. of vertices and no. of edges). Open with jupyter notebook (iPythonNotebook file).
	-SourceCode contains both the source code as well as the randomly generated graphs that serves as input to the program.
	-Analysis contains code which generates result graphs which compare the density of the graphs with the time taken.

To change the input to the demo file, change file name in main to needed input file's names. Input file name is of the format "no_verticesxno_edges.txt(instance_no)".

Compiling Instructions:

g++ algo_name.cpp -o algo_name

./algo_name.out

where algo_name is in {"ek", "dinic", "pushrelabel", "relabeltofront"}

*----------------*---------------------*-------------------*---------------------*--------------------------*

The Report folder contains the final report, along with individual graphs of the density vs time taken for each algorithm (in the graphs folder).


