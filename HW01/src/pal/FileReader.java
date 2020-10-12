package pal;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Vector;

public class FileReader {

	int capitalCity = -1;

	public Vector<Vector<Node>> read() throws IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		int[] line = Arrays.stream(reader.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
		Vector<Vector<Node>> map = new Vector<>();
		int cities = line[0];
		int roads = line[1];
		capitalCity = line[2];
		for(int i = 0; i < cities; i++){
			map.add(i, new Vector<>());
		}
		for(int i = 0; i < roads; i++){
			int[] road = Arrays.stream(reader.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
			Node first = new Node(road[2],road[0]);
			Node second = new Node(road[2],road[1]);
			map.elementAt(road[0]).add(second);
			map.elementAt(road[1]).add(first);
		}
		return map;
	}
}
