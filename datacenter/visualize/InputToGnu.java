import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class InputToGnu {
public static void main(String[] args) throws FileNotFoundException {
	
	Scanner sc = new Scanner(System.in);
	
	int r = sc.nextInt();
	int s = sc.nextInt();
	
	int u = sc.nextInt();
	
	int p = sc.nextInt();
	
	int m = sc.nextInt();
	
	boolean[][] grid = new boolean[r][s];
	
	for (int i = 0; i < u; i++) {
		
		int ri = sc.nextInt();
		int ci = sc.nextInt();
		
		grid[ri][ci] = true;
	}
	
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < s; j++) {
			System.out.println(j + " " + i + " " + (grid[i][j] ? "1" : "0"));
		}
	}
	
	int sizesum = 0;
	
	
	for (int i = 0; i < m; i++) {
		int size =sc.nextInt();
//		sizesum += size;
		
		int cap = sc.nextInt();
		
//		double eff = cap / ((double) size);
//		System.out.println(eff);
//		System.out.println(cap);
	}
}
}
