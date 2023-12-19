package ex3_4.structures;

import java.util.AbstractCollection;


public interface AbstractGraph<V,L> {
    boolean isDirected(); // dice se il grafo è diretto o meno -- O(1)

    boolean isWeighted(); // dice se il grafo è etichettato o meno -- O(1)

    boolean addVertex(V a); // aggiunge un nodo -- O(1)

    boolean addEdge(V a, V b, L l); // aggiunge un arco dati estremi ed etichetta -- O(1)

    boolean containsVertex(V a); // controlla se un nodo è nel grafo -- O(1)

    boolean containsEdge(V a, V b); // controlla se un arco è nel grafo -- O(1) (*)

    boolean removeVertex(V a); // rimuove un nodo dal grafo -- O(N)

    boolean removeEdge(V a, V b); // rimuove un arco dal grafo -- O(1) (*)

    int getVertexNum(); // numero di nodi -- O(1)

    int getEdgeNum(); // numero di archi -- O(N)

    AbstractCollection<V> getVertices(); // recupero dei nodi del grafo -- O(N)

    AbstractCollection<AbstractEdge<V, L>> getEdges(); // recupero degli archi del grafo -- O(N)

    AbstractCollection<V> getNeighbours(V a); // recupero dei nodi adiacenti ad un dato nodo -- O(1) (*)

    L getWeight(V a, V b); // recupero dell'etichetta di un arco -- O(1) (*)


    interface AbstractEdge<V, E> {
        V getStart();

        V getEnd();

        E getWeight();
    }
}
