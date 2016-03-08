//3_2. ​Вычислить количество узлов в самом широком слое декартового дерева и
//количество узлов в самом широком слое наивного дерева поиска. Вывести их разницу.

#include <iostream>
#include <queue>
#include <vector>

template <class T>
struct DataNode {
    T *data;
    int level;
    DataNode(T *data, int level):data(data), level(level) {}
};

/*-------------------------------------------------------*/
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
    int getMaxWide();
};

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

template <class T>
int BinaryTree<T>::getMaxWide() {
    int level = 1;
    std::queue<DataNode<Node<T> > *> queue;
    std::vector<int>counts;
    if (root == NULL) {
        return 0;
    }
    
    queue.push(new DataNode<Node<T> >(root, 1));

    int level_wide = 0;
    
    while (!queue.empty()) {
        
        DataNode<Node<T> > *node = queue.front();
        
        if (level == node->level) {
            level_wide++;
        } else {
            counts.push_back(level_wide);
            level_wide = 1;
            level = node->level;
        }
        
        queue.pop();
        
        if (node->data->left != NULL) {
            queue.push(new DataNode<Node<T> >(node->data->left, level + 1));
        }
        
        if (node->data->right != NULL) {
            queue.push(new DataNode<Node<T> >(node->data->right, level + 1));
        }
        
        delete node;
    }
    int max = counts[0];
    for (int i = 1; i < counts.size(); ++i) {
        if (counts[i] > max) {
            max = counts[i];
        }
    }
    
    return max;
    
}
/*----------------------------------------------------*/

template <class T>
struct TreapNode {
    T data;
    int priority;
    TreapNode<T> *left;
    TreapNode<T> *right;
    
    TreapNode(T data, int priority) : data(data), left(NULL), right(NULL), priority(priority) { }
};

template <class T>
class DecartTree {
public:
    TreapNode<T> *root;
    
    DecartTree(){
        root = NULL;
    }
    ~DecartTree(){
        deleteNode(root);
    }
    
    void add(TreapNode<T> *&, T, int);
    int getMaxWide();
private:
    void split(TreapNode<T> *, T, TreapNode<T> *&, TreapNode<T> *&);
    TreapNode<T> *merge(TreapNode<T> *, TreapNode<T> *);
    void deleteNode(TreapNode<T> *);
    
};

template <class T>
void DecartTree<T>::deleteNode(TreapNode<T> *node) {
    if (node == NULL) {
        return;
    }
    
    deleteNode(node->left);
    deleteNode(node->right);
    
    delete node;
}

template<class T>
void DecartTree<T>::split(TreapNode<T> *currentNode, T data, TreapNode<T> *&left, TreapNode<T> *&right) {
    if (currentNode == 0) {
        left = 0;
        right = 0;
    } else if (currentNode->data <= data) {
        split(currentNode->right, data, currentNode->right, right);
        left = currentNode;
    } else {
        split(currentNode->left, data, left, currentNode->left);
        right = currentNode;
    }
}

template<class T>
TreapNode<T> *DecartTree<T>::merge(TreapNode<T> *left, TreapNode<T> *right) {
    if (left == 0 || right == 0) {
        return left == 0 ? right : left;
    }
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    }
    right->left = merge(left, right->left);
    return right;
}

template<class T>
void DecartTree<T>::add(TreapNode<T> *&node, T data, int priority) {
    if (node != NULL) {
        if (node->priority < priority) {
            TreapNode<T> *left = NULL;
            TreapNode<T> *right = NULL;
            
            split(node, data, left, right);
            
            TreapNode<T> *newNode = new TreapNode<T>(data, priority);
            newNode->left = left;
            newNode->right = right;
            
            node = newNode;
            
            return;
        }
        if (node->data > data) {
            add(node->left, data, priority);
        }
        else {
            add(node->right, data, priority);
        }
    } else {
        node = new TreapNode<T>(data, priority);
    }
}

template <class T>
int DecartTree<T>::getMaxWide() {
    int level = 1;
    std::queue<DataNode<TreapNode<T> > *> queue;
    std::vector<int>counts;
    if (root == NULL) {
        return 0;
    }
    queue.push(new DataNode<TreapNode<T> >(root, 1));
    
    int level_wide = 0;
    
    while (!queue.empty()) {
        
        DataNode<TreapNode<T> > *node = queue.front();
        
        if (level == node->level) {
            level_wide++;
        } else {
            counts.push_back(level_wide);
            level_wide = 1;
            level = node->level;
        }
        
        queue.pop();
        
        if (node->data->left != NULL) {
            queue.push(new DataNode<TreapNode<T> >(node->data->left, level + 1));
        }
        
        if (node->data->right != NULL) {
            queue.push(new DataNode<TreapNode<T> >(node->data->right, level + 1));
        }
        
        delete node;
    }
    int max = counts[0];
    for (int i = 1; i < counts.size(); ++i) {
        if (counts[i] > max) {
            max = counts[i];
        }
    }
    
    return max;

}

int main() {
    BinaryTree<int> *naiveTree = new BinaryTree<int>();
    DecartTree<int> *decartTree = new DecartTree<int>();
    
    int count;
    std::cin >> count;
    
    int data;
    int priority;
    
    for (int i = 0; i < count; ++i) {
        std::cin >> data >> priority;
        naiveTree->add(naiveTree->root, data);
        decartTree->add(decartTree->root, data, priority);
    }
    
    int decartMaxCount = decartTree->getMaxWide();
    int naiveMaxCount = naiveTree->getMaxWide();
    
    std::cout << decartMaxCount - naiveMaxCount;
    
    delete naiveTree;
    delete decartTree;
    
    return 0;
}















