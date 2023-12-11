package structures;

public class Key {
  private final String edge;
  private double key;
  private String parent;

  public Key(String edge,double key){
    this.edge = edge;
    this.key = key;
    this.parent = null;
  }

  public String getVertex() {
    return edge;
  }

  public double getKey() {
    return key;
  }

  public void setKey(double key) {
    this.key = key;
  }

  public String getParent() {
    return parent;
  }

  public void setParent(String parent) {
    this.parent = parent;
  }

  
}
