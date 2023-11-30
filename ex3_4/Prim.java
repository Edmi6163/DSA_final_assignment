import exceptions.GraphException;
import structures.Graph;
import structures.Key;
import structures.PriorityQueue;

import javax.sound.midi.Soundbank;
import java.io.*;
import java.util.*;
import java.util.Scanner;

public class Prim {
  public static Graph<String, Float> graph;

  //main must do:
  //1. read the graph from the csv file args[1]
  //2. calculate the minimum spanning forest with prim's algorithm
  //3. print the result to the console
  
  /**
   * main function read the csv file and create the mst,
   * print the number of vertices, edges and total of km
   * calculated by the mst
   * @param: args[0] must contain the csv file path
   */
  public static void main(String[] args) throws GraphException {
    Graph<String,Double> graph = readCsv(args[0]);
    String firstVertex = graph.getVertices().iterator().next();

    Graph<String,Double> mst = mst(graph, firstVertex);

    System.out.println("Number of vertices: " + mst.getVertexNum());
    System.out.println("Number of edges: " + mst.getEdgeNum());

    System.out.println("Total of km: " + calculateWeight(mst) + "km");
  }

  /**
   * read the csv file and create the graph
   * @param path csv file path
   * @return graph
   */
  private static Graph<String, Double> readCsv(String path) {
    Graph<String, Double> graph = new Graph<>(false, true);
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
   * @return the minumu spanning tree of the graph
   * @throws GraphException
   */
  private static Graph<String, Double> mst(Graph<String, Double> graph, String root) throws GraphException {
    if (graph == null || graph.getVertexNum() == 0) {
      throw new GraphException("Graph is empty");
    }
    Graph<String, Double> mst = new Graph<>(false, true);
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
   * @param graph
   * @return
   */
  public static double calculateWeight(Graph<String, Double> graph) {
    double weight = 0;
    for (String vertex : graph.getVertices()) {
      for (String neighbor : graph.getNeighbours(vertex)) {
        weight += graph.getWeight(vertex, neighbor);
      }
    }
    return weight / 2;
  }
}
