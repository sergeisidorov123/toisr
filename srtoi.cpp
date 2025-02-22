#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Guitar {
    string brand;
    string model;
    int strings;
    int frets;
    string material;
    string shape;
    bool isDeleted = false; // Флаг для пометки удаленных гитар

    Guitar(string b = "", string m = "", int s = 0, int f = 0, string n = "", string sh = "")
        : brand(b), model(m), strings(s), frets(f), material(n), shape(sh), isDeleted(false) {
    }
};


// Для бренда
struct Index {
    string value; 
    int index;    
};

// Для количества струн
struct StringsIndex {
    int value;    
    int index;    
};

// Для третьей части
struct Node{
    Guitar data;    // Данные 
    Node* next;     // Указатель на следующий элемент

    Node(const Guitar& g) : data(g), next(nullptr) {}
};

// Функция ввода данных о гитарах
Guitar* inputGuitars(int& n) {
    cout << "Введите количество гитар: ";
    cin >> n;
    cin.ignore(); // Очистка буфера после ввода числа

    Guitar* guitars = new Guitar[n];

    for (int i = 0; i < n; i++) {
        string brand, model, material, shape;
        int strings, frets;

        cout << "Гитара " << i + 1 << ":\n";
        cout << "Производитель: ";
        getline(cin, brand);
        cout << "Модель: ";
        getline(cin, model);
        cout << "Количество струн: ";
        cin >> strings;
        cout << "Количество ладов: ";
        cin >> frets;
        cin.ignore();
        cout << "Материал грифа: ";
        getline(cin, material);
        cout << "Форма: ";
        getline(cin, shape);

        guitars[i] = Guitar(brand, model, strings, frets, material, shape);
    }
    return guitars;
}

//ЧАСТЬ 1

// Создание индексов по двум атрибутам
void createIndexes(const Guitar* guitars, int n, Index* brandIndex, StringsIndex* stringsIndex) {
    for (int i = 0; i < n; i++) {
        brandIndex[i] = { guitars[i].brand, i };
        stringsIndex[i] = { guitars[i].strings, i };
    }

    // Сортировка индекса по возрастанию для производителя
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (brandIndex[i].value > brandIndex[j].value) {
                swap(brandIndex[i], brandIndex[j]);
            }
        }
    }

    // Сортировка индекса по убыванию для количества струн
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (stringsIndex[i].value < stringsIndex[j].value) {
                swap(stringsIndex[i], stringsIndex[j]);
            }
        }
    }
}

// Вывод
void printGuitars(const Guitar* guitars, int n) {
    cout << "\nСписок гитар:\n";
    for (int i = 0; i < n; i++) {
        cout << setw(8) << left << guitars[i].brand << "|" << setw(15) << left << guitars[i].model << "|"
            << left << guitars[i].strings << " струн| "
            << left << guitars[i].frets << " ладов| "
            << setw(15) << guitars[i].material << "| "
            << guitars[i].shape << "\n";
    }
}

// Сортированный вывод
void printSortedGuitars(const Guitar* guitars, int n, const Index* brandIndex, const StringsIndex* stringsIndex) {
    cout << "\nГитары, отсортированные в лексикографическом порядке по возрастанию:\n"; // Для производителя
    for (int i = 0; i < n; i++) {
        const Guitar& guitar = guitars[brandIndex[i].index];
        cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
            << left << guitar.strings << " струн| "
            << left << guitar.frets << " ладов| "
            << setw(15) << guitar.material << "| "
            << guitar.shape << "\n";
    }
    cout << "------------------------------------------\n";

    cout << "\nГитары, отсортированные по количеству струн по убыванию:\n"; // Для струн
    for (int i = 0; i < n; i++) {
        const Guitar& guitar = guitars[stringsIndex[i].index];
        cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
            << left << guitar.strings << " струн| "
            << left << guitar.frets << " ладов| "
            << setw(15) << guitar.material << "| "
            << guitar.shape << "\n";
    }
    cout << "------------------------------------------\n";
}

// Рекурсивный бинарный поиск
int binarySearchRecursive(const Index* index, const string& target, int left, int right) {
    if (left > right) {
        return -1; // Элемент не найден
    }

    int mid = left + (right - left) / 2;

    if (index[mid].value == target) {
        return mid; 
    }
    else if (index[mid].value < target) {
        return binarySearchRecursive(index, target, mid + 1, right); 
    }
    else {
        return binarySearchRecursive(index, target, left, mid - 1); 
    }
}

