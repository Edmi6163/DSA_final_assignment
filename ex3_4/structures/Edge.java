package ex3_4.structures;
// https://howtodoinjava.com/java14/java-14-record-type/

public record Edge<V,E>(V source,E weight,V target) {
  public Edge<V,E> getReverse(){
    return new Edge<>(this.target, this.weight, this.source);
  }
}
