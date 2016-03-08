//1_2. Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв. Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте в случае, когда коэффициент заполнения таблицы достигает 3/4. Для разрешения коллизий используйте двойное хеширование.


#include <iostream>
#include <string>
#include <vector>

#define INITIAL_SIZE 8
#define REHASH_FACTOR 3.0/4.0

using std::string;
using std::vector;

const int hash_param_A = 37;
const int hash_param_B = 59;

int HashA(const string& s, int m) {
    int result = 0;
    for (int i = 0; i < s.length(); ++i) {
        result = (result * hash_param_A + s[i]) % m;
    }
    return result;
}

int HashB(const string& s, int m) {
    int result = 0;
    for (int i = 0; i < s.length(); ++i) {
        result = (result * hash_param_B + s[i]) % m;
    }
    return (2 * result + 1) % m;
}

struct Node {
    string Data;
    bool isDeleted;
    
    Node(const string& data) : Data(data), isDeleted(false) {}
};

class HashTable {
public:
    HashTable();
    
    bool Has(const string& s);
    // Возвращает false, если элемент уже есть.
    bool Add(const string& s);
    // Возвращает false, если элемента нет.
    bool Remove(const string& s);
    
private:
    vector<Node *> table;
    int size; // Количество элементов.
    int realSize;
    void rehash();
};

HashTable::HashTable() : size(INITIAL_SIZE), realSize(0), table(INITIAL_SIZE, NULL){
    
}

bool HashTable::Has(const string &s) {
    int hash = HashA(s, size);
    int secondHash = HashB(s, size);
    int i = 0;
    while (table[hash] != NULL && i < size) {
        if (table[hash]->Data == s && !table[hash]->isDeleted) {
            return true;
        }
        hash = (hash + secondHash) % size;
        i++;
     }
    return false;
}

bool HashTable::Add(const string &s) {
    if ( (float) realSize / (float) size >= REHASH_FACTOR) {
        rehash();
    }
    int hash = HashA(s, size);
    int secondHash = HashB(s, size);

    int i = 0;
    int deletedNodeIndex = -1;
    while (table[hash] != NULL && i < size) {
        if (table[hash]->Data == s && !table[hash]->isDeleted) {
            return false;
        }
        if (table[hash]->isDeleted && deletedNodeIndex < 0) {
            deletedNodeIndex = hash;
        }
        hash = (hash + secondHash) % size;
        ++i;
    }
    
    if (deletedNodeIndex >= 0) {
        table[deletedNodeIndex]->Data = s;
        table[deletedNodeIndex]->isDeleted = false;
    } else {
        table[hash] = new Node(s);
    }
    
    realSize++;
    return true;
}

bool HashTable::Remove(const string &s) {
    int hash = HashA(s, size);
    int secondHash = HashB(s, size);

    int i = 0;
    while (table[hash] != NULL && i < size) {
        if (table[hash]->Data == s && !table[hash]->isDeleted) {
            table[hash]->isDeleted = true;
            realSize--;
            return true;
        }
        hash = (hash + secondHash) % size;
        ++i;
    }
    return false;
}

void HashTable::rehash() {
    int newSize = size * 2;
    std::vector<Node *> newTable(newSize, NULL);
    for (int i = 0; i < size; ++i) {
        if (table[i] != NULL && !table[i]->isDeleted) {
            std::string data = table[i]->Data;
            int currentHash = HashA(data, newSize);
            int anotherHash = HashB(data, newSize);
            int j = 0;
            
            while (newTable[currentHash] != NULL && j < newSize) {
                currentHash = (currentHash + anotherHash) % newSize;
                ++j;
            }
            newTable[currentHash] = new Node(data);
        }
    }
    
    table = newTable;
    size = newSize;

}

void execute_command(char const command, std::string const &s, HashTable &table) {
    bool result;
    switch (command) {
        case '+':
            result = table.Add(s);
            break;
        case '-':
            result = table.Remove(s);
            break;
        case '?':
            result = table.Has(s);
            break;
        default:
            result = false;
    }
    
    std::cout << ( (result) ? "OK" : "FAIL" ) << std::endl;
}

int main() {
    char command;
    string data;
    
    HashTable table;
    while (std::cin >> command >> data) {
        execute_command(command, data, table);
    }
    
    return 0;
}

