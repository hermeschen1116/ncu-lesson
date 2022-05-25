import java.text.StringCharacterIterator;
import java.util.Scanner;

public class Task1 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int numInput;
        String cardNumber;

        numInput = Integer.parseInt(input.nextLine());
        input.nextLine();
        for (int i = 0; i < numInput; i++) {
            cardNumber = input.nextLine();
            System.out.println(cardNumber);
        }
    }
}
