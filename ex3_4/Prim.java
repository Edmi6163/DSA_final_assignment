
import exceptions.ElementNotFoundException;
import exceptions.GraphException;
import structures.Graph;
import structures.PriorityQueue;

import java.util.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Prim {
    public static Graph<String,Float> graph;
    //main must do:
    //1. read the graph from the csv file args[1]
    //2. calculate the minimum spanning forest with prim's algorithm
    //3. print the result to the console
  public static void main(String[] args) {

    String filePath = "";
    if(args.length > 0)
      filePath = args[0];
    else 
      System.out.println("no file provided");
    
    Graph<String, Float> graphFromFile = readCsv(filePath);
    mst(graphFromFile);
    // printResult();
  } 

  /*   
   * @brief: read the csv file and create the graph adding the edges
   */
  private static Graph<String,Float> readCsv(final String path) {
    System.out.println("reading csv file");
    try {
      File file = new File(path);
      Scanner scanner = new Scanner(file);
      Graph<String,Float> builder = new Graph<>(true);
      while(scanner.hasNextLine()) {
        String line = scanner.nextLine();
        String[] values = line.split(",");
        builder.addEdge(values[0], values[1], Float.parseFloat(values[2]));
      }
      scanner.close();
      try {
      graph = builder.build();
      } catch( GraphException | ElementNotFoundException e) {
        e.printStackTrace();
      }
    } catch (FileNotFoundException e) {
      e.printStackTrace();
    }
    System.out.println("graph from csv created correctly");
    return graph;
  }

  /*
   * @brief: generic implementation of a Prim's minimum spanning tree algorithm
   */
  public static Graph<String,Float> mst(Graph <String,Float> graph){
		System.out.println("calculating mst: ");
    Graph<String,Float> mst = new Graph<>(true);
    Set<String> visited = new HashSet<>();
    PriorityQueue<String,Float> edgeQueue = new PriorityQueue<>(Comparator.comparing(v1 -> graph.map.get(v1),Float::compare));
    if(graph.map.isEmpty()) {
      return mst;
    }
    String startVertex = graph.map.keySet().iterator().next();
    visited.add(startVertex);

    for(String to : graph.map.get(startVertex).keySet()){
      edgeQueue.add(to);
    }

    while(visited.size() < graph.map.size() && !edgeQueue.isEmpty()){
      String vertex = edgeQueue.extracMin();

      if(!visited.contains(vertex)) {
        mst.addVertex(startVertex);
        mst.addVertex(vertex);
        Float weight = graph.map.get(startVertex).get(vertex);
        mst.addEdge(startVertex,vertex,weight);
        visited.add(vertex);
        
        for(String to : graph.map.get(vertex).keySet()){
          if(!visited.contains(to)){
            edgeQueue.add(to);
          }
        }

      }  
      
    }
    return mst;
  }


}
