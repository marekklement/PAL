package pal;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

	public static void main(String[] args) throws IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		int numberOfLines = Integer.parseInt(reader.readLine());
		double[] previousLine = null, firstLine = null;
		double len = 0;
		for (int i = 0; i < numberOfLines; i++){
			String s = reader.readLine();
			String[] split = s.split(" ");
			if(i == 0){
				previousLine = new double[]{Double.parseDouble(split[0]), Double.parseDouble(split[1])};
				firstLine = previousLine;
			} else {
				double[] nextLine = new double[]{Double.parseDouble(split[0]), Double.parseDouble(split[1])};
				if(checkSame(previousLine, nextLine)) continue;
				len += addLen(previousLine, nextLine);
				previousLine = nextLine;
			}
		}
		if(numberOfLines!=0) {
			assert previousLine != null;
			len += addLen(previousLine, firstLine);
		}
		//
		int res = (int) Math.ceil(5*len);
		System.out.println(res);
	}

	private static boolean checkSame(double[] node1, double[] node2){
		return node1[0] == node2[0] && node1[1] == node2[1];
	}

	private static double addLen(double[] node1, double[] node2){
		double a = node1[0] - node2[0];
		double b = node1[1] - node2[1];
		double a2 = a*a;
		double b2 = b*b;
		return Math.pow(a2 + b2, 0.5);
	}
}
