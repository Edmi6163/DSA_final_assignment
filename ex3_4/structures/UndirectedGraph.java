package ex3_4.structures;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class UndirectedGraph<V,E> extends DirectedGraph<V,E>{
  /*
   * @return the number of edges in the graph divided by 2 because the graph is undirected, so 
   * the number of edges is duplicated
   */
  @Override
  public int getEdgeNum(){
    return super.getEdgeNum()/2;
  }

  /*
   * add edge in both direction
   */
  @Override
  public void addEdge(V from,V to, E weight){
    super.addEdge(from,to,weight);
    super.addEdge(to,from,weight);
  }

  /*
   * remove edge in both direction
   */
  @Override
  public void removeEdge(V from,V to){
    super.removeEdge(from, to);
    super.removeEdge(to,from);
  }

  /*
   * get the edges,filter the duplicate and return the list
   */
  @Override
  public ArrayList<Edge<V,E>> getEdges(){
    Set<Edge<V,E>> set = new HashSet<>();
    super.getEdges().stream().filter(edge -> !set.contains(edge.getReverse())).forEach(set::add);
    return new ArrayList<>(set);
  }

    
}
