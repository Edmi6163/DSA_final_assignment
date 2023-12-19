package ex3_4.structures;

import ex3_4.structures. AbstractGraph;

public class Edge<V,E> implements AbstractGraph.AbstractEdge<V,E> {
  private final V start;
  private final V end;
  private final E weight;

  public Edge(V start,V end,E weight){
    this.start = start;
    this.end = end;
    this.weight = weight;
  }

  public V getStart(){
    return start;
  }

  public V getEnd(){
    return end;
  }

    public E getWeight(){
        return weight;
    }
}
