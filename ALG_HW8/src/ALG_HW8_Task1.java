import java.text.CharacterIterator;
import java.text.StringCharacterIterator;
import java.util.*;

public class ALG_HW8_Task1 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String plaintext;
        ArrayList<node> tmp;
        node root;

        plaintext = input.next();
        tmp = getFrequencyTable(plaintext);
        //for (ALG_HW8_Task1.node node : tmp) System.out.println(node.toString());
        root = buildHuffmanTree(tmp);
        showHuffmanTree(root);
    }

    public static ArrayList<node> getFrequencyTable(String _plaintext_) {
        HashMap<Character, node> countBuffer = new HashMap<>();
        CharacterIterator letter = new StringCharacterIterator(_plaintext_);
        char current;
        ArrayList<node> frequencyTable = new ArrayList<>();

        while (letter.current() != CharacterIterator.DONE) {
            current = letter.current();
            if (countBuffer.containsKey(current))
                countBuffer.computeIfPresent(current, (k, v) -> new node("" + k, v.getRate() + 1));
            else countBuffer.putIfAbsent(current, new node("" + current, 1));
            letter.next();
        }

        countBuffer.forEach((k, v) -> frequencyTable.add(v));
        frequencyTable.sort(node.compare);

        return frequencyTable;
    }

    public static node buildHuffmanTree(ArrayList<node> _frequencyTable_) {
        node root;
        while (_frequencyTable_.size() > 1) {
            _frequencyTable_.set(0, _frequencyTable_.get(0).merge(_frequencyTable_.get(1)));
            System.out.print("tree:");
            showHuffmanTree(_frequencyTable_.get(0));
            _frequencyTable_.remove(1);
            _frequencyTable_.sort(node.compare);
        }
        root = _frequencyTable_.get(0);
        System.out.println("root:"+root.toString());

        return root;
    }

    public static void showHuffmanTree(node _node_) {
        System.out.println(_node_.toString());
        if (_node_.getLeft() != null) showHuffmanTree(_node_.getLeft());
        if (_node_.getRight() != null) showHuffmanTree(_node_.getRight());
    }

    static class node {
        static Comparator<node> compare = (_n1_, _n2_) -> {
            int rate1 = _n1_.getRate();
            int rate2 = _n2_.getRate();
            if (rate1 != rate2) return rate1 < rate2 ? -1 : 1;
            else return _n1_.getPlaintext().compareTo(_n2_.getPlaintext());
        };
        private String ciphertext;
        private String plaintext;
        private int rate;
        private node left;
        private node right;

        public node(String _text_, int _rate_) {
            plaintext = _text_;
            ciphertext = "";
            rate = _rate_;
            left = null;
            right = null;
        }

        String getPlaintext() {
            return plaintext;
        }

        void setPlaintext(String _plaintext_) {
            plaintext = _plaintext_;
        }

        void concatPlaintext(String _text_) {
            setPlaintext(plaintext + _text_);
        }

        String getCiphertext() {
            return ciphertext;
        }
        void setCiphertext (String _ciphertext_) {
            ciphertext = _ciphertext_;
        }
        void concatCiphertext(String _text_) {
            setCiphertext(ciphertext + _text_);
        }

        int getRate() {
            return rate;
        }

        void computeRate(int _rate_) {
            rate += _rate_;
        }

        node getLeft() {
            return left;
        }

        void setLeft(node _node_) {
            left = _node_;
        }

        node getRight() {
            return right;
        }

        void setRight(node _node_) {
            right = _node_;
        }
        @Override
        public String toString() {
            return "(" + plaintext + ", " + rate + ", " + ciphertext + ")";
        }

        node merge(node _node_) {
            node merged = new node(plaintext, rate);

            merged.concatPlaintext(_node_.plaintext);
            merged.computeRate(_node_.getRate());
            merged.setLeft(new node(plaintext, rate));
            merged.setRight(new node(_node_.getPlaintext(), _node_.getRate()));

            return merged;
        }
    }
}