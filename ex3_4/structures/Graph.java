package ex3_4.structures;

import java.util.HashMap;

/*
 * Class representing a graph with generic vertices and edges
 * @param <V> the type of the vertices
 * @param <E> the type of the edges
 */
public class Graph<V, E> {
  private final HashMap<V, HashMap<V, E>> map;
  private boolean directed;
  public Graph() {
    map = new HashMap<>();
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

}
