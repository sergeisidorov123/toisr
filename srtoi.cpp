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


// Обход дерева по возрастанию
void inOrderPass(BrandTreeNode* root, const Guitar* guitars) {
    if (root == nullptr) return;

    inOrderPass(root->left, guitars);
    const Guitar& guitar = guitars[root->index];
    cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
        << left << guitar.strings << " струн| "
        << left << guitar.frets << " ладов| "
        << setw(15) << guitar.material << "| "
        << guitar.shape << "\n\n";
    inOrderPass(root->right, guitars);
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
        << guitar.shape << "\n\n";
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
        << guitar.shape << "\n\n";
    unOrderPassStrings(root->left, guitars);
}


// Функция поиска по ключу
void searchByKey(TreeNode* root, const Guitar* guitars, const string& key) {
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
        searchByKey(root->left, guitars, key);
    }
    else {
        searchByKey(root->right, guitars, key);
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
TreeNode* deleteFromTree(TreeNode* root, const string& key, int& deletedIndex) 

{
    //Узел не найден
    if (root == nullptr) { 
        return nullptr;
    }

    if (key < root->key) {
        root->left = deleteFromTree(root->left, key, deletedIndex);
    }
    else if (key > root->key) {
        root->right = deleteFromTree(root->right, key, deletedIndex);
    }
    else {
        // Узел найден
        deletedIndex = root->index; // Сохранение индекса 

        // Узел с одним потомком или без 
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // Узел с двумя потомками
        // Находим минимальный элемент в правом поддереве
        TreeNode* temp = root->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }

        // Копируем данные минимального элемента в текущий узел
        root->key = temp->key;
        root->index = temp->index;

        // Удаляем минимальный элемент
        root->right = deleteFromTree(root->right, temp->key, deletedIndex);
    }

    return root;
}


// Обновление индексов 
void updateTreeIndices(TreeNode* root, int deletedIndex) {
    if (root == nullptr) {
        return;
    }

    // Если индекс узла больше удаленного, уменьшаем его на 1
    if (root->index > deletedIndex) {
        root->index--;
    }

    // Рекурсивно обновляем индексы в левом и правом поддеревьях
    updateTreeIndices(root->left, deletedIndex);
    updateTreeIndices(root->right, deletedIndex);
}


// Функция удаления, связываюшая все предыдущие
void Delete(Guitar*& guitars, int& n, TreeNode*& root, const string& key) {
    int deletedIndex = -1;

    // Удаляем узел из дерева и получаем индекс удаляемого элемента
    root = deleteFromTree(root, key, deletedIndex);

    if (deletedIndex == -1) {
        cout << "Гитара с производителем '" << key << "' не найдена.\n";
        return;
    }

    // Удаление элемента
    deleteFromArray(guitars, n, deletedIndex);

    // Обновление индексов
    updateTreeIndices(root, deletedIndex);

    cout << "Гитара с производителем '" << key << "' успешно удалена.\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int n = 8;
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

    Index* brandIndex = new Index[n];
    StringsIndex* stringsIndex = new StringsIndex[n];

    createIndexes(guitars, n, brandIndex, stringsIndex);

    printGuitars(guitars, n);
    printSortedGuitars(guitars, n, brandIndex, stringsIndex);

    // Редактирование записи по производителю
    string targetBrand;
    cout << "\nВведите производителя гитары для редактирования: ";
    getline(cin, targetBrand);

    int count = printGuitarsByBrand(guitars, brandIndex, n, targetBrand);

    if (count == 1) {
        for (int i = 0; i < n; i++) {
            if (brandIndex[i].value == targetBrand) {
                editGuitar(guitars, n, brandIndex, stringsIndex, brandIndex[i].index);
                break;
            }
        }
        cout << "\nОбновленный список гитар:\n";
        printGuitars(guitars, n);
        printSortedGuitars(guitars, n, brandIndex, stringsIndex);
    }
    else if (count > 1) {
        int index = selectGuitarIndex(n);
        if (index != -1) {
            editGuitar(guitars, n, brandIndex, stringsIndex, index);
        }
        cout << "\nОбновленный список гитар:\n";
        printGuitars(guitars, n);
        printSortedGuitars(guitars, n, brandIndex, stringsIndex);
    }

    // Удаление записи по производителю
    cout << "\nВведите производителя гитары для удаления: ";
    getline(cin, targetBrand);

    deleteGuitarByBrand(guitars, n, brandIndex, stringsIndex, targetBrand);

    cout << "\nОбновленный список гитар:\n";
    printGuitars(guitars, n);
    printSortedGuitars(guitars, n, brandIndex, stringsIndex);

    // Удаление записи по количеству струн
    int targetStrings;
    cout << "\nВведите количество струн для удаления: ";
    cin >> targetStrings;

    deleteGuitarByStrings(guitars, n, brandIndex, stringsIndex, targetStrings);

    cout << "\nОбновленный список гитар:\n";
    printGuitars(guitars, n);
    printSortedGuitars(guitars, n, brandIndex, stringsIndex);

    delete[] guitars;
    delete[] brandIndex;
    delete[] stringsIndex;


    //ЧАСТЬ 2

    // Создание бинарного дерева по атрибуту производителю
    TreeNode* brandTree = nullptr;
    for (int i = 0; i < n; i++) {
        brandTree = insert(brandTree, guitars[i].brand, i);
    }

    // Вывод данных по возрастанию
    cout << "\nГитары, отсортированные по производителю (по возрастанию):\n";
    inOrderPass(brandTree, guitars);

    // Вывод данных по убыванию
    cout << "\nГитары, отсортированные по производителю (по убыванию):\n";
    unOrderPass(brandTree, guitars);

    // Поиск гитары по производителю
    string targetBrand;
    cout << "\nВведите производителя для поиска: ";
    getline(cin, targetBrand);
    searchByKey(brandTree, guitars, targetBrand);

    // Удаление записи
    string targetBrand;
    cout << "\nВведите производителя для удаления: ";
    getline(cin, targetBrand);
    Delete(guitars, n, brandTree, targetBrand);

    // Вывод данных после удаления
    cout << "\nПосле удаления:\n";
    unOrderPass(brandTree, guitars);

    // Освобождение памяти
    delete[] guitars;

    // Освобождение памяти
    delete[] guitars;
}