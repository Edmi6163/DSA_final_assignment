package structures;

public interface AbstractEdge<V,E> {
    V getStart();
    V getEnd();
    E getWeight();
}
