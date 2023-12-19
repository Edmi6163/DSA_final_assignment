package ex3_4.test;

 import ex3_4.structures.AbstractGraph;
 import ex3_4.structures.Graph;
 import ex3_4.structures.PriorityQueue;
 import ex3_4.Prim;
 import org.junit.Test;
 import static org.junit.Assert.*;


 import exceptions.GraphException;

 import java.util.Collection;
 import java.util.Iterator;

public class StructuresTest {

    public void setUp() {
        PriorityQueue<Integer> priorityQueue = new PriorityQueue<>(Integer::compareTo);
    }

    @Test
    public void testIsDirected(){
        Graph<String, Double> directedGraph = new Graph<>(true, true);
        Graph<String, Double> unDirectedGraph = new Graph<>(false, true);
        assertTrue(directedGraph.isDirected());
        assertFalse(unDirectedGraph.isDirected());
    }

    @Test
    public void testAddVertex(){
        Graph<String, Double> graph = new Graph<>(true, true);
        assertTrue(graph.addVertex("A"));
        assertFalse(graph.addVertex("A"));
        assertTrue(graph.containsVertex("A"));
    }

    @Test
    public void testAddEdge(){
        Graph<String, Double> graph = new Graph<>(true, true);
        graph.addVertex("A");
        graph.addVertex("B");
        assertTrue(graph.addEdge("A", "B", 1.0));
        assertTrue(graph.containsEdge("A", "B"));
    }
    @Test
    public void testRemoveVertex() {
        Graph<String, Float> graph = new Graph<>(false, false);
        graph.addVertex("A");
        graph.addVertex("B");
        graph.addVertex("C");

        assertTrue(graph.removeVertex("B"));
        assertFalse(graph.removeVertex("B"));

        assertFalse(graph.containsVertex("B"));
    }

    @Test
    public void testRemoveEdge() {
        Graph<String, Float> graph = new Graph<>(false, true);
        graph.addVertex("A");
        graph.addVertex("B");
        graph.addEdge("A", "B", 1.0f);

        assertTrue(graph.removeEdge("A", "B"));
        assertFalse(graph.removeEdge("A", "B"));

        assertFalse(graph.containsEdge("A", "B"));
    }

    @Test
    public void testGetVertex() {
        Graph<String, Float> graph = new Graph<>(false, false);
        graph.addVertex("A");
        graph.addVertex("B");
        graph.addVertex("C");

        Collection<String> nodes = graph.getVertices();
        assertEquals(3, nodes.size());
        assertTrue(nodes.contains("A"));
        assertTrue(nodes.contains("B"));
        assertTrue(nodes.contains("C"));
    }

    @Test
    public void testGetEdges() {
        Graph<String, Float> graph = new Graph<>(true, true);
        graph.addVertex("A");
        graph.addVertex("B");
        graph.addVertex("C");
        graph.addEdge("A", "B", 1.0f);
        graph.addEdge("B", "C", 2.0f);

        Collection<AbstractGraph.AbstractEdge<String, Float>> edges = graph.getEdges();
        assertEquals(2, edges.size());

        int count = 0;
        for (AbstractGraph.AbstractEdge<String, Float> edge : edges) {
            if (edge.getStart().equals("A") && edge.getEnd().equals("B") && edge.getWeight().equals(1.0f)) {
                count++;
            } else if (edge.getStart().equals("B") && edge.getEnd().equals("C") && edge.getWeight().equals(2.0f)) {
                count++;
            }
        }

        assertEquals(2, count);
    }

    @Test
    public void testPrimSingleNode() throws GraphException {
        Graph<String, Double> singleNodeGraph = new Graph<>(false, true);
        singleNodeGraph.addVertex("A");

        Graph<String, Double> mst = Prim.mst(singleNodeGraph, "A");
        assertEquals(1, mst.getVertexNum());
        assertEquals(0, mst.getEdgeNum());
    }


}
