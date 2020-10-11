package pal;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class FileReader {

	public HighWayMap read() throws IOException {
		HighWayMap map = new HighWayMap();
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		int[] line = Arrays.stream(reader.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
		map.setCities(line[0]);
		map.setRoads(line[1]);
		map.setCapitalCity(line[2]);
		int[][] table = new int[map.getCities()][map.getCities()];
		for(int i = 0; i < map.getRoads(); i++){
			int[] trip = Arrays.stream(reader.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
			table[trip[0]][trip[1]] = trip[2];
			table[trip[1]][trip[0]] = trip[2];
		}
		map.setTable(table);
		return map;
	}
}
