package structures;
import exceptions.*;
import structures.AbstractQueue;

import java.util.Collection;
import java.util.Comparator;
import java.util.ArrayList;
import java.util.HashMap;

public class PriorityQueue<E> implements AbstractQueue<E> {

	private final Comparator<? super E> comparator;
	private final ArrayList<E> queue;
	private final HashMap<E, Integer> indexMap;

	/*
	 */
	public PriorityQueue(Comparator<E> comparator) {
		this.comparator = comparator;
		this.queue = new ArrayList<>();
		this.indexMap = new HashMap<>();
	}

	private void heapifyUp(int index) {
		while (index > 0) {
			int parentIndex = (index - 1) / 2;
			if (comparator.compare(queue.get(parentIndex), queue.get(index)) <= 0) {
				break;
			}
			swap(queue, parentIndex, index);
			index = parentIndex;
		}
	}

	private void heapifyDown(int index) {
		int leftChildIndex = index * 2 + 1;
		int rightChildIndex = index * 2 + 2;

		while (leftChildIndex < queue.size()) {
			int smallestChildIndex = leftChildIndex;
			if (rightChildIndex < queue.size() && comparator.compare(queue.get(rightChildIndex), queue.get(leftChildIndex)) < 0)
				smallestChildIndex = rightChildIndex;
			if (comparator.compare(queue.get(smallestChildIndex), queue.get(index)) < 0)
				break;

			swap(queue, smallestChildIndex, index);
			index = smallestChildIndex;
			leftChildIndex = index * 2 + 1;
			rightChildIndex = index * 2 + 2;
		}

	}

	@Override
	public boolean empty() {
		return queue.isEmpty();
	}

	@Override
	public boolean push(E e) {
		if (indexMap.containsKey(e))
			return false;
		queue.add(e);
		int index = queue.size() - 1;
		indexMap.put(e, index);
		heapifyUp(index);
		return true;
	}

	@Override
	public E top() {
		if (queue.isEmpty())
			return null;
		return queue.get(0);
	}

	@Override
	public void pop() {
		if (queue.isEmpty())
			return;
		int lastIndex = queue.size() - 1;
		swap(queue, 0, lastIndex);
		indexMap.remove(queue.get(lastIndex));
		queue.remove(lastIndex);
		heapifyDown(0);
	}

	public boolean contains(E e) {
		return indexMap.containsKey(e);
	}

	private void swap(ArrayList<E> list, int i, int j) {
		E temp = list.get(i);
		list.set(i, list.get(j));
		list.set(j, temp);
		indexMap.put(list.get(i), i);
		indexMap.put(list.get(j), j);
	}

	public boolean remove(E e) {
		Integer index = indexMap.get(e);
		if (index == null)
			return false;
		int lastIndex = queue.size() - 1;
		if (index != lastIndex) {
			swap(queue, index, lastIndex);
			queue.remove(lastIndex);
			indexMap.remove(e);

			int parentIndex = (index - 1) / 2;
			if (comparator.compare(queue.get(parentIndex), queue.get(index)) > 0) {
				while (index > 0 && comparator.compare(queue.get(parentIndex), queue.get(index)) > 0) {
					swap(queue, parentIndex, index);
					index = parentIndex;
					parentIndex = (index - 1) / 2;
				}
			} else {
				heapifyDown(index);
			}
		} else {
			queue.remove(lastIndex);
			indexMap.remove(e);
		}
		return true;
	}

	public void increasePriority(E e1,E e2) {
	Integer index = indexMap.get(e1);

	if(index == null)
		return;

	if(comparator.compare(e1, e2) >= 0)
		return;

	queue.set(index, e2);
	indexMap.put(e2, index);
	indexMap.remove(e1);
	heapifyUp(index);
	}


public void addAll(Collection<E> edgesWithStartNode){
	for(E edge : edgesWithStartNode) {
		push(edge);
	}
}
}