import java.util.Scanner;

public class Task3 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int numInput;
        int numElement;

        numInput = input.nextInt();
        for (int i = 0; i < numInput; i++) {
            numElement = input.nextInt();
            if (numElement % 2 == 1 && numElement > 1 && numElement < 1000000000) {
                System.out.println(multiplyLast3Element(numElement));
            }
        }

        input.close();
    }

    public static int multiplyLast3Element (int numElement) {
        int lastElement = 1 + 2 * ((numElement + 3) * ((numElement-1) / 2) / 2);
        return lastElement * (lastElement-2) * (lastElement-4);
    }
}
