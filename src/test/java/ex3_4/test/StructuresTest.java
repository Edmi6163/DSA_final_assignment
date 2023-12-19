package ex3_4.test;

 import org.junit.Test;
 import static org.junit.Assert.*;

 import structures.Graph;
 import structures.PriorityQueue;
 import ex3_4.Prim;
 import exceptions.GraphException;

public class StructuresTest {
    @Test
    public void testEmptyGraph() {
        Graph<String, Double> graph = new Graph<>(false, true);
        try {
        Prim.mst(graph, "A");
        fail("GraphException expected");
        } catch (GraphException e) {
        assertEquals("Graph is empty", e.getMessage());
        }
    }

    @Test
    public void testOneVertex() {
        structures.Graph<String, Double> graph = new Graph<>(false, true);
        graph.addVertex("A");
        try {
        Prim.mst(graph, "A");
        fail("GraphException expected");
        } catch (GraphException e) {
        assertEquals("Graph has only one vertex", e.getMessage());
        }
    }

    @Test
    public void testTwoVertices() {
        Graph<String, Double> graph = new Graph<>(false, true);
        graph.addVertex("A");
        graph.addVertex("B");
        try {
        Prim.mst(graph, "A");
        fail("GraphException expected");
        } catch (GraphException e) {
        assertEquals("Graph has only two vertices", e.getMessage());
        }
    }

    @Test
    public void testThreeVertices() {
        Graph<String, Double> graph = new Graph<>(false, true);
        graph.addVertex("A");
        graph.addVertex("B");
        graph.addVertex("C");
        try {
        Prim.mst(graph, "A");
        fail("GraphException expected");
        } catch (GraphException e) {
        assertEquals("Graph has only three vertices", e.getMessage());
        }
    }

    @Test
    public void testFourVertices() {
        Graph<String, Double> graph = new Graph<>(false, true);
        graph.addVertex("A");
        graph.addVertex("B");
        graph.addVertex("C");
        graph.addVertex("D");
        try {
        Prim.mst(graph, "A");
        fail("GraphException expected");
        } catch (GraphException e) {
        assertEquals("Graph has only four vertices", e.getMessage());
        }
    }

    @Test
    public void testHeapifyUp() {
        PriorityQueue<Integer> priorityQueue = new PriorityQueue<>(Integer::compareTo);
        int smallestElement = priorityQueue.top();

        priorityQueue.push(5);
        priorityQueue.push(8);
        priorityQueue.push(3);
        priorityQueue.push(2);

        priorityQueue.heapifyUp(3);
        assertEquals(2, (int) priorityQueue.top());
    }

    @Test
    public void testHeapifyDown() {
        PriorityQueue<Integer> priorityQueue = new PriorityQueue<>(Integer::compareTo);




        priorityQueue.push(8);
        priorityQueue.push(5);
        priorityQueue.push(3);
        priorityQueue.push(2);

        priorityQueue.heapifyDown(0);

        assertEquals(2, (int) priorityQueue.top());

    }
  
}
