package pal;

public class HighWayMap {
	private int cities;
	private int roads;
	private int capitalCity;
	private int[][] table;

	public int getCities() {
		return cities;
	}

	public void setCities(int cities) {
		this.cities = cities;
	}

	public int getRoads() {
		return roads;
	}

	public void setRoads(int roads) {
		this.roads = roads;
	}

	public int getCapitalCity() {
		return capitalCity;
	}

	public void setCapitalCity(int capitalCity) {
		this.capitalCity = capitalCity;
	}

	public int[][] getTable() {
		return table;
	}

	public void setTable(int[][] table) {
		this.table = table;
	}
}
