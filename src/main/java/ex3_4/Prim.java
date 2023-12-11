package ex3_4;

import exceptions.GraphException;
import structures.AbstractEdge;
import structures.Graph;
import structures.Key;
import structures.PriorityQueue;

import java.io.*;
import java.util.*;

public class Prim {
  public static Graph<String, Float> graph;


  /**
   * main function read the csv file and create the mst,
   * print the number of vertices, edges and total of km
   * calculated by the mst
   */
  public static void main(String[] args) throws GraphException {
    Graph<String,Double> graph = readCsv(args[0]);
    String firstVertex = graph.getVertices().iterator().next();

    long startTime = System.nanoTime();
    Graph<String,Double> mst = mst(graph, firstVertex);
    long endTime = System.nanoTime();

    System.out.println("Number of vertices: " + mst.getVertexNum());
    System.out.println("Number of edges: " + mst.getEdgeNum());

    System.out.printf("Total of km: %.3f km\n", calculateWeight(mst)/1000);
    System.out.println("Time taken: " + ((endTime - startTime)/1000) + " seconds");
  }

  /**
   * read the csv file and create the graph
   * @param path csv file path
   * @return graph
   */
  private static Graph<String, Double> readCsv(String path) {
    Graph<String, Double> graph = new Graph<>(true, true);
    try (BufferedReader reader = new BufferedReader(new FileReader(path))) {
      String line;
      while ((line = reader.readLine()) != null) {
        String[] values = line.split(",");
        String start = values[0];
        String end = values[1];
        double weight = Double.parseDouble(values[2]);

        graph.addVertex(start);
        graph.addVertex(end);
        graph.addEdge(start, end, weight);
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
    return graph;
  }

  /**
   * create the mst using the structure PriorityQueue
   * @param graph graph created from the csv file 
   * @param root first vertex of the graph
   * @return the minimum spanning tree of the graph
   * @throws GraphException
   */
  public static Graph<String, Double> mst(Graph<String, Double> graph, String root) throws GraphException {
    if (graph == null || graph.getVertexNum() == 0) {
      throw new GraphException("Graph is empty");
    }
    Graph<String, Double> mst = new Graph<>(true, true);
    Set<String> visited = new HashSet<>();
    Map<String, Key> keys = new HashMap<>();

    for (String vertex : graph.getVertices()) {
      keys.put(vertex, new Key(vertex, Double.POSITIVE_INFINITY));
    }
    Comparator<Key> keyComparator = Comparator.comparingDouble(Key::getKey);
    PriorityQueue<Key> queue = new PriorityQueue<>(keyComparator);
    keys.get(root).setKey(0);
    queue.addAll(keys.values());

    while (!queue.empty()) {
      Key currKey = queue.top();
      queue.pop();
      String currVertex = currKey.getVertex();
      visited.add(currVertex);
      mst.addVertex(currVertex);

      if (currKey.getParent() != null) {
        mst.addVertex(currKey.getParent());
        double edgeWeight = graph.getWeight(currKey.getParent(), currVertex);
        mst.addEdge(currVertex, currKey.getParent(), edgeWeight);
      }

      for (String neighbor : graph.getNeighbours(currVertex)) {
        if (!visited.contains(neighbor)) {
          double newKey = graph.getWeight(currVertex, neighbor);
          if (newKey < keys.get(neighbor).getKey()) {
            Key newNeighborKey = new Key(neighbor, newKey);
            newNeighborKey.setParent(currVertex);
            queue.push(newNeighborKey);
            keys.put(neighbor, newNeighborKey);

          }
        }
      }
    }

    return mst;
  }

  /**
   * calculate the total weight of the vertex of the graph
   * @param graph the graph created from the csv file
   * @return the total weight of the graph, aka the total of km
   */
  public static double calculateWeight(Graph<String, Double> graph) throws GraphException {
    double weight = 0;
    for (AbstractEdge<String,Double> edge : graph.getEdges()) {
        weight += edge.getWeight();
      }
    return weight / 2;
  }
}
