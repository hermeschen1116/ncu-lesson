import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

public class ALG_HW8_Task3 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int nInput;
        String buffer;
        List<Node> nodeInfo;

        nInput = Integer.parseInt(input.nextLine());
        input.nextLine();
        for (int i = 0; i < nInput; i++) {
            buffer = input.nextLine();
            nodeInfo = getAllNodeInfo(buffer);
            if (isValidTree(nodeInfo)) treeLevelTraversal(nodeInfo);
            else System.out.println("not complete");
        }
    }

    public static Node getNodeInfo(String infoBuffer) {
        String[] info = infoBuffer.substring(1, infoBuffer.length() - 1).split(",");
        if (info.length == 2) return new Node(Integer.parseInt(info[0]), info[1]);
        else return new Node(Integer.parseInt(info[0]), "");
    }

    public static List<Node> getAllNodeInfo(String infoBuffer) {
        ArrayList<Node> nodeInfo = new ArrayList<>();
        String tmp = infoBuffer.substring(0, infoBuffer.length() - 3);
        String[] infos = tmp.split(" ");

        for (String s : infos) { nodeInfo.add(getNodeInfo(s)); }
        nodeInfo.sort(Node.compareLevel);

        return nodeInfo;
    }

    public static boolean isValidTree(List<Node> nodeInfo) {
        List<Node> nodes = new ArrayList<>(nodeInfo);
        Node root;
        Node cur;
        String path;
        int cnt = 1;

        nodes.sort(Node.compare);
        root = nodes.get(0);
        nodes.remove(0);
        if (!root.getPath().equals("")) { return false; }
        for (Node n : nodes) {
            path = n.getPath();
            cur = root;
            for (int i = 0; i < path.length(); i++) {
                if (i == path.length() - 1)  {
                    if (path.charAt(i) == 'L') {
                        if (cur.getLeft() == null) {
                            cur.setLeft(n);
                            ++cnt;
                        } else { return false; }
                    } else {
                        if (cur.getRight() == null) {
                            cur.setRight(n);
                            ++cnt;
                        } else { return false; }
                    }
                }
                if (path.charAt(i) == 'L') { cur = cur.left; }
                else { cur = cur.right; }
            }
        }
        return cnt == nodes.size() + 1;
    }

    public static void treeLevelTraversal(List<Node> nodeInfo) {
        nodeInfo.sort(Node.compareLevel);
        for (Node n :nodeInfo) System.out.print(n.getValue()+" ");
        System.out.println();
    }

    static class Node {
        static Comparator<Node> compare = Comparator.comparing(Node::getPath);
        static Comparator<Node> compareLevel = (n1, n2) -> {
            int pathLen1 = n1.getPath().length();
            int pathLen2 = n2.getPath().length();
            if (pathLen1 == pathLen2) return n1.getPath().compareTo(n2.getPath());
            else {
                return pathLen1 < pathLen2 ? -1 : 1;
            }
        };
        private final int value;
        private final String path;
        private Node left;
        private Node right;

        public Node(int value, String path) {
            this.value = value;
            this.path = path;
            left = null;
            right = null;
        }

        int getValue() {
            return value;
        }

        String getPath() {
            return path;
        }

        Node getLeft() {
            return left;
        }

        void setLeft(Node node) {
            left = node;
        }

        Node getRight() {
            return right;
        }

        void setRight(Node node) {
            right = node;
        }
    }
}