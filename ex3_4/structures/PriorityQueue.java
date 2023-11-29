package ex3_4.structures;
import exceptions.*;
import structures.AbstractQueue;

import java.util.Comparator;
import java.util.ArrayList;
import java.util.HashMap;

public class PriorityQueue<E> implements AbstractQueue<E> {

	private final Comparator<? super E> comparator;
	private final ArrayList<E> queue;
	private final HashMap<E,Integer> indexMap;

	/*
	 */
	public PriorityQueue(Comparator<E> comparator) {
		this.comparator = comparator;
		this.queue = new ArrayList<>();
		this.indexMap = new HashMap<>();
	}

	private void heapifyUp(int index){
		while(index > 0){
			int parentIndex = (index-1)/2;
			if(comparator.compare(queue.get(parentIndex),queue.get(index)) <= 0){
				break;
			}
			swap(heap,parentIndex,index);
			index = parentIndex;
		}
	}


}