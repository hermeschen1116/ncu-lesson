import java.util.Scanner;

public class ALG_HW7_Task2 {
    public static int countScarecrow(int _size_, String _crops_) {
        int cnt = 0;
        StringBuilder strModifier = new StringBuilder(_crops_);

        for (int i = 0; i < _size_; i++) {
            if (_crops_.charAt(i) == '.') {
                cnt++;
                i += 2;
            }
        }

        return cnt;
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int nData, cropSize;
        String crops;

        nData = input.nextInt();
        for (int i = 0; i < nData; i++) {
            cropSize = input.nextInt();
            crops = input.next();
            System.out.printf("Case %d: %d\n", i + 1, countScarecrow(cropSize, crops));
        }
    }
}
