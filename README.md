# מטלה 2 - גרפים 

id:324207935
email:shbabkoff123@gmail.com

-I assumed that in order to define an undirected graph, the user should enter 'false' in the load function.
The default is 'true' which means by default the graph is directed.

- I wrote all my algorithms in namespace called 'Algorithms'
- `isConnected(g)`- a boolean function that gets a Graph as a parameter and return if the graph is connected or not. 
The function call helpers functions: "isConnectedHelper" and "allvisited" that uses DFS algorithm idea.

- `isContainsCycle(g)` - boolean function checking if the graph contain any cycle.
Using helper function "isContainCycleHelper" that also gets a parameter if the graph is directed or not.
also hre in using the DFS algorithm idea

- `isBipartite(g)`- the function check if the graph is bipartite and if so it return the 2 sets of the vertices.
i use the coloring math method in order to check if the graph can be colored with only 2 colors.

- `shortestPath(g,start,end)` - function that find the shotrtest path between 2 vertices(which are parameters of the function).
in this function i use the bellman ford method.
(which hendel also negative edges)
if a negative cycle is ditected, the function mention it and return "-1".
- negativeCycle(g) -

-'negativeCycle(g)'- function that hceck if the graph contain negative cycle and if so return it.
also here im using the bellman ford method (go over the graph n-1 types and doing relaxition , and go 1 more time to see if any improvments have been found)


