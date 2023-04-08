package ex3_4.structures;
import ex3_4.exceptions.*;
import java.util.Comparator;
import java.util.ArrayList;

public class PriorityQueue<E> implements AbstractQueue<E> {

	private final Comparator<? super E> comparator;
	private final ArrayList<E> queue;

	/*
	 */
	public PriorityQueue(Comparator<E> comparator) throws ArgumentException {
		if(comparator == null) {
			throw new ArgumentException("Comparator cannot be null");
		}
		this.comparator = comparator;
		this.queue = new ArrayList<>();
	}

	/*
	 * check if queue is empty
	 */
	@Override
	public boolean empty() {
		return this.queue.isEmpty();
	}

	/*
	 * add an element to the queue
	 */
	@Override
	public boolean push(E e) {
		return this.queue.add(e);
	}

	/*
	 * get the top element of the queue
	 */
	public E top() {
		return this.queue.get(0);
	}
/*
 * remvoe the top element of the queue
 */
	public void pop() {
		this.queue.remove(0);
	}

}