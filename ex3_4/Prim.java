import exceptions.ElementNotFoundException;
import exceptions.GraphException;
import structures.Graph;
import structures.PriorityQueue;

import java.io.*;
import java.util.*;
import java.util.Scanner;

public class Prim {
    public static Graph<String,Float> graph;
    //main must do:
    //1. read the graph from the csv file args[1]
    //2. calculate the minimum spanning forest with prim's algorithm
    //3. print the result to the console
  public static void main(String[] args) {
  }

  private static Graph<String,Double> readCsv(String path){
    Graph<String,Double> graph = new Graph<>(false,true);
    try(BufferedReader reader = new BufferedReader(new FileReader(path))) {
    String line;
    while((line = reader.readLine()) != null) {
      String[] values = line.split(",");
      String start = values[0];
      String end = values[1];
      double weight = Double.parseDouble(values[2]);

      graph.addVertex(start);
      graph.addVertex(end);
      graph.addEdge(start, end, weight);
    }
    } catch(IOException e) {
      e.printStackTrace();
    }
    return graph;
  }

  }
