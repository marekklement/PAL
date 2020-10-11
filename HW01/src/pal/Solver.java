package pal;

import java.util.LinkedList;
import java.util.List;

import jdk.internal.util.xml.impl.Pair;

public class Solver {

	int [] costs;
	int [] from;
	List<Integer> added;
	HighWayMap map;
	List<NumPair> used;

	public int solve(HighWayMap map){
		this.map = map;
		costs = new int[map.getCities()];
		from = new int[map.getCities()];
		int [] capitalRow = map.getTable()[map.getCapitalCity()];
		added = new LinkedList<>();
		added.add(map.getCapitalCity());
		used = new LinkedList<>();
		List<Integer> potencial = new LinkedList<>();
		for(int i = 0; i< capitalRow.length; i++){
			if(capitalRow[i] != 0){
				costs[i] = capitalRow[i];
				from[i] = map.getCapitalCity();
				potencial.add(i);
			}
		}
		//
		return solveInner(potencial);
	}

	public int solveInner(List<Integer> potencial){
		if(potencial.size() == 0){
			return sumCosts();
		}
		for(Integer pot : potencial){
			for (Integer check : potencial) {
				if(!pot.equals(check)){
					int num = map.getTable()[pot][check];
					if(num != 0 && costs[check]>num && map.getTable()[from[check]][check] >= map.getTable()[from[pot]][pot] && !used.contains(new NumPair(pot,check))){
						if(map.getTable()[from[check]][check] == map.getTable()[from[pot]][pot]){
							used.add(new NumPair(pot,check));
						}
						costs[check] = num;
						from[check] = pot;
					}
				}
			}
		}
		added.addAll(potencial);
		if(added.size() == map.getCities()){
			return sumCosts();
		}
		List<Integer> newPotencial = getNewPotencial(potencial);
		return solveInner(newPotencial);
	}

	private List<Integer> getNewPotencial(List<Integer> potencial){
		List<Integer> newPotencial = new LinkedList<>();
		for (Integer pot: potencial) {
			int [] row = map.getTable()[pot];
			for(int i = 0; i< row.length; i++){
				if(row[i] != 0 && !added.contains(i)){
					if(costs[i] == 0 || costs[i] > row[i]) {
						costs[i] = row[i];
						from[i] = pot;
						newPotencial.add(i);
					}
				}
			}
		}
		return newPotencial;
	}

	private int sumCosts(){
		int sum = 0;
		for (int cost: costs) {
			sum += cost;
		}
		return sum;
	}
}
