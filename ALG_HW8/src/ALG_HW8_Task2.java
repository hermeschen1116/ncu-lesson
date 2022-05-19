import java.util.ArrayList;
import java.util.Scanner;

public class ALG_HW8_Task2 {
    public static ArrayList<Integer> multiplyBigNumber(ArrayList<Integer> _multiplicand_, int _smallMultiplier_) {
        ArrayList<Integer> result = new ArrayList<>(_multiplicand_);
        int length = result.size(), buffer, carry = 0;

        for (int i = 0; i < length; i++) {
            buffer = result.get(i) * _smallMultiplier_ + carry;
            result.set(i, buffer % 10);
            carry = buffer / 10;
            if (i == length - 1 && carry != 0) result.add(carry);
        }

        return result;
    }

    public static ArrayList<Integer> sumBigNumber(ArrayList<Integer> _n1_, ArrayList<Integer> _n2_) {
        ArrayList<Integer> result;
        int buffer, carry = 0, length;

        if (_n1_.size() > _n2_.size()) {
            result = new ArrayList<>(_n1_);
            for (int i = 0; i < _n2_.size(); i++) result.set(i, result.get(i) + _n2_.get(i));
        } else {
            result = new ArrayList<>(_n2_);
            for (int i = 0; i < _n1_.size(); i++) result.set(i, result.get(i) + _n1_.get(i));
        }

        length = result.size();
        for (int i = 0; i < length; i++) {
            buffer = result.get(i) + carry;
            result.set(i, buffer % 10);
            carry = buffer / 10;
            if (i == length - 1 && carry != 0) result.add(carry);
        }

        return result;
    }

    public static ArrayList<Integer> power2Recursion(int _power_, ArrayList<ArrayList<Integer>> _powerSet_) {
        ArrayList<Integer> tmp = new ArrayList<>();

        if (_power_ < _powerSet_.size()) tmp = _powerSet_.get(_power_);
        else {
            if (_power_ == 0) tmp.add(1);
            else tmp = multiplyBigNumber(power2Recursion(_power_ - 1, _powerSet_), 2);
            _powerSet_.add(tmp);
        }
        return tmp;
    }

    public static String sum2Exponent(int _power1_, int _power2_) {
        ArrayList<ArrayList<Integer>> powerSet = new ArrayList<>();
        ArrayList<Integer> sum;
        StringBuilder result = new StringBuilder();

        sum = sumBigNumber(power2Recursion(_power1_, powerSet), power2Recursion(_power2_, powerSet));
        for (int i = sum.size() - 1; i >= 0; i--) result.append(sum.get(i));

        return result.toString();
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
