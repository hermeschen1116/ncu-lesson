import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ALG_HW8_Task3 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int nInput;
        String buffer;
        List<Node> nodeInfo;
        String errorMsg = "not complete";

        nInput = Integer.parseInt(input.nextLine());
        input.nextLine();
        for (int i = 0; i < nInput; i++) {
            buffer = input.nextLine();
            nodeInfo = getNodeList(buffer);
            if (!nodeInfo.isEmpty()) {
                if (validateTree(nodeInfo)) treeLevelTraversal(nodeInfo);
                else {
                    System.out.println(errorMsg);
                }
            } else {
                System.out.println(errorMsg);
            }
        }
    }

    public static boolean validateStringFormat(String text, String format) {
        Pattern pattern = Pattern.compile(format);
        Matcher matcher = pattern.matcher(text);

        return matcher.matches();
    }

    public static Node getNodeInfo(String infoBuffer) {
        String[] info = infoBuffer.substring(1, infoBuffer.length() - 1).split(",");
        if (validateStringFormat(infoBuffer, "\\(\\d+,\\)")) {
            return new Node(Integer.parseInt(info[0]), "");
        }
        return new Node(Integer.parseInt(info[0]), info[1]);
    }

    public static List<Node> getNodeList(String infoBuffer) {
        HashMap<String, Node> cache = new HashMap<>();
        ArrayList<Node> nodeInfo = new ArrayList<>();
        String[] infos = infoBuffer.split(" ");
        Node nodeBuffer;

        if (!validateStringFormat(infoBuffer, "(\\(\\d+,[LR]*\\) )+\\(\\)")) return Collections.emptyList();
        for (String s : infos) {
            if (s.equals("()")) break;
            if (validateStringFormat(s, "\\(\\d+,[LR]*\\)")) {
                nodeBuffer = getNodeInfo(s);
                if (cache.containsKey(nodeBuffer.getPath())) {
                    return Collections.emptyList();
                }
                cache.put(nodeBuffer.getPath(), nodeBuffer);
            } else {
                return Collections.emptyList();
            }
        }
        cache.forEach((k, v) -> nodeInfo.add(v));
        nodeInfo.sort(Node.compare);

        return nodeInfo.get(0).getPath().equals("") ? nodeInfo : Collections.emptyList();
    }

    public static boolean validateTree(List<Node> nodeInfo) {
        List<Node> nodes = new ArrayList<>(nodeInfo);
        Node root = nodes.get(0);
        Node cur;
        Node next;
        String pathBuffer;
        int cnt = 1;

        if (nodeInfo.isEmpty()) return false;
        nodes.remove(0);
        nodes.sort(Node.compare);
        for (Node n : nodes) {
            pathBuffer = n.getPath();
            cur = root;
            for (int i = 0; i < pathBuffer.length(); i++) {
                if (i == pathBuffer.length() - 1) {
                    if (pathBuffer.charAt(i) == 'L') {
                        cur.setLeft(n);
                    } else {
                        cur.setRight(n);
                    }
                    ++cnt;
                    break;
                }
                next = (pathBuffer.charAt(i) == 'L') ? cur.getLeft() : cur.getRight();
                if (next == null) return false;
                cur = next;
            }
        }
        return cnt == nodeInfo.size();
    }

    public static void treeLevelTraversal(List<Node> nodeInfo) {
        nodeInfo.sort(Node.compareLevel);
        for (Node n : nodeInfo) System.out.print(n.getValue() + " ");
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