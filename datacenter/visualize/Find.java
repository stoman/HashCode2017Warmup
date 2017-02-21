
import java.awt.Color;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Find {
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

		// for (int i = 0; i < r; i++) {
		// for (int j = 0; j < s; j++) {
		// System.out.println(j + " " + i + " " + (grid[i][j] ? "1" : "2"));
		// }
		// }

		List<Integer> sizes = new ArrayList<>();
		List<Integer> caps = new ArrayList<>();
		for (int i = 0; i < m; i++) {
			int size = inscan.nextInt();
			int cap = inscan.nextInt();
			sizes.add(size);
			caps.add(cap);
		}

		BufferedReader ansscan = new BufferedReader(new FileReader(ans));

		Color[] colors = generateColors(100);

		for (int i = 0; i < m; i++) {
			String l = ansscan.readLine();
			if (l.startsWith("x")) {
				System.out.println("cap " + caps.get(i) + ", size " + sizes.get(i));
				
			}
		}
	}

	public static Color[] generateColors(int n) {
		Color[] cols = new Color[n];
		for (int i = 0; i < n; i++) {
			cols[i] = Color.getHSBColor((float) i / (float) n, 0.85f, 1.0f);
		}
		return cols;
	}

	public static String toCol(Color[] col, int n) {
		Color c = col[Math.min(n, 100)];
		String hex = "#" + Integer.toHexString(c.getRGB()).substring(2);
		return hex;
	}
}
