import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Scanner;

public class ALG_HW8_Task2 {
    public static BigInteger power2Recursion(int _power_, ArrayList<BigInteger> _powerSet_) {
        BigInteger multiplier = new BigInteger("2");
        BigInteger tmp;

        if (_power_ < _powerSet_.size()) tmp = _powerSet_.get(_power_);
        else {
            if (_power_ == 0) tmp = new BigInteger("1");
            else tmp = power2Recursion(_power_ - 1, _powerSet_).multiply(multiplier);
            _powerSet_.add(tmp);
        }
        return tmp;
    }

    public static BigInteger sum2Exponent(int _power1_, int _power2_) {
        ArrayList<BigInteger> powerSet = new ArrayList<>();
        int powerD = Math.abs(_power1_ - _power2_);
        BigInteger sum;
        BigInteger tmp;

        sum = power2Recursion(Math.min(_power1_, _power2_), powerSet);
        if (powerD > powerSet.size()) tmp = power2Recursion(powerD, powerSet);
        else tmp = powerSet.get(powerD);
        tmp = tmp.multiply(sum);
        sum = sum.add(tmp);

        return sum;
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int nData, m, n;

        nData = input.nextInt();
        for (int i = 0; i < nData; i++) {
            m = input.nextInt();
            n = input.nextInt();
            System.out.println(sum2Exponent(m, n));
        }
    }
}
