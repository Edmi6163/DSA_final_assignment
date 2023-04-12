package ex3_4;
import ex3_4.exceptions.ElementNotFoundException;
import ex3_4.exceptions.GraphException;
import ex3_4.structures.*;
import java.util.*;
import java.io.File;
public class Prim {
  public static void main(String[] args) {
    //main must do:
    //1. read the graph from the csv file args[1]
    //2. calculate the minimum spanning forest with prim's algorithm
    //3. print the result to the console
    if(args[1] == null) {
      System.out.println("No file path provided ");
      return;
    }
    readCsv(args[1]);
    mst();
    printResult();
  } 

  private static Graph<String,Float>  readCsv(String path) {
    //read the csv file and create the graph
    File file = new File(path);
    Scanner scanner = new Scanner(file);
    Graph<String,Float> builder = new Graph<>();
    while(scanner.hasNextLine()) {
      String line = scanner.nextLine();
      String[] values = line.split(",");
      //add the edge to the graph
      builder.addEdge(values[0], values[1], Float.parseFloat(values[2]));
    }
    scanner.close();
    graph = builder.build();

  }
}
