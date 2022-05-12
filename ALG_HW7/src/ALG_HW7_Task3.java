import java.util.ArrayList;
import java.util.Scanner;

public class ALG_HW7_Task3 {
    public static int maxPaper(int _nPaper_, ArrayList<int[]> _papers_) {
        int max = 0, maxIndex = 0;

        for (int i = 0; i < _nPaper_; i++) {
            if (_papers_.get(i)[0]*_papers_.get(i)[1] > max) {
                max = _papers_.get(i)[0]*_papers_.get(i)[1];
                maxIndex = i;
            }
        }

        return maxIndex+1;
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int nPaper, x, y;
        ArrayList<int[]> papers = new ArrayList<>();

        while (true) {
            nPaper = input.nextInt();
            if (nPaper == 0) break;
            papers.clear();
            for (int i = 0; i < nPaper; i++) {
                x = input.nextInt();
                y = input.nextInt();
                papers.add(new int[]{x, y});
            }
            System.out.println(maxPaper(nPaper, papers));
        }
    }
}
