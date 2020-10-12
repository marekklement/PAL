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
}
