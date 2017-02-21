import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class AnswerToGnu {
	public static void main(String[] args) throws IOException {

		String infile = args[0];
		String ansfile = args[1];

		File in = new File(infile);
		File ans = new File(ansfile);

		Scanner inscan = new Scanner(in);

		int r = inscan.nextInt();
		int s = inscan.nextInt();
		int u = inscan.nextInt();
		int p = inscan.nextInt();
		int m = inscan.nextInt();

		boolean[][] grid = new boolean[r][s];

		for (int i = 0; i < u; i++) {

			int ri = inscan.nextInt();
			int ci = inscan.nextInt();

			grid[ri][ci] = true;
		}

//		for (int i = 0; i < r; i++) {
//			for (int j = 0; j < s; j++) {
//				System.out.println(j + " " + i + " " + (grid[i][j] ? "1" : "2"));
//			}
//		}
		
		List<Integer> sizes = new ArrayList<>();
		List<Integer> caps = new ArrayList<>();
		for (int i = 0; i < m; i++) {
			int size = inscan.nextInt();
			int cap = inscan.nextInt();
			sizes.add(size);
			caps.add(cap);
		}
		
		BufferedReader ansscan = new BufferedReader(new FileReader(ans));
		
		for (int i = 0; i < m; i++) {
			String l = ansscan.readLine();
			if (!l.startsWith("x")) {
				Scanner lscan = new Scanner(l);
				int row = lscan.nextInt();
				int col = lscan.nextInt();
				int pool = lscan.nextInt();
				
				System.out.println("set object " + (i+1) + " rect from " + (col - 0.4) + ", " + (row - 0.4) + " to " + (col + (sizes.get(i) - 1) + 0.4) + ", " + (row + 0.4));
				System.out.println("set label " + (i+1) + " \"" + pool + "\" at " + (col + ((sizes.get(i) - 1) / 2.0)) + ", " + row + " front center");
			}
		}
		
	}
}