// Функция поиска по производителю с использованием рекурсивного бинарного поиска
void searchByBrandRecursive(const Guitar* guitars, int n, const Index* brandIndex, const string& targetBrand) {
    int index = binarySearchRecursive(brandIndex, targetBrand, 0, n - 1);

    if (index == -1) {
        cout << "Гитары с производителем '" << targetBrand << "' не найдены.\n";
    }
    else {
        cout << "\nРезультаты поиска по производителю '" << targetBrand << "':\n";
        const Guitar& guitar = guitars[brandIndex[index].index];
        cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
            << left << guitar.strings << " струн| "
            << left << guitar.frets << " ладов| "
            << setw(15) << guitar.material << "| "
            << guitar.shape << "\n";
    }
}

// Итерационный бинарный поиск
int binarySearchIterative(const StringsIndex* index, int target, int n) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (index[mid].value == target) {
            return mid; 
        }
        else if (index[mid].value < target) {
            right = mid - 1; 
        }
        else {
            left = mid + 1; 
        }
    }

    return -1; // Элемент не найден
}

// Функция поиска по количеству струн с использованием итерационного бинарного поиска
void searchByStringsIterative(const Guitar* guitars, int n, const StringsIndex* stringsIndex, int targetStrings) {
    int index = binarySearchIterative(stringsIndex, targetStrings, n);

    if (index == -1) {
        cout << "Гитары с количеством струн '" << targetStrings << "' не найдены.\n";
    }
    else {
        cout << "\nРезультаты поиска по количеству струн '" << targetStrings << "':\n";
        const Guitar& guitar = guitars[stringsIndex[index].index];
        cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
            << left << guitar.strings << " струн| "
            << left << guitar.frets << " ладов| "
            << setw(15) << guitar.material << "| "
            << guitar.shape << "\n";
    }
}

// Функция для редактирования записи по индексу
void editGuitar(Guitar* guitars, int n, Index* brandIndex, StringsIndex* stringsIndex, int index) {
    if (index < 0 || index >= n) {
        cout << "Некорректный номер!\n";
        return;
    }

    Guitar& guitar = guitars[index];

    cout << "Текущие данные гитары:\n";
    cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
        << left << guitar.strings << " струн| "
        << left << guitar.frets << " ладов| "
        << setw(15) << guitar.material << "| "
        << guitar.shape << "\n";

    string brand, model, material, shape;
    int strings, frets;

    cout << "Введите новые данные:\n";
    cout << "Производитель: ";
    getline(cin, brand);
    cout << "Модель: ";
    getline(cin, model);
    cout << "Количество струн: ";
    cin >> strings;
    cout << "Количество ладов: ";
    cin >> frets;
    cin.ignore();
    cout << "Материал грифа: ";
    getline(cin, material);
    cout << "Форма: ";
    getline(cin, shape);

    // Обновление данных
    guitar.brand = brand;
    guitar.model = model;
    guitar.strings = strings;
    guitar.frets = frets;
    guitar.material = material;
    guitar.shape = shape;

    // Обновление индексов
    for (int i = 0; i < n; i++) {
        if (brandIndex[i].index == index) {
            brandIndex[i].value = brand;
        }
        if (stringsIndex[i].index == index) {
            stringsIndex[i].value = strings;
        }
    }

    // Сортировка индексов
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (brandIndex[i].value > brandIndex[j].value) {
                swap(brandIndex[i], brandIndex[j]);
            }
            if (stringsIndex[i].value < stringsIndex[j].value) {
                swap(stringsIndex[i], stringsIndex[j]);
            }
        }
    }

    cout << "Данные гитары успешно обновлены!\n";
}

// Функция для вывода записей для производителя
int printGuitarsByBrand(const Guitar* guitars, const Index* brandIndex, int n, const string& targetBrand) {
    cout << "\nГитары с производителем '" << targetBrand << "':\n";
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (brandIndex[i].value == targetBrand) {
            const Guitar& guitar = guitars[brandIndex[i].index];
            cout << "Номер: " << brandIndex[i].index + 1 << " | "
                << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
                << left << guitar.strings << " струн| "
                << left << guitar.frets << " ладов| "
                << setw(15) << guitar.material << "| "
                << guitar.shape << "\n";
            count++;
        }
    }
    if (count == 0) {
        cout << "Гитары с производителем '" << targetBrand << "' не найдены.\n";
    }
    return count; // Для построения дальнейшей логики в мейне
}

// Функция для вывода записей для струн
int printGuitarsByStrings(const Guitar* guitars, const StringsIndex* stringsIndex, int n, int targetStrings) {
    cout << "\nГитары с количеством струн '" << targetStrings << "':\n";
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (stringsIndex[i].value == targetStrings) {
            const Guitar& guitar = guitars[stringsIndex[i].index];
            cout << "Номер: " << stringsIndex[i].index + 1 << " | "
                << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
                << left << guitar.strings << " струн| "
                << left << guitar.frets << " ладов| "
                << setw(15) << guitar.material << "| "
                << guitar.shape << "\n";
            count++;
        }
    }
    if (count == 0) {
        cout << "Гитары с количеством струн '" << targetStrings << "' не найдены.\n";
    }
    return count;
}

// Функция для выбора записи по индексу (для удаления и редактирования)
int selectGuitarIndex(int n) {
    int index;
    cout << "Найдено несколько гитар, введите номер гитары для изменения: ";
    cin >> index;
    cin.ignore(); // Очистка буфера

    if (index < 1 || index > n) {
        cout << "Некорректно введен номер!\n";
        return -1;
    }
    return index - 1;
}

// Удаление гитар по производителю
void deleteGuitarByBrand(Guitar*& guitars, int& n, Index*& brandIndex, StringsIndex*& stringsIndex, const string& targetBrand) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (guitars[i].brand == targetBrand) {
            count++;
        }
    }

    if (count == 0) {
        cout << "Гитары с производителем '" << targetBrand << "' не найдены.\n";
        return;
    }

    if (count == 1) {
        for (int i = 0; i < n; i++) {
            if (guitars[i].brand == targetBrand) {
                for (int j = i; j < n - 1; j++) {
                    guitars[j] = guitars[j + 1];
                }
                n--;

                delete[] brandIndex;
                delete[] stringsIndex;
                brandIndex = new Index[n];
                stringsIndex = new StringsIndex[n];
                createIndexes(guitars, n, brandIndex, stringsIndex);

                cout << "Гитара успешно удалена!\n";
                return;
            }
        }
    }

    printGuitarsByBrand(guitars, brandIndex, n, targetBrand);

    int indexToDelete = selectGuitarIndex(n);
    if (indexToDelete == -1) {
        return;
    }

    for (int i = indexToDelete; i < n - 1; i++) {
        guitars[i] = guitars[i + 1];
    }

    n--;

    delete[] brandIndex;
    delete[] stringsIndex;
    brandIndex = new Index[n];
    stringsIndex = new StringsIndex[n];
    createIndexes(guitars, n, brandIndex, stringsIndex);

    cout << "Гитара успешно удалена!\n";
}

// Удаление гитар по количеству струн
void deleteGuitarByStrings(Guitar*& guitars, int& n, Index*& brandIndex, StringsIndex*& stringsIndex, int targetStrings) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (guitars[i].strings == targetStrings) {
            count++;
        }
    }

    if (count == 0) {
        cout << "Гитары с количеством струн '" << targetStrings << "' не найдены.\n";
        return;
    }

    if (count == 1) {
        for (int i = 0; i < n; i++) {
            if (guitars[i].strings == targetStrings) {
                for (int j = i; j < n - 1; j++) {
                    guitars[j] = guitars[j + 1];
                }
                n--;

                delete[] brandIndex;
                delete[] stringsIndex;
                brandIndex = new Index[n];
                stringsIndex = new StringsIndex[n];
                createIndexes(guitars, n, brandIndex, stringsIndex);

                cout << "Гитара успешно удалена!\n";
                return;
            }
        }
    }

    printGuitarsByStrings(guitars, stringsIndex, n, targetStrings);

    int indexToDelete = selectGuitarIndex(n);
    if (indexToDelete == -1) {
        return;
    }

    for (int i = indexToDelete; i < n - 1; i++) {
        guitars[i] = guitars[i + 1];
    }

    n--;

    delete[] brandIndex;
    delete[] stringsIndex;
    brandIndex = new Index[n];
    stringsIndex = new StringsIndex[n];
    createIndexes(guitars, n, brandIndex, stringsIndex);

    cout << "Гитара успешно удалена!\n";
}

//ЧАСТЬ 2

//Описание стракта по производителю
struct BrandTreeNode {
    string key;   
    int index;    
    BrandTreeNode* left;
    BrandTreeNode* right;

    BrandTreeNode(string k, int i) : key(k), index(i), left(nullptr), right(nullptr) {}
};

//Описание стракта по кол-ву струн
struct StringsTreeNode {
    int key;      
    int index;    
    StringsTreeNode* left;
    StringsTreeNode* right;

    StringsTreeNode(int k, int i) : key(k), index(i), left(nullptr), right(nullptr) {}
};


// Функция для добавления узлов в дерево по производителю
BrandTreeNode* insertBrand(BrandTreeNode* root, string key, int index) {
    if (root == nullptr) {
        return new BrandTreeNode(key, index);
    }

    if (key < root->key) {
        root->left = insertBrand(root->left, key, index);
    }
    else {
        root->right = insertBrand(root->right, key, index);
    }

    return root;
}

// Функция для добавления узлов в дерево по кол-ву струн
StringsTreeNode* insertStrings(StringsTreeNode* root, int key, int index) {
    if (root == nullptr) {
        return new StringsTreeNode(key, index);
    }

    if (key < root->key) {
        root->left = insertStrings(root->left, key, index);
    }
    else {
        root->right = insertStrings(root->right, key, index);
    }

    return root;
}


// Обход дерева по возрастанию для производителя
void inOrderPassBrand(BrandTreeNode* root, const Guitar* guitars) {
    if (root == nullptr) return;

    inOrderPassBrand(root->left, guitars);
    const Guitar& guitar = guitars[root->index];
    cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
        << left << guitar.strings << " струн| "
        << left << guitar.frets << " ладов| "
        << setw(15) << guitar.material << "| "
        << guitar.shape << "\n\n";
    inOrderPassBrand(root->right, guitars);
}

// Обход дерева по возрастанию для кол-ва струн
void inOrderPassStrings(StringsTreeNode* root, const Guitar* guitars) {
    if (root == nullptr) return;

    inOrderPassStrings(root->left, guitars);
    const Guitar& guitar = guitars[root->index];
    cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
        << left << guitar.strings << " струн| "
        << left << guitar.frets << " ладов| "
        << setw(15) << guitar.material << "| "
        << guitar.shape << "\n\n";
    inOrderPassStrings(root->right, guitars);
}

// Обход по убыванию для ключа производителя
void unOrderPassBrand(BrandTreeNode* root, const Guitar* guitars) {
    if (root == nullptr) return;

    unOrderPassBrand(root->right, guitars);
    const Guitar& guitar = guitars[root->index];
    cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
        << left << guitar.strings << " струн| "
        << left << guitar.frets << " ладов| "
        << setw(15) << guitar.material << "| "
        << guitar.shape << "\n";
    unOrderPassBrand(root->left, guitars);
}

// Объход по убыванию для ключа кол-ва струн
void unOrderPassStrings(StringsTreeNode* root, const Guitar* guitars) {
    if (root == nullptr) return;

    unOrderPassStrings(root->right, guitars);
    const Guitar& guitar = guitars[root->index];
    cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
        << left << guitar.strings << " струн| "
        << left << guitar.frets << " ладов| "
        << setw(15) << guitar.material << "| "
        << guitar.shape << "\n";
    unOrderPassStrings(root->left, guitars);
}


// Функция поиска по ключу для производителя
void searchByBrand(BrandTreeNode* root, const Guitar* guitars, const string& key) {
    if (root == nullptr) {
        cout << "Гитара с производителем '" << key << "' не найдена.\n";
        return;
    }

    if (key == root->key) {
        const Guitar& guitar = guitars[root->index];
        cout << "Найдена гитара:\n";
        cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
            << left << guitar.strings << " струн| "
            << left << guitar.frets << " ладов| "
            << setw(15) << guitar.material << "| "
            << guitar.shape << "\n\n";
    }
    else if (key < root->key) {
        searchByBrand(root->left, guitars, key);
    }
    else {
        searchByBrand(root->right, guitars, key);
    }
}

