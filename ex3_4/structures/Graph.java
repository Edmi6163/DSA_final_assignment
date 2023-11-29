package structures;

import java.util.AbstractCollection;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import exceptions.GraphException;
import ex3_4.structures.Edge;


/*
 * Class representing a graph with generic vertices and edges
 * @param <V> the type of the vertices
 * @param <E> the type of the edges
 */
public class Graph<V, E> {
  private final boolean directed;
  private final boolean weighted;
  private final Map<V, Map<V,E>> adjencyMap;
  private int edgeNum;

  public Graph(boolean directed, boolean weighted) {
    this.directed = directed;
    this.weighted = weighted;
    this.adjencyMap = new HashMap<>();
    this.edgeNum = 0;
  }

  public boolean isDirected(){
    return directed;
  }

  public boolean isWeighted(){
    return weighted;
  }

  public boolean addVertex(V vertex){
    if(adjencyMap.containsKey(vertex))
      return false;

    adjencyMap.put(vertex, new HashMap<>());
    return true;
  }

  public boolean addEdge(V a,V b,E weight){
    if(!containsVertex(a) || !containsVertex(b)) {
      System.out.println("vertex not found");
      return false;
    }
    if(weight == null && isWeighted()) {
      System.out.println("weight not found");
      return false;
    }

    adjencyMap.get(a).put(a,weight);
    if(!isDirected()) {
      adjencyMap.get(b).put(a,weight);
      edgeNum += 2;
    } else {
      edgeNum++;
    }
    return true;
  }

  public boolean containsVertex(V vertex){
    return adjencyMap.containsKey(vertex);
  }

    public boolean containsEdge(V a,V b) {
      return adjencyMap.get(a) != null && adjencyMap.get(a).containsKey(b);
    }

    public boolean removeVertex(V vertex) {
        if(!containsVertex(vertex))
          return false;

        int edgesRemoved = adjencyMap.get(a).size();
        adjencyMap.remove(vertex);
        for(Map.Entry<V,Map<V,E>> entry : adjencyMap.entrySet()){
          entry.getValue().remove(vertex);
        }
        edgeNum -= edgesRemoved;

        if(!isDirected()){
          edgeNum -= edgesRemoved;
        }
        return true;
    }

    public boolean removeEdge(V a,V b) {
      if(!containsEdge(a,b))
        return false;

      adjencyMap.get(a).remove(b);
      if(!isDirected()) {
        adjencyMap.get(b).remove(a);
        edgeNum -= 2;
      } else {
        edgeNum--;
      }
      return true;
    }

    public int getEdgeNum() {
    return adjencyMap.size();
    }

    public int getVertexNum() {
      return adjencyMap.size();
    }

    public AbstractCollection<V> getVertices(){
      return new ArrayList<>(adjencyMap.keySet());
    }

   public AbstractCollection<AbstractEdge<V,E>> getEdges(){
    AbstractCollection<AbstractEdge<V,E>> edges = new ArrayList<>();
    for(V source: adjencyMap.keySet()){
      for(Map.Entry<V,E> entry: adjencyMap.get(source).entrySet()){
        V target = entry.getKey();
        E weight = entry.getValue();
        edges.add(new Edge<>(source,target,weight));
      }
    }
    return edges;
   }

   public AbstractCollection<V> getNeighbours(V vertex){
    if(!containsVertex(vertex))
      return null;

    return new ArrayList<>(adjencyMap.get(vertex).keySet());

   }

   public E getWeight(V a,V b) throws GraphException {
    if(!containsEdge(a,b))
      return null;
    return adjencyMap.get(a).get(b);
   }
}

