import java.text.CharacterIterator;
import java.text.StringCharacterIterator;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Scanner;

public class ALG_HW8_Task1 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String plaintext;

        plaintext = input.next();
        getHuffmanCodeTable(plaintext);
    }

    public static ArrayList<Node> getFrequencyTable(String plaintext) {
        HashMap<Character, Node> countBuffer = new HashMap<>();
        CharacterIterator letter = new StringCharacterIterator(plaintext);
        char current;
        ArrayList<Node> frequencyTable = new ArrayList<>();

        while (letter.current() != CharacterIterator.DONE) {
            current = letter.current();
            if (countBuffer.containsKey(current)) {
                countBuffer.computeIfPresent(current, (k, v) -> new Node("" + k, v.getRate() + 1));
            } else {
                countBuffer.putIfAbsent(current, new Node("" + current, 1));
            }
            letter.next();
        }

        countBuffer.forEach((k, v) -> frequencyTable.add(v));
        frequencyTable.sort(Node.compare);

        return frequencyTable;
    }

    public static Node buildHuffmanTree(ArrayList<Node> frequencyTable) {
        ArrayList<Node> buffer = new ArrayList<>(frequencyTable);

        while (buffer.size() > 1) {
            buffer.set(0, buffer.get(0).merge(buffer.get(1)));
            buffer.remove(1);
            buffer.sort(Node.compare);
        }

        return buffer.get(0);
    }

    public static void getHuffmanCode(Node root, ArrayList<Node> table) {
        if (root.isLeaf()) {
            for (Node n : table) {
                if (n.getPlaintext().equals(root.getPlaintext()) && !n.getPlaintext().isEmpty()) {
                    n.setCiphertext(root.getCiphertext());
                }
            }
        } else {
            if (root.getLeft() != null) root.getLeft().concatCiphertext(root.getCiphertext());
            if (root.getRight() != null) root.getRight().concatCiphertext(root.getCiphertext());
            getHuffmanCode(root.getLeft(), table);
            getHuffmanCode(root.getRight(), table);
        }
    }
    public static void getHuffmanCodeTable (String plaintext) {
        ArrayList<Node> table = getFrequencyTable(plaintext);
        Node root = buildHuffmanTree(table);

        getHuffmanCode(root, table);
        table.sort(Node.compareCiphertext);
        for (Node n : table) System.out.println(n.getPlaintext() + ":" + n.getCiphertext());
    }

    static class Node {
        static Comparator<Node> compare = (n1, n2) -> {
            int rate1 = n1.getRate();
            int rate2 = n2.getRate();
            if (rate1 != rate2) return rate1 < rate2 ? -1 : 1;
            else return n1.getPlaintext().compareTo(n2.getPlaintext());
        };
        static Comparator<Node> compareCiphertext = (n1, n2) -> {
            int ciphertext1 = Integer.parseInt(n1.getCiphertext(), 2);
            int ciphertext2 = Integer.parseInt(n2.getCiphertext(), 2);
            if (ciphertext1 == ciphertext2) return 0;
            return ciphertext1 < ciphertext2 ? -1 : 1;
        };
        private String ciphertext;
        private String plaintext;
        private int rate;
        private Node left;
        private Node right;

        public Node(String text, int rate) {
            plaintext = text;
            ciphertext = "";
            this.rate = rate;
            left = null;
            right = null;
        }

        String getPlaintext() {
            return plaintext;
        }

        void setPlaintext(String text) {
            this.plaintext = text;
        }

        void concatPlaintext(String text) {
            setPlaintext(plaintext + text);
        }

        String getCiphertext() {
            return ciphertext;
        }

        void setCiphertext(String text) {
            ciphertext = text;
        }

        void concatCiphertext(String text) {
            setCiphertext(text + ciphertext);
        }

        int getRate() {
            return rate;
        }

        void computeRate(int rate) {
            this.rate += rate;
        }

        Node getLeft() {
            return left;
        }

        void setLeft(Node node) {
            left = node;
            left.setCiphertext("0");
        }

        Node getRight() {
            return right;
        }

        void setRight(Node node) {
            right = node;
            right.setCiphertext("1");
        }

        boolean isLeaf() {
            return left == null && right == null;
        }

        @Override
        public String toString() {
            return "(" + plaintext + ", " + rate + ", " + ciphertext + ")";
        }

        Node merge(Node node) {
            Node merged = new Node(plaintext, rate);

            merged.concatPlaintext(node.plaintext);
            merged.computeRate(node.getRate());
            merged.setLeft(this);
            merged.setRight(node);

            return merged;
        }
    }
}