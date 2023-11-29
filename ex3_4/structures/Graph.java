package structures;

import java.util.HashMap;

import ex3_4.exceptions.ElementNotFoundException;
import ex3_4.exceptions.GraphException;
import ex3_4.structures.DirectedGraph;
import ex3_4.structures.UndirectedGraph;


/*
 * Class representing a graph with generic vertices and edges
 * @param <V> the type of the vertices
 * @param <E> the type of the edges
 */
public class Graph<V, E> {
  public final HashMap<V, HashMap<V, E>> map = new HashMap<>();
  private boolean directed;
  private final ex3_4.structures.DirectedGraph<V,E> internalGraph;

  public Graph(boolean directed) {
    internalGraph = directed ? new DirectedGraph<>() : new UndirectedGraph<>();
  }

  public Graph<V, E> addVertex(V vertex) {
    map.put(vertex, new HashMap<>());
    return this;
  }

  public Graph<V, E> addEdge(V from, V to, E weight) {
    if (!map.containsKey(from))
      this.addVertex(from);

    if (!map.containsKey(to))
      this.addVertex(to);

    map.get(from).put(to, weight);
    return this;
  }
  
  public Graph<V,E> buildDirectedGraph(boolean isDirected){
    directed = isDirected;
    return this;
  }
  
  /*
   * Make an instances of Graph with edges and vertices previously added
   * @return graph
   */
  public Graph<V,E> build() throws GraphException, ElementNotFoundException{
    Graph<V,E> graph = new Graph<>(directed);

    for(V vertex : map.keySet()) {
      graph.addVertex(vertex);
    }

    for(var entry : this.map.entrySet()) {
      for(var edge : entry.getValue().entrySet()) {
        graph.addEdge(entry.getKey(), edge.getKey(), edge.getValue());
      }
    }
    return graph;
  }
}

