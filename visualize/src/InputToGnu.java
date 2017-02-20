import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.Scanner;

public class InputToGnu {

	public static void main(String[] args) throws FileNotFoundException {

		// read
		// System.setIn(new FileInputStream(new File("small.in")));
		// System.setOut(new PrintStream(new FileOutputStream(new File("small.dat"))));

		Scanner sc = new Scanner(System.in);
		int r = sc.nextInt();
		int c = sc.nextInt();
		int l = sc.nextInt();
		int h = sc.nextInt();
		sc.nextLine();

		char[][] grid = new char[r][c];

		for (int i = 0; i < r; i++) {
			String line = sc.nextLine();
			for (int j = 0; j < c; j++) {
				grid[i][j] = line.charAt(j);
			}
		}
		
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				System.out.println(j + " " + i + " " + (grid[i][j] == 'T' ? 1 : 2));
			}
		}
	}

}
