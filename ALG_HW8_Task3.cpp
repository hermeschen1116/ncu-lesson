#include <iostream>
#include <string>
#include <regex>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
private:
    int value;
    string path;
    Node *left{};
    Node *right{};

public:
    explicit Node(int v = 0, string  p = "", Node *n1 = nullptr, Node* n2 = nullptr):
    value(v), path(std::move(p)), left(n1), right(n2) {};

    [[nodiscard]] int getValue() const;

    [[nodiscard]] string getPath() const;

    Node *getLeft();

    void setLeft(Node *node);

    Node *getRight();

    void setRight(Node *node);

};

Node *getNodeInfo(const string &nodeInfo);

bool findNode(const vector<Node *> &nodeList, const string &path);

vector<Node *> getNodeList();

bool compareNode(Node *n1, Node *n2);

bool compareNodeLevel(Node *n1, Node *n2);

bool validateTree(vector<Node *> nodeList);

void treeLevelTraversal(vector<Node *> nodeList);

int main() {
    int nInput;
    vector<Node *> nodeInfoBuffer;
    regex inputPattern(R"((\(\d+,[LR]*\)))");

    cin >> nInput;
    for (int i = 0; i < nInput; i++) {
        nodeInfoBuffer = getNodeList();
        if (!nodeInfoBuffer.empty()) {
            if (validateTree(nodeInfoBuffer)) treeLevelTraversal(nodeInfoBuffer);
            else cout << "not complete" << endl;
        } else cout << "not complete" << endl;
    }

    return 0;
}

int Node::getValue() const { return value; }

string Node::getPath() const { return path; }

Node *Node::getLeft() { return left; }

void Node::setLeft(Node *node) { left = node; }

Node *Node::getRight() { return right; }

void Node::setRight(Node *node) { right = node; }

Node *getNodeInfo(const string &nodeInfo) {
    unsigned long splitPoint = nodeInfo.find(',');
    unsigned long length = nodeInfo.length();
    int value = stoi(nodeInfo.substr(1, splitPoint - 1));
    string path = nodeInfo.substr(splitPoint + 1, length - splitPoint - 2);

    if (regex nodePattern(R"(\(\d+,\))"); !regex_match(nodeInfo, nodePattern)) return new Node(value, path);
    return new Node(value);
}

bool findNode(const vector<Node *> &nodeList, const string &path) {
    return any_of(nodeList.begin(), nodeList.end(), [path](Node const *n) { return n->getPath() == path; });
}

vector<Node *> getNodeList() {
    string inputBuffer;
    regex inputPattern(R"((\(\d+,[LR]*\)))");
    Node *nodeBuffer;
    vector<Node *> nodeList;

    while (true) {
        cin >> inputBuffer;
        if (inputBuffer == "()") break;
        if (regex_match(inputBuffer, inputPattern)) {
            nodeBuffer = getNodeInfo(inputBuffer);
            if (findNode(nodeList, nodeBuffer->getPath())) return {};
            nodeList.push_back(nodeBuffer);
        } else return {};
    }
    sort(nodeList.begin(), nodeList.end(), compareNode);

    if (nodeList.empty()) return {};
    if (!nodeList[0]->getPath().empty()) return {};
    return nodeList;
}

bool compareNode(Node *n1, Node *n2) { return n1->getPath() < n2->getPath(); }

bool compareNodeLevel(Node *n1, Node *n2) {
    unsigned long pathLength1 = n1->getPath().length();
    unsigned long pathLength2 = n2->getPath().length();
    if (pathLength1 == pathLength2) return compareNode(n1, n2);
    else return pathLength1 < pathLength2;
}

bool validateTree(vector<Node *> nodeList) {
    vector<Node *> nodes;
    Node *root = nodeList[0];
    Node *cur;
    Node *next;
    string pathBuffer;
    int cnt = 1;

    if (nodeList.empty()) return false;
    for (int i = 1; i < nodeList.size(); i++) nodes.push_back(nodeList[i]);
    sort(nodes.begin(), nodes.end(), compareNode);
    for (Node *n: nodes) {
        pathBuffer = n->getPath();
        cur = root;
        for (int i = 0; i < pathBuffer.length() - 1; i++) {
            next = (pathBuffer[i] == 'L') ? cur->getLeft() : cur->getRight();
            if (next != nullptr) cur = next;
            else {
                nodes.clear();
                return false;
            }
        }
        if (pathBuffer[pathBuffer.length() - 1] == 'L') cur->setLeft(n);
        else cur->setRight(n);
        ++cnt;
    }
    nodes.clear();
    return cnt == nodeList.size();
}

void treeLevelTraversal(vector<Node *> nodeList) {
    sort(nodeList.begin(), nodeList.end(), compareNodeLevel);
    cout << nodeList[0]->getValue();
    for (int i = 1; i < nodeList.size(); i++) cout << " " << nodeList[i]->getValue();
    cout << endl;
}