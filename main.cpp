#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> statuses = {"never used", "tombstone", "occupied"};


struct table_element{
    std::string status;
    std::string key;
};

class hash_table {
    public:
        hash_table();
        void insert(std::string);
        void deletion(std::string);
        int search(std::string);
        void printTable();
    protected:
        std::vector<table_element> table;
};

void hash_table::printTable() {
    bool first = true;
    for (int i = 0; i < 26; i++) {
        if (!table[i].key.empty() && table[i].status == statuses[2]) {
            if (!first) std::cout << " ";
            std::cout << table[i].key;
            first = false;
        }
    }
    std::cout << std::endl;
};


hash_table::hash_table() {
    table_element model;
    model.status = statuses[0];
    model.key = "";
    for(int i = 0; i<26; i++) {
        table.push_back(model);
    }
}

int hash_table::search(std::string key) {
    int index = 0;
    if (!key.empty() && key.length() <= 10) { // Check if the string is not empty
        char lastChar = key.back();
        index = lastChar - 'a';
    } else {return -1;}

    for(int i = 0; i<26; i++) {
        if(table[index].key == key) {
            return index;
        } else {
            index = (index + 1) % 26;
        }
    }
    return -1;
}

void hash_table::insert(std::string key) {
    if(search(key) != -1) {
        return;
    };
    int index = 0;
    if (!key.empty() && key.length() <= 10) { // Check if the string is not empty
        char lastChar = key.back();
        index = lastChar - 'a';
    } else {return;}

    for(int i = 0; i<26; i++) {

        if(table[index].status != statuses[2]) {
            table[index].key = key;
            table[index].status = statuses[2];
            break;
        } else {
            index = (index + 1) % 26;
        }
    }
}

void hash_table::deletion(std::string key) {
    int index = search(key);
    if(index > -1) {
        table[index].status = statuses[1];
        table[index].key = "";
    }
}

int main() {
    hash_table Hash;
    std::string line;
    std::getline(std::cin, line);

    std::string token;
    for (size_t i = 0; i <= line.size(); i++) {
        if (i == line.size() || line[i] == ' ') {
            if (!token.empty()) {
                char op = token[0];
                std::string word = token.substr(1);
                if (op == 'A') {
                    Hash.insert(word);
                } else if (op == 'D') {
                    Hash.deletion(word);
                }
            }
            token.clear();
        } else {
            token += line[i];
        }
    }

    // Output all keys from a–z separated by spaces
    Hash.printTable();

    return 0;
}