// Функция поиска по ключу для кол-ва струн
void searchByStrings(StringsTreeNode* root, const Guitar* guitars, int key) {
    if (root == nullptr) {
        cout << "Гитара с количеством струн '" << key << "' не найдена.\n";
        return;
    }

    if (key == root->key) {
        const Guitar& guitar = guitars[root->index];
        cout << "Найдена гитара:\n";
        cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
            << left << guitar.strings << " струн| "
            << left << guitar.frets << " ладов| "
            << setw(15) << guitar.material << "| "
            << guitar.shape << "\n\n";
    }
    else if (key < root->key) {
        searchByStrings(root->left, guitars, key);
    }
    else {
        searchByStrings(root->right, guitars, key);
    }
}

// Удаление записи из массива
void deleteFromArray(Guitar*& guitars, int& n, int index) {
    if (index < 0 || index >= n) {
        cout << "Некорректный индекс для удаления!\n";
        return;
    }

    for (int i = index; i < n - 1; i++) {
        guitars[i] = guitars[i + 1];
    }
    n--;
}

// Удаление узла из дерева
BrandTreeNode* deleteFromBrandTree(BrandTreeNode* root, const string& key, int& deletedIndex) {
    if (root == nullptr) {
        return nullptr;
    }

    if (key < root->key) {
        root->left = deleteFromBrandTree(root->left, key, deletedIndex);
    }
    else if (key > root->key) {
        root->right = deleteFromBrandTree(root->right, key, deletedIndex);
    }
    else {
        // Узел найден
        deletedIndex = root->index; 

        // Узел с одним потомком или без
        if (root->left == nullptr) {
            BrandTreeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            BrandTreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // Узел с двумя потомками
        BrandTreeNode* temp = root->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }

        root->key = temp->key;
        root->index = temp->index;

        // Удаляем минимальный элемент
        root->right = deleteFromBrandTree(root->right, temp->key, deletedIndex);
    }

    return root;
}

// Удаление узла из дерева
StringsTreeNode* deleteFromStringsTree(StringsTreeNode* root, int key, int& deletedIndex) {
    if (root == nullptr) {
        return nullptr;
    }

    if (key < root->key) {
        root->left = deleteFromStringsTree(root->left, key, deletedIndex);
    }
    else if (key > root->key) {
        root->right = deleteFromStringsTree(root->right, key, deletedIndex);
    }
    else {
        // Узел найден
        deletedIndex = root->index; 

        // Узел с одним потомком или без
        if (root->left == nullptr) {
            StringsTreeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            StringsTreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // Узел с двумя потомками
        StringsTreeNode* temp = root->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }

        root->key = temp->key;
        root->index = temp->index;

        // Удаляем минимальный элемент
        root->right = deleteFromStringsTree(root->right, temp->key, deletedIndex);
    }

    return root;
}


// Обновление индексов для производителя
void updateBrandTreeIndices(BrandTreeNode* root, int deletedIndex) {
    if (root == nullptr) {
        return;
    }

    if (root->index > deletedIndex) {
        root->index--;
    }

    updateBrandTreeIndices(root->left, deletedIndex);
    updateBrandTreeIndices(root->right, deletedIndex);
}

// Обновление индексов для кол-ва струн
void updateStringsTreeIndices(StringsTreeNode* root, int deletedIndex) {
    if (root == nullptr) {
        return;
    }

    if (root->index > deletedIndex) {
        root->index--;
    }

    updateStringsTreeIndices(root->left, deletedIndex);
    updateStringsTreeIndices(root->right, deletedIndex);
}


// Функция удаления, связываюшая все предыдущие для производителя
void deleteByBrand(Guitar*& guitars, int& n, BrandTreeNode*& brandTree, StringsTreeNode*& stringsTree, const string& targetBrand) {
    int deletedIndex = -1;

    // Удаляем узел из дерева по brand
    brandTree = deleteFromBrandTree(brandTree, targetBrand, deletedIndex);

    if (deletedIndex == -1) {
        cout << "Гитара с производителем '" << targetBrand << "' не найдена.\n";
        return;
    }

    // Удаляем элемент из массива
    deleteFromArray(guitars, n, deletedIndex);

    // Обновляем индексы в обоих деревьях
    updateBrandTreeIndices(brandTree, deletedIndex);
    updateStringsTreeIndices(stringsTree, deletedIndex);

    cout << "Гитара с производителем '" << targetBrand << "' успешно удалена.\n";
}

