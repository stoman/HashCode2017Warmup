import java.util.Scanner;

public class slicer {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int t = sc.nextInt();

        int s = sc.nextInt();
        for (int i = 0; i < s; i++) {

            int lat = sc.nextInt();
            int lon = sc.nextInt();

            int v = sc.nextInt();
            System.out.println(v);
            int w = sc.nextInt();

            int d = sc.nextInt();
        }

        int c = sc.nextInt();
        for (int i = 0; i < c; i++) {
            // value
            int val = sc.nextInt();
//          System.out.println(val);
            
            // number of locs
            int l = sc.nextInt();
//          System.out.println(l);
            
            // ranges
            int r = sc.nextInt();
            
            for (int j = 0; j < l; j++) {
                int lat = sc.nextInt();
                int lon = sc.nextInt();
            }
            
            for (int j = 0; j < r; j++) {
                int start = sc.nextInt();
                int stop = sc.nextInt();
            }
        }
    }
}
