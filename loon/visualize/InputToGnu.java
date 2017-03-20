import java.io.FileNotFoundException;
import java.util.Scanner;

public class InputToGnu {
    public static void main(String[] args) throws FileNotFoundException {
        
        Scanner sc = new Scanner(System.in);
        
        int r = sc.nextInt();
        int c = sc.nextInt();
        int a = sc.nextInt();
        
        int l = sc.nextInt();
        int v = sc.nextInt();
        int b = sc.nextInt();
        int t = sc.nextInt();
        
        int rs = sc.nextInt();
        int cs = sc.nextInt();
        
        for (int i = 0; i < l; i++) {
            // target i
            int ri = sc.nextInt();
            int ci = sc.nextInt();
            
            if (ri == rs && ci == cs) {
                System.out.println(ci + " " + ri + " " + 1);
            } else {
                System.out.println(ci + " " + ri + " " + 0);
            }
        }
        System.out.println(cs + " " + rs + " " + 1);
        
        for (int i = 0; i < a; i++) {
            for (int ri = 0; ri < r; ri++) {
                for (int ci = 0; ci < c; ci++) {
                    int drc = sc.nextInt();
                    int crc = sc.nextInt();
                    
//                  double len = Math.sqrt(drc * drc + crc * crc);
//                  System.out.println(len);
                }
            }
        }
        
        // Sysout x, y, color
    }
}