// Функция удаления, связываюшая все предыдущие для кол-ва струн
void deleteByStrings(Guitar*& guitars, int& n, BrandTreeNode*& brandTree, StringsTreeNode*& stringsTree, int targetStrings) {
    int deletedIndex = -1;

    // Удаляем узел из дерева по strings
    stringsTree = deleteFromStringsTree(stringsTree, targetStrings, deletedIndex);

    if (deletedIndex == -1) {
        cout << "Гитара с количеством струн '" << targetStrings << "' не найдена.\n";
        return;
    }

    // Удаляем элемент из массива
    deleteFromArray(guitars, n, deletedIndex);

    // Обновляем индексы в обоих деревьях
    updateBrandTreeIndices(brandTree, deletedIndex);
    updateStringsTreeIndices(stringsTree, deletedIndex);

    cout << "Гитара с количеством струн '" << targetStrings << "' успешно удалена.\n";
}

// Часть 3

// Функция для вставки элемента в список 
void insertSorted(Node*& head, const Guitar& guitar) {
    Node* newNode = new Node(guitar);

    // Если список пуст или новый элемент должен быть первым
    if (head == nullptr ||
        (guitar.brand < head->data.brand) ||
        (guitar.brand == head->data.brand && guitar.strings > head->data.strings)) {
        newNode->next = head;
        head = newNode;
    }
    else {
        Node* current = head;
        // Поиск места для вставки
        while (current->next != nullptr &&
            (current->next->data.brand < guitar.brand ||
                (current->next->data.brand == guitar.brand && current->next->data.strings >= guitar.strings))) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Функция для добавления новой записи
void addNewRecord(Node*& head) {
    char choice;
    do {
        inputAndInsert(head);
        cout << "Хотите добавить еще одну гитару? (da/net): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'da');
}

// Функция ввода данных и добавления в список 
void inputAndInsert(Node*& head) {
    Guitar guitar;
    cout << "Введите данные о гитаре:\n";
    cout << "Производитель: ";
    getline(cin, guitar.brand);
    cout << "Модель: ";
    getline(cin, guitar.model);
    cout << "Количество струн: ";
    cin >> guitar.strings;
    cout << "Количество ладов: ";
    cin >> guitar.frets;
    cin.ignore();
    cout << "Материал грифа: ";
    getline(cin, guitar.material);
    cout << "Форма: ";
    getline(cin, guitar.shape);

    insertSorted(head, guitar);
}


// функция вывода списка по возрастанию производителя и убыванию струн
void printListAscending(const Node* head) {
    cout << "Список гитар по возрастанию производителя и убыванию струн:\n";
    const Node* current = head;
    while (current != nullptr) {
        const Guitar& guitar = current->data;
        cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
            << left << guitar.strings << " струн| "
            << left << guitar.frets << " ладов| "
            << setw(15) << guitar.material << "| "
            << guitar.shape << "\n\n";
        current = current->next;
    }
}

// функция вывода списка по убыванию производителя и возрастанию струн
void printListDescending(const Node* head) {
    cout << "Список гитар по убыванию производителя и возрастанию струн:\n";
    // Создаем временный список в обратном порядке
    Node* reversedList = nullptr;
    const Node* current = head;
    while (current != nullptr) {
        Node* newNode = new Node(current->data);
        newNode->next = reversedList;
        reversedList = newNode;
        current = current->next;
    }

    // Выводим временный список
    current = reversedList;
    while (current != nullptr) {
        const Guitar& guitar = current->data;
        cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
            << left << guitar.strings << " струн| "
            << left << guitar.frets << " ладов| "
            << setw(15) << guitar.material << "| "
            << guitar.shape << "\n\n";
        current = current->next;
    }

    // Освобождаем память временного списка
    while (reversedList != nullptr) {
        Node* temp = reversedList;
        reversedList = reversedList->next;
        delete temp;
    }
}

// Функция поиска значений по производителю
void searchByBrand(const Node* head, const string& targetBrand) {
    const Node* current = head;
    bool found = false;

    cout << "Результаты поиска по производителю '" << targetBrand << "':\n";
    while (current != nullptr) {
        if (current->data.brand == targetBrand) {
            const Guitar& guitar = current->data;
            cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
                << left << guitar.strings << " струн| "
                << left << guitar.frets << " ладов| "
                << setw(15) << guitar.material << "| "
                << guitar.shape << "\n\n";
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Гитары с производителем '" << targetBrand << "' не найдены.\n";
    }
}

// Функция поиска значений по кол-ву струн
void searchByStrings(const Node* head, int targetStrings) {
    const Node* current = head;
    bool found = false;

    cout << "Результаты поиска по количеству струн '" << targetStrings << "':\n";
    while (current != nullptr) {
        if (current->data.strings == targetStrings) {
            const Guitar& guitar = current->data;
            cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
                << left << guitar.strings << " струн| "
                << left << guitar.frets << " ладов| "
                << setw(15) << guitar.material << "| "
                << guitar.shape << "\n\n";
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Гитары с количеством струн '" << targetStrings << "' не найдены.\n";
    }
}

// Функция удаления по производителю
void deleteByBrand(Node*& head, const string& targetBrand) {
    Node* current = head;
    Node* prev = nullptr;
    bool found = false;

    while (current != nullptr) {
        if (current->data.brand == targetBrand) {
            found = true;
            if (prev == nullptr) {
                // Удаляем голову списка
                head = current->next;
                delete current;
                current = head;
            }
            else {
                // Удаляем элемент в середине или конце
                prev->next = current->next;
                delete current;
                current = prev->next;
            }
        }
        else {
            prev = current;
            current = current->next;
        }
    }

    if (found) {
        cout << "Гитары с производителем '" << targetBrand << "' успешно удалены.\n";
    }
    else {
        cout << "Гитары с производителем '" << targetBrand << "' не найдены.\n";
    }
}

// Функция удаления по кол-ву струн
void deleteByStrings(Node*& head, int targetStrings) {
    Node* current = head;
    Node* prev = nullptr;
    bool found = false;

    while (current != nullptr) {
        if (current->data.strings == targetStrings) {
            found = true;
            if (prev == nullptr) {
                // Удаляем голову списка
                head = current->next;
                delete current;
                current = head;
            }
            else {
                // Удаляем элемент в середине или конце
                prev->next = current->next;
                delete current;
                current = prev->next;
            }
        }
        else {
            prev = current;
            current = current->next;
        }
    }

    if (found) {
        cout << "Гитары с количеством струн '" << targetStrings << "' успешно удалены.\n";
    }
    else {
        cout << "Гитары с количеством струн '" << targetStrings << "' не найдены.\n";
    }
}


int main() {
    setlocale(LC_ALL, "Russian");

    int n = 1;
    Guitar* guitars = new Guitar[n]{
        {"IBANEZ", "GRG121", 6, 24, "Клен", "Modernstrat"},
        {"IBANEZ", "RG421", 6, 24, "Клен", "Superstrat"},
        {"FENDER", "SQUIER AFFINITY", 6, 21, "Клен", "Telecaster"},
        {"CORT", "CR250", 6, 22, "Красное дерево", "Les Paul"},
        {"JACKSON", "JS22Q", 7, 24, "Клен", "Superstrat"},
        {"JACKSON", "JS32", 8, 24, "Клен", "Superstrat"},
        {"VESTON", "EFV", 6, 24, "Клен", "Flying-V"},
        {"SOLAR", "E26C", 6, 22, "Клен", "Explorer"}
    };



    //ЧАСТЬ 1

    Index* brandIndex = new Index[n];
    StringsIndex* stringsIndex = new StringsIndex[n];
    createIndexes(guitars, n, brandIndex, stringsIndex);

    //printGuitars(guitars, n);
    //printSortedGuitars(guitars, n, brandIndex, stringsIndex);

    //// Редактирование записи по производителю
    //string targetBrand;
    //cout << "\nВведите производителя гитары для редактирования: ";
    //getline(cin, targetBrand);

    //int count = printGuitarsByBrand(guitars, brandIndex, n, targetBrand);

    //if (count == 1) {
    //    for (int i = 0; i < n; i++) {
    //        if (brandIndex[i].value == targetBrand) {
    //            editGuitar(guitars, n, brandIndex, stringsIndex, brandIndex[i].index);
    //            break;
    //        }
    //    }
    //    cout << "\nОбновленный список гитар:\n";
    //    printGuitars(guitars, n);
    //    printSortedGuitars(guitars, n, brandIndex, stringsIndex);
    //}
    //else if (count > 1) {
    //    int index = selectGuitarIndex(n);
    //    if (index != -1) {
    //        editGuitar(guitars, n, brandIndex, stringsIndex, index);
    //    }
    //    cout << "\nОбновленный список гитар:\n";
    //    printGuitars(guitars, n);
    //    printSortedGuitars(guitars, n, brandIndex, stringsIndex);
    //}

    //// Удаление записи по производителю
    //cout << "\nВведите производителя гитары для удаления: ";
    //getline(cin, targetBrand);

    //deleteGuitarByBrand(guitars, n, brandIndex, stringsIndex, targetBrand);

    //cout << "\nОбновленный список гитар:\n";
    //printGuitars(guitars, n);
    //printSortedGuitars(guitars, n, brandIndex, stringsIndex);

    //// Удаление записи по количеству струн
    //int targetStrings;
    //cout << "\nВведите количество струн для удаления: ";
    //cin >> targetStrings;

    //deleteGuitarByStrings(guitars, n, brandIndex, stringsIndex, targetStrings);

    //cout << "\nОбновленный список гитар:\n";
    //printGuitars(guitars, n);
    //printSortedGuitars(guitars, n, brandIndex, stringsIndex);

    //delete[] guitars;
    //delete[] brandIndex;
    //delete[] stringsIndex;


    //ЧАСТЬ 2

    //// Создание бинарного дерева по атрибуту производителю
    //BrandTreeNode* brandTree = nullptr;
    //StringsTreeNode* stringsTree = nullptr;
    //for (int i = 0; i < n; i++) {
    //    brandTree = insertBrand(brandTree, guitars[i].brand, i);
    //    stringsTree = insertStrings(stringsTree, guitars[i].strings, i);
    //}

    //cout << "Гитары, отсортированные по производителю по убыванию:\n";
    //unOrderPassBrand(brandTree, guitars);

    //cout << "Гитары, отсортированные по количеству струн по убыванию:\n";
    //unOrderPassStrings(stringsTree, guitars);

    //// Поиск гитары по производителю
    //string targetBrand;
    //cout << "\nВведите производителя для поиска: ";
    //getline(cin, targetBrand);
    //searchByBrand(brandTree, guitars, targetBrand);

    //// Вывод данных до удаления
    //cout << "До удаления:\n";
    //inOrderPassBrand(brandTree, guitars);

    //// Удаление по brand
    //string targetBrand = "JACKSON";
    //deleteByBrand(guitars, n, brandTree, stringsTree, targetBrand);

    //// Вывод данных после удаления по производителю
    //cout << "\nПосле удаления по произвоидителю:\n";
    //inOrderPassBrand(brandTree, guitars);

    //// Удаление по strings
    //int targetStrings = 6;
    //deleteByStrings(guitars, n, brandTree, stringsTree, targetStrings);

    //// Вывод данных после удаления по струнам
    //cout << "\nПосле удаления по кол-ву струн:\n";
    //inOrderPassBrand(brandTree, guitars);


    // Освобождение памяти
    //delete[] guitars;

    //ЧАСТЬ 3

    //Node* head = nullptr;
    //// Добавление записей
    //addNewRecord(head);

    //// Вывод списка по возрастанию
    //printListAscending(head);

    //// Вывод списка по убыванию
    //printListDescending(head);

    //// Поиск по производителю
    //string targetBrand = "IBANEZ";
    //searchByBrand(head, targetBrand);

    //// Поиск по количеству струн
    //int targetStrings = 6;
    //searchByStrings(head, targetStrings);

    //// Удаление по производителю
    //deleteByBrand(head, targetBrand);

    //// Удаление по количеству струн
    //deleteByStrings(head, targetStrings);
}