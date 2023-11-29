package structures;

public interface AbstractQueue<E> {
  public boolean empty();

  public boolean push(E e);

  public E top();

  public void pop(); 
}
