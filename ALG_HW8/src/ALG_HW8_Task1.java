import java.text.CharacterIterator;
import java.text.StringCharacterIterator;
import java.util.HashMap;
import java.util.Scanner;

class node {
    private char letter;
    private int count;
    private String code;
    private node left, right;

    public node (char _letter_, int _count_) {
        this.letter = _letter_;
        this.count = _count_;
        this.code = "";
    }

    public void setLeftNode (node _left_) {
        this.left = _left_;
    }

    public void setRightNode (node _right_) {
        this.right = _right_;
    }
}

class huffmanTree {
    
}

public class ALG_HW8_Task1 {
    public static HashMap<Character, Integer> countLetter (String _plaintext_) {
        HashMap<Character, Integer> letterTable = new HashMap<Character, Integer>();
        CharacterIterator letter = new StringCharacterIterator(_plaintext_);
        char tmp;

        while (letter.current() != CharacterIterator.DONE)
        {
            tmp = letter.current();
            if (letterTable.containsKey(tmp)) letterTable.computeIfPresent(tmp, (key, value) -> value + 1);
            else letterTable.putIfAbsent(tmp, 1);
            letter.next();
        }

        return letterTable;
    }


    public static void main (String[] args) {
        Scanner input = new Scanner(System.in);
        String plaintext;

        plaintext = input.next();
        System.out.println(countLetter(plaintext));
    }
}
