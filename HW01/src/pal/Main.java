package pal;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Vector;

public class Main {
	public static void main(String[] args) throws IOException {
		Vector<Vector<Node>> read = read();
		System.out.println(prim(read,capitalCity));
	}

	static int capitalCity = -1;

	public static Vector<Vector<Node>> read() throws IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String[] split = reader.readLine().split(" ");
		int cities = Integer.parseInt(split[0]);
		int roads = Integer.parseInt(split[1]);
		capitalCity = Integer.parseInt(split[2]);
		Vector<Vector<Node>> map = new Vector<>();
		for(int i = 0; i < cities; i++){
			map.add(i, new Vector<>());
		}
		for(int i = 0; i < roads; i++){
			String[] splitIn = reader.readLine().split(" ");
			int from = Integer.parseInt(splitIn[0]);
			int to = Integer.parseInt(splitIn[1]);
			int cost = Integer.parseInt(splitIn[2]);
			Node first = new Node(cost,from);
			Node second = new Node(cost,to);
			map.elementAt(from).add(second);
			map.elementAt(to).add(first);
		}
		return map;
	}

	public static int prim(Vector<Vector<Node>> tableOfRoads, int capital) {
		int cost = 0;
		tableOfRoads = getLevels(tableOfRoads,capital);
		int numberOfCities = tableOfRoads.size();

		PriorityQueue<Node> primaryQueue = new PriorityQueue<>();
		PriorityQueue<Node> secondPriority = new PriorityQueue<>();

		boolean visited[] = new boolean[numberOfCities];

		visited[capital] = true;
		int visitedAll = 1;

		int num = tableOfRoads.get(capital).size();
		for (int i = 0; i < num; i++) {
			Node node = tableOfRoads.get(capital).get(i);
			primaryQueue.add(node);
		}
		while (!primaryQueue.isEmpty() || !secondPriority.isEmpty()) {
			if(visitedAll == numberOfCities){
				break;
			}
			if(primaryQueue.isEmpty()){
				PriorityQueue<Node> swap = primaryQueue;
				primaryQueue = secondPriority;
				secondPriority = swap;
			}
			Node current = primaryQueue.poll();

			if (visited[current.index]) {
				continue;
			}
			visited[current.index] = true;
			visitedAll+=1;
			cost += current.weight;
			if(visitedAll == numberOfCities) break;
			Vector<Node> vector = tableOfRoads.get(current.index);
			int number = vector.size();
			for (int i = 0; i < number; i++) {
				Node node = vector.get(i);
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

	private static Vector<Vector<Node>> getLevels(Vector<Vector<Node>> tableOfRoads, int capital){
		int numberOfCities = tableOfRoads.size();
		int[] levels = new int[numberOfCities];
		Queue<Node> queue = new LinkedList<>();
		boolean visited[] = new boolean[numberOfCities];
		visited[capital] = true;
		int visitedAll = 1;

		int num = tableOfRoads.get(capital).size();
		for (int i = 0; i < num; i++) {
			Node node = tableOfRoads.get(capital).get(i);
			node.level = 1;
			levels[node.index] = 1;
			queue.add(node);
		}
		while (!queue.isEmpty()) {
			if(visitedAll == numberOfCities) break;
			Node current = queue.remove();
			if (visited[current.index]) {
				continue;
			}
			int level = current.level + 1;
			visited[current.index] = true;
			visitedAll+=1;
			int number = tableOfRoads.get(current.index).size();
			for (int i = 0; i < number; i++) {
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
