package pal;

public class NumPair {

	public int first;
	public int second;

	public NumPair(int first, int second){
		this.first = first;
		this.second = second;
	}

	@Override
	public boolean equals(Object o) {
		if(o instanceof NumPair){
			return (((NumPair) o).first == this.first && ((NumPair) o).second == this.second) || (((NumPair) o).second == this.first && ((NumPair) o).first == this.second);
		}
		return false;
	}
}
