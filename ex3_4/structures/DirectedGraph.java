package ex3_4.structures;

import java.util.*;

// https://stackoverflow.com/questions/4553624/hashmap-get-put-complexity
public class DirectedGraph<V,E> {
  private final Map<V,Map<V,E>> adjencyMap;

  public DirectedGraph() {
    this.adjencyMap = new HashMap<>();
  }
/*
 * for each funtion see the one @Graph class
 */
  public void addVertex(V vertex) {
    this.adjencyMap.put(vertex, new HashMap<>());
  }


  public void addEdge(V from,V to, E weight){
    adjencyMap.get(from).put(to,weight);
  }

  public boolean containsVertex(V vertex){
    return this.adjencyMap.containsKey(vertex); 
  }

  public boolean containsEdge(V from, V to){
    return this.adjencyMap.get(from).containsKey(to);
  } 

  public void removeVertex(V vertex){
    this.adjencyMap.values().forEach(map -> map.remove(vertex));
  }

  public void removeEdge(V from,V to){
    this.adjencyMap.get(from).remove(to);
  }

  public int getEdgeNum(){
    return adjencyMap.values().stream().reduce(0,(acc,curr)->acc+curr.size(),Integer::sum);
  }

  public ArrayList<V> getVerticesNum(){
    return new ArrayList<>(this.adjencyMap.keySet());
  }

  public ArrayList<Edge<V,E>> getEdges(){
    ArrayList<Edge<V,E>> edges = new ArrayList<>();

    adjencyMap.forEach((from,toMap)->toMap.forEach((to,weight)->edges.add(new Edge<>(from,weight,to))));

    return edges;
  }

}
