package pal;

import java.io.IOException;

public class Main {
	public static void main(String[] args) throws IOException {
		FileReader reader = new FileReader();
		HighWayMap read = reader.read();
		SolverPrim solver = new SolverPrim();
		System.out.println(solver.solve(read));
	}
}
