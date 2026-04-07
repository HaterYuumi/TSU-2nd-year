#include <iostream> 
#include <vector>
#include <random>
#include <time.h>

using namespace std;

class Node
{
public:
    int key;
    Node* right;
    Node* left;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
    ~Node() = default;
};

class Tree
{
protected:
    Node* root;

    void printer(Node* node, int level) const {
        if (node) {
            printer(node->right, level + 1);
            for (int i = 0; i < level; i++) std::cout << "  ";
            std::cout << node->key << std::endl;
            printer(node->left, level + 1);
        }
    }

    void ClearTree(Node* node) {
        if (node) {
            ClearTree(node->left);
            ClearTree(node->right);
            delete node;
        }
    }

    Node* CopyTree(Node* node) {
        if (node) {
            Node* newNode = new Node(node->key);
            newNode->left = CopyTree(node->left);
            newNode->right = CopyTree(node->right);
            return newNode;
        }
        return nullptr;
    }

public:
    Tree() : root(nullptr) {}

    Tree(int k) : root(new Node(k)) {}

    Tree(const Tree& other) {
        root = CopyTree(other.root);
    }

    ~Tree() {
        ClearTree(root);
    }

    Tree& operator=(const Tree& other) {
        if (this == &other) {
            return *this;
        }
        ClearTree(root);
        root = CopyTree(other.root);
        return *this;
    }

    Node* find(int k) {
        if (root == nullptr) {
            return nullptr;
        }
        Node* curr = root;
        while (curr && curr->key != k) {
            if (k < curr->key) {
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }
        }
        return curr;
    }

    Node* MAX_node() {
        Node* maxx = root;
        while (maxx && maxx->right) {
            maxx = maxx->right;
        }
        return maxx;
    }

    Node* MIN_node() {
        Node* minn = root;
        while (minn && minn->left) {
            minn = minn->left;
        }
        return minn;
    }

    void Add(int k) {
        Node* newNode = new Node(k);

        Node* prev = nullptr;
        Node* node = root;
        while (node) {
            prev = node;

            if (newNode->key < node->key) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }

        if (prev == nullptr) {
            root = newNode;
        }
        else if (k < prev->key) {
            prev->left = newNode;
        }
        else {
            prev->right = newNode;
        }
    }

    void Del_node(int k) {
        Node* node = root;
        Node* prev = nullptr;

        while (node && node->key != k) {
            prev = node;

            if (k < node->key) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }

        if (!node) {
            cout << "value is not found" << endl;
            return;
        }

        if (!node->left && !node->right) {
            if (node == root) {
                root = nullptr;
            }
            else if (node == prev->left) {
                prev->left = nullptr;
            }
            else {
                prev->right = nullptr;
            }
            delete node;
        }

        else if (!node->left && node->right) {
            if (node == root) {
                root = node->right;
            }
            else if (node == prev->left) {
                prev->left = node->right;
            }
            else {
                prev->right = node->right;
            }
            delete node;
        }

        else if (node->left && !node->right) {
            if (node == root) {
                root = node->left;
            }
            else if (node == prev->left) {
                prev->left = node->left;
            }
            else {
                prev->right = node->left;
            }
            delete node;
        }

        else {
            Node* minRight = node->right;
            Node* minRightParent = node;

            while (minRight->left) {
                minRightParent = minRight;
                minRight = minRight->left;
            }

            node->key = minRight->key;

            if (minRight == minRightParent->left) {
                minRightParent->left = minRight->right;
            }
            else {
                minRightParent->right = minRight->right;
            }
            delete minRight;
        }
    }

    void way_in_width() {
        vector<Node*> res;

        if (!root) return;

        vector<Node*> level;
        level.push_back(root);

        while (!level.empty()) {
            vector<Node*> next_level;

            for (auto node : level) {
                cout << node->key << " ";
                res.push_back(node);

                if (node->left)
                    next_level.push_back(node->left);

                if (node->right)
                    next_level.push_back(node->right);
            }

            level = next_level;
        }
        cout << endl;
    }

    void left_node_right() {
        if (!root) return;

        vector<Node*> st;
        Node* node = root;

        while (node || !st.empty()) {
            while (node) {
                st.push_back(node);
                node = node->left;
            }

            if (!st.empty()) {
                node = st.back();
                st.pop_back();

                cout << node->key << " ";
                node = node->right;
            }
        }
        cout << endl;
    }

    friend ostream& operator<<(ostream& out, const Tree& tree) {
        if (!tree.root) {
            out << "[Empty tree]";
            return out;
        }

        tree.printer(tree.root, 0);
        return out;
    }
};

int main()
{
    srand(time(0));

    Tree tree;
    tree.Add(5);
    tree.Add(3);
    tree.Add(7);
    tree.Add(2);
    tree.Add(4);
    tree.Add(6);
    tree.Add(10);
    tree.Add(8);
    tree.Add(15);

    cout << tree << endl;

    tree.Del_node(5);

    cout << tree << endl;

    tree.Del_node(6);

    cout << tree << endl;

    Node* min = tree.MIN_node();
    cout << "Minimum: " << min->key << endl;

    Node* max = tree.MAX_node();
    cout << "Maximum: " << max->key << endl;
    cout << endl;

    cout << "left_node_right" << endl;
    tree.left_node_right();
    cout << endl;

    cout << "way_in_width" << endl;
    tree.way_in_width();
    cout << endl;

    return 0;
}
