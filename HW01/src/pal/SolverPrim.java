package pal;

import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Vector;

public class SolverPrim {

	public int prim(Vector<Vector<Node>> tableOfRoads, int capital) {
		int cost = 0;
		tableOfRoads = getLevels(tableOfRoads,capital);
		int numberOfCities = tableOfRoads.size();

		PriorityQueue<Node> primaryQueue = new PriorityQueue<>();
		PriorityQueue<Node> secondPriority = new PriorityQueue<>();

		boolean visited[] = new boolean[numberOfCities];

		visited[capital] = true;
		int visitedAll = 1;

		for (int i = 0; i < tableOfRoads.get(capital).size(); i++) {
			Node node = tableOfRoads.get(capital).get(i);
			primaryQueue.add(node);
		}
		while (!primaryQueue.isEmpty() || !secondPriority.isEmpty()) {
			if(visitedAll == numberOfCities){
				break;
			}
			if(primaryQueue.isEmpty()){
				primaryQueue = secondPriority;
				secondPriority = new PriorityQueue<>();
			}
			Node current = primaryQueue.poll();

			if (visited[current.index]) {
				continue;
			}
			visited[current.index] = true;
			visitedAll+=1;
			cost += current.weight;
			for (int i = 0; i < tableOfRoads.get(current.index).size(); i++) {
				Node node = tableOfRoads.get(current.index).get(i);
				if(visited[node.index]) continue;
				if(node.level == current.level ) {
					primaryQueue.add(node);
				} else {
					secondPriority.add(node);
				}
			}
		}

		return cost;
	}

	private Vector<Vector<Node>> getLevels(Vector<Vector<Node>> tableOfRoads, int capital){
		int numberOfCities = tableOfRoads.size();
		int[] levels = new int[numberOfCities];
		Queue<Node> queue = new LinkedList<>();
		boolean visited[] = new boolean[numberOfCities];
		visited[capital] = true;

		for (int i = 0; i < tableOfRoads.get(capital).size(); i++) {
			Node node = tableOfRoads.get(capital).get(i);
			node.level = 1;
			levels[node.index] = 1;
			queue.add(node);
		}
		while (!queue.isEmpty()) {
			Node current = queue.remove();
			if (visited[current.index]) {
				continue;
			}
			int level = current.level + 1;
			visited[current.index] = true;
			for (int i = 0; i < tableOfRoads.get(current.index).size(); i++) {
				Node node = tableOfRoads.get(current.index).get(i);
				if(levels[node.index] != 0){
					node.level = levels[node.index];
				} else if (node.index == capital) {
					node.level = 0;
				} else {
					node.level = level;
					levels[node.index] = level;
					queue.add(node);
				}

			}
		}

		return tableOfRoads;
	}
}

