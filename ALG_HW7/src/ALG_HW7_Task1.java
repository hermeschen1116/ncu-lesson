import java.util.Scanner;
import java.lang.Math;

public class ALG_HW7_Task1 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int nData;
        double exp, powered;

        nData = input.nextInt();
        for (int i = 0; i < nData; i++) {
            exp = input.nextDouble();
            powered = input.nextDouble();
            System.out.printf("%.0f\n", Math.pow(powered, 1/exp));
        }
    }
}
