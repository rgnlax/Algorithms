//2_4. Выведите элементы в порядке level­order (по слоям, “в ширину”).

#include <iostream>
#include <queue>

template <class T>
struct Node {
    T data;
    Node *left;
    Node *right;
    
    Node(T data) : data(data), left(NULL), right(NULL) {}
};

template <class T>
class BinaryTree {
public:
    Node<T> *root;
    BinaryTree();
    ~BinaryTree();
    void add(Node<T> *&, T);
    void leveOrderPrint();
    void deleteNode(Node<T> *);
};

int main() {
    BinaryTree<int> *tree = new BinaryTree<int>();
    
    int count;
    std::cin >> count;
    
    for (int i = 0; i < count; ++i) {
        int data;
        std::cin >> data;
        tree->add(tree->root, data);
    }
    
    tree->leveOrderPrint();
    
    delete tree;
    return 0;
}

template <class T>
BinaryTree<T>::~BinaryTree<T>() {
    deleteNode(root);
}

template <class T>
void BinaryTree<T>::deleteNode(Node<T> *node) {
    if (node == NULL) {
        return;
    }
    
    deleteNode(node->left);
    deleteNode(node->right);
    
    delete node;
}

template <class T>
void BinaryTree<T>::add(Node<T> *& node, T data) {
    if (node != NULL) {
        if (node->data > data) {
            add(node->left, data);
        } else {
            add(node->right, data);
        }
    } else {
        node = new Node<T>(data);
    }
}

template <class T>
void BinaryTree<T>::leveOrderPrint() {
    std::queue<Node<T> *>queue;
    if (root == NULL) {
        return;
    }
    queue.push(root);
    while (!queue.empty()) {
        Node<T> *node = queue.front();
        std::cout << node->data << ' ';
        queue.pop();
        
        if (node->left != NULL) {
            queue.push(node->left);
        }
        
        if (node->right != NULL) {
            queue.push(node->right);
        }
        
    }
}

template <class T>
BinaryTree<T>::BinaryTree() {
    root = NULL;
}






