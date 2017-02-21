import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.Scanner;

public class AnswerToGnu {
	public static void main(String[] args) throws FileNotFoundException {
		// read
		// System.setIn(new FileInputStream(new File("small.ans")));
		// System.setOut(new PrintStream(new FileOutputStream(new File("small.ans.dat"))));

		Scanner sc = new Scanner(System.in);

		int s = sc.nextInt();

		for (int i = 1; i <= s; i++) {
			int y1 = sc.nextInt();
			int x1 = sc.nextInt();
			int y2 = sc.nextInt();
			int x2 = sc.nextInt();

			System.out.println(
					"set object " + i + " rect from " + (x1 - 0.4) + "," + (y1 - 0.4) + " to " + (x2 + 0.4) + "," + (y2 + 0.4));
		}
	}
}
