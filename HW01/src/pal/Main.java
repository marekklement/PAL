package pal;

import java.io.IOException;
import java.util.Vector;

public class Main {
	public static void main(String[] args) throws IOException {
		FileReader reader = new FileReader();
		Vector<Vector<Node>> read = reader.read();
		SolverPrim solver = new SolverPrim();
		System.out.println(solver.prim(read,reader.capitalCity));
	}
}
