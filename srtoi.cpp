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
        if (!guitars[i].isDeleted) {
            cout << setw(8) << left << guitars[i].brand << "|" << setw(15) << left << guitars[i].model << "|"
                << left << guitars[i].strings << " струн| "
                << left << guitars[i].frets << " ладов| "
                << setw(15) << guitars[i].material << "| "
                << guitars[i].shape << "\n";
        }
    }
}

// Сортированный вывод
void printSortedGuitars(const Guitar* guitars, int n, const Index* brandIndex, const StringsIndex* stringsIndex) {
    cout << "\nГитары, отсортированные в лексикографическом порядке по возрастанию:\n"; // Для производителя
    for (int i = 0; i < n; i++) {
        const Guitar& guitar = guitars[brandIndex[i].index];
        if (!guitar.isDeleted) {
            cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
                << left << guitar.strings << " струн| "
                << left << guitar.frets << " ладов| "
                << setw(15) << guitar.material << "| "
                << guitar.shape << "\n";
        }
    }
    cout << "------------------------------------------\n";

    cout << "\nГитары, отсортированные по количеству струн по убыванию:\n"; // Для струн
    for (int i = 0; i < n; i++) {
        const Guitar& guitar = guitars[stringsIndex[i].index];
        if (!guitar.isDeleted) {
            cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
                << left << guitar.strings << " струн| "
                << left << guitar.frets << " ладов| "
                << setw(15) << guitar.material << "| "
                << guitar.shape << "\n";
        }
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
        if (!guitar.isDeleted) {
            cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
                << left << guitar.strings << " струн| "
                << left << guitar.frets << " ладов| "
                << setw(15) << guitar.material << "| "
                << guitar.shape << "\n";
        }
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
        if (!guitar.isDeleted) {
            cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
                << left << guitar.strings << " струн| "
                << left << guitar.frets << " ладов| "
                << setw(15) << guitar.material << "| "
                << guitar.shape << "\n";
        }
    }
}


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

    bool brandChanged = (guitar.brand != brand);
    bool stringsChanged = (guitar.strings != strings);

    guitar.brand = brand;
    guitar.model = model;
    guitar.strings = strings;
    guitar.frets = frets;
    guitar.material = material;
    guitar.shape = shape;

    for (int i = 0; i < n; i++) {
        if (brandIndex[i].index == index) {
            brandIndex[i].value = brand;
        }
        if (stringsIndex[i].index == index) {
            stringsIndex[i].value = strings;
        }
    }

    if (brandChanged) {
        // Сортировка brandIndex в лексикографическом порядке по возрастанию
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (brandIndex[j].value > brandIndex[j + 1].value) {
                    Index temp = brandIndex[j];
                    brandIndex[j] = brandIndex[j + 1];
                    brandIndex[j + 1] = temp;
                }
            }
        }
    }

    if (stringsChanged) {
        // Сортировка stringsIndex по убыванию
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (stringsIndex[j].value < stringsIndex[j + 1].value) {
                    StringsIndex temp = stringsIndex[j];
                    stringsIndex[j] = stringsIndex[j + 1];
                    stringsIndex[j + 1] = temp;
                }
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
        if (brandIndex[i].value == targetBrand && !guitars[brandIndex[i].index].isDeleted) {
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
        if (stringsIndex[i].value == targetStrings && !guitars[stringsIndex[i].index].isDeleted) {
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


// Функция для обновления индекс-массивов после удаления
void updateIndexesAfterDeletion(Index* brandIndex, StringsIndex* stringsIndex, int n, int deletedIndex) {
    for (int i = 0; i < n; i++) {
        if (brandIndex[i].index == deletedIndex) {
            brandIndex[i].value = "";
        }
        if (stringsIndex[i].index == deletedIndex) {
            stringsIndex[i].value = -1;
        }
    }
}

void deleteGuitarByBrand(Guitar* guitars, int n, Index* brandIndex, StringsIndex* stringsIndex, const string& targetBrand) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (guitars[i].brand == targetBrand && !guitars[i].isDeleted) {
            count++;
        }
    }

    if (count == 0) {
        cout << "Гитары с производителем '" << targetBrand << "' не найдены.\n";
        return;
    }

    if (count == 1) {
        for (int i = 0; i < n; i++) {
            if (guitars[i].brand == targetBrand && !guitars[i].isDeleted) {
                guitars[i].isDeleted = true;
                cout << "Гитара успешно удалена!\n";
                // Обновляем индекс-массивы
                updateIndexesAfterDeletion(brandIndex, stringsIndex, n, i);
                return;
            }
        }
    }

    cout << "\nГитары с производителем '" << targetBrand << "':\n";
    for (int i = 0; i < n; i++) {
        if (guitars[i].brand == targetBrand && !guitars[i].isDeleted) {
            cout << "Номер: " << i + 1 << " | "
                << setw(8) << left << guitars[i].brand << "|" << setw(15) << left << guitars[i].model << "|"
                << left << guitars[i].strings << " струн| "
                << left << guitars[i].frets << " ладов| "
                << setw(15) << guitars[i].material << "| "
                << guitars[i].shape << "\n";
        }
    }

    int indexToDelete = selectGuitarIndex(n);
    if (indexToDelete == -1) {
        return;
    }

    if (indexToDelete < 0 || indexToDelete >= n) {
        cout << "Некорректный номер!\n";
        return;
    }

    if (guitars[indexToDelete].brand == targetBrand && !guitars[indexToDelete].isDeleted) {
        guitars[indexToDelete].isDeleted = true;
        cout << "Гитара успешно удалена!\n";
        // Обновляем индекс-массивы
        updateIndexesAfterDeletion(brandIndex, stringsIndex, n, indexToDelete);
    }
    else {
        cout << "Некорректный номер!\n";
    }
}

// Удаление гитар по количеству струн
void deleteGuitarByStrings(Guitar* guitars, int n, Index* brandIndex, StringsIndex* stringsIndex, int targetStrings) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (guitars[i].strings == targetStrings && !guitars[i].isDeleted) {
            count++;
        }
    }

    if (count == 0) {
        cout << "Гитары с количеством струн '" << targetStrings << "' не найдены.\n";
        return;
    }

    if (count == 1) {
        for (int i = 0; i < n; i++) {
            if (guitars[i].strings == targetStrings && !guitars[i].isDeleted) {
                guitars[i].isDeleted = true;
                cout << "Гитара успешно удалена!\n";
                // Обновляем индекс-массивы
                updateIndexesAfterDeletion(brandIndex, stringsIndex, n, i);
                return;
            }
        }
    }

    cout << "\nГитары с количеством струн '" << targetStrings << "':\n";
    for (int i = 0; i < n; i++) {
        if (guitars[i].strings == targetStrings && !guitars[i].isDeleted) {
            cout << "Номер: " << i + 1 << " | "
                << setw(8) << left << guitars[i].brand << "|" << setw(15) << left << guitars[i].model << "|"
                << left << guitars[i].strings << " струн| "
                << left << guitars[i].frets << " ладов| "
                << setw(15) << guitars[i].material << "| "
                << guitars[i].shape << "\n";
        }
    }

    int indexToDelete = selectGuitarIndex(n);
    if (indexToDelete == -1) {
        return;
    }

    if (indexToDelete < 0 || indexToDelete >= n) {
        cout << "Некорректный номер!\n";
        return;
    }

    if (guitars[indexToDelete].strings == targetStrings && !guitars[indexToDelete].isDeleted) {
        guitars[indexToDelete].isDeleted = true;
        cout << "Гитара успешно удалена!\n";
        // Обновляем индекс-массивы
        updateIndexesAfterDeletion(brandIndex, stringsIndex, n, indexToDelete);
    }
    else {
        cout << "Некорректный номер!\n";
    }
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
        << guitar.shape << "\n";
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
        << guitar.shape << "\n";
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


// Функция рекурсивного поиска по ключу для производителя
void treeBinarySearchByBrand(BrandTreeNode* root, const Guitar* guitars, const string& key) {
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
        treeBinarySearchByBrand(root->left, guitars, key);
    }
    else {
        treeBinarySearchByBrand(root->right, guitars, key);
    }
}

// Функция рекурсивного поиска по ключу для кол-ва струн
void treeBinarySearchByStrings(StringsTreeNode* root, const Guitar* guitars, int key) {
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
        treeBinarySearchByStrings(root->left, guitars, key);
    }
    else {
        treeBinarySearchByStrings(root->right, guitars, key);
    }
}

// Функция итерационного поиска по ключу для производителя
void treeIterativeSearchByBrand(BrandTreeNode* root, const Guitar* guitars, const string& key) {
    BrandTreeNode* current = root;
    bool found = false; 

    while (current != nullptr) {
        if (current->key == key) {
            const Guitar& guitar = guitars[current->index];
            cout << "Найдена гитара:\n";
            cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
                << left << guitar.strings << " струн| "
                << left << guitar.frets << " ладов| "
                << setw(15) << guitar.material << "| "
                << guitar.shape << "\n\n";
            found = true; 
        }

        if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    if (!found) {
        cout << "Гитара с производителем '" << key << "' не найдена.\n";
    }
}


// Функция итерационного поиска по ключу для струн
void treeIterativeSearchByStrings(StringsTreeNode* root, const Guitar* guitars, int key) {
    StringsTreeNode* current = root;
    bool found = false; 

    while (current != nullptr) {
        if (current->key == key) {
            const Guitar& guitar = guitars[current->index];
            cout << "Найдена гитара:\n";
            cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
                << left << guitar.strings << " струн| "
                << left << guitar.frets << " ладов| "
                << setw(15) << guitar.material << "| "
                << guitar.shape << "\n\n";
            found = true; 
        }

        if (key < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    if (!found) {
        cout << "Гитара с количеством струн '" << key << "' не найдена.\n";
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

// Удаление узла из дерева для производителя
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

// Удаление узла из дерева для кол-ва струн
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


// Балансировка 


// Преобразование дерева в односвязный список для производителя
BrandTreeNode* treeToList(BrandTreeNode* root, BrandTreeNode*& prev) {
    if (root == nullptr) return nullptr;

    treeToList(root->left, prev);

    root->left = prev;
    if (prev != nullptr) {
        prev->right = root;
    }
    prev = root;

    treeToList(root->right, prev);

    return root;
}

// Построение сбалансированного дерева из односвязного списка для производителя
BrandTreeNode* listToTree(BrandTreeNode*& head, int start, int end) {
    if (start > end || head == nullptr) return nullptr;

    int mid = (start + end) / 2;

    BrandTreeNode* leftChild = listToTree(head, start, mid - 1);

    BrandTreeNode* root = head;
    root->left = leftChild;

    head = head->right;

    root->right = listToTree(head, mid + 1, end);

    return root;
}

// Основная функция для балансировки дерева для производителя
BrandTreeNode* balanceBrandTree(BrandTreeNode* root) {
    if (root == nullptr) return nullptr;

    BrandTreeNode* prev = nullptr;
    treeToList(root, prev);

    BrandTreeNode* head = root;
    while (head->left != nullptr) {
        head = head->left;
    }

    int count = 0;
    BrandTreeNode* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->right;
    }

    return listToTree(head, 0, count - 1);
}

// Преобразование дерева в односвязный список для струн
StringsTreeNode* treeToList(StringsTreeNode* root, StringsTreeNode*& prev) {
    if (root == nullptr) return nullptr;

    treeToList(root->left, prev);

    root->left = prev;
    if (prev != nullptr) {
        prev->right = root;
    }
    prev = root;

    treeToList(root->right, prev);

    return root;
}

// Построение сбалансированного дерева из односвязного списка для струн
StringsTreeNode* listToTree(StringsTreeNode*& head, int start, int end) {
    if (start > end || head == nullptr) return nullptr;

    int mid = (start + end) / 2;

    StringsTreeNode* leftChild = listToTree(head, start, mid - 1);

    StringsTreeNode* root = head;
    root->left = leftChild;

    head = head->right;

    // Рекурсивно строим правое поддерево
    root->right = listToTree(head, mid + 1, end);

    return root;
}

// Основная функция для балансировки дерева для струн
StringsTreeNode* balanceStringsTree(StringsTreeNode* root) {
    if (root == nullptr) return nullptr;

    StringsTreeNode* prev = nullptr;
    treeToList(root, prev);

    StringsTreeNode* head = root;
    while (head->left != nullptr) {
        head = head->left;
    }

    int count = 0;
    StringsTreeNode* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->right;
    }

    return listToTree(head, 0, count - 1);
}


// Демонстрация работы билансировки
int getHeightBrand(BrandTreeNode* root) {
    if (root == nullptr) return 0;
    return 1 + max(getHeightBrand(root->left), getHeightBrand(root->right));
}

// Демонстрация работы билансировки
int getHeightStrings(StringsTreeNode* root) {
    if (root == nullptr) return 0;
    return 1 + max(getHeightStrings(root->left), getHeightStrings(root->right));
}

// Часть 3


struct Node {
    Guitar data;    // Данные 
    Node* next;     // Указатель на следующий элемент

    Node(const Guitar& g) : data(g), next(nullptr) {}
};

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

// Функция для добавления новой записи
void addNewRecord(Node*& head) {
    string choice;
    do {
        inputAndInsert(head);
        cout << "Хотите добавить еще одну гитару? (da/net): ";
        cin >> choice;
    } while (choice == "da");
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
            << guitar.shape << "\n";
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
            << guitar.shape << "\n";
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
void iterativeSearchByBrand3(const Node* head, const string& targetBrand) {
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
                << guitar.shape << "\n";
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Гитары с производителем '" << targetBrand << "' не найдены.\n";
    }
}

// Функция итерационного поиска значений по кол-ву струн
void iterativeSearchByStrings3(const Node* head, int targetStrings) {
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
                << guitar.shape << "\n";
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Гитары с количеством струн '" << targetStrings << "' не найдены.\n";
    }
}

// Функция рекурсивного поиска значений по производителю
void recursiveSearchByBrand3(const Node* head, const string& targetBrand) {
    static bool found = false; 


    if (head == nullptr) {
        if (!found) {
            cout << "Гитары с производителем '" << targetBrand << "' не найдены.\n";
        }
        found = false; 
        return;
    }


    if (head->data.brand == targetBrand) {
        const Guitar& guitar = head->data;
        cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
            << left << guitar.strings << " струн| "
            << left << guitar.frets << " ладов| "
            << setw(15) << guitar.material << "| "
            << guitar.shape << "\n";
        found = true; 
    }

    // Рекурсивный вызов для следующего элемента
    recursiveSearchByBrand3(head->next, targetBrand);
}


// Функция рекурсивного поиска значений по кол-ву струн
void recursiveSearchByStrings3(const Node* head, int targetStrings) {
    static bool found = false; // Локальный статический флаг

    // Базовый случай: если список пуст
    if (head == nullptr) {
        if (!found) {
            cout << "Гитары с количеством струн '" << targetStrings << "' не найдены.\n";
        }
        found = false; // Сбрасываем флаг для следующих вызовов
        return;
    }

    // Если текущий элемент соответствует критерию
    if (head->data.strings == targetStrings) {
        const Guitar& guitar = head->data;
        cout << setw(8) << left << guitar.brand << "|" << setw(15) << left << guitar.model << "|"
            << left << guitar.strings << " струн| "
            << left << guitar.frets << " ладов| "
            << setw(15) << guitar.material << "| "
            << guitar.shape << "\n";
        found = true; // Устанавливаем флаг, что найден хотя бы один элемент
    }

    // Рекурсивный вызов для следующего элемента
    recursiveSearchByStrings3(head->next, targetStrings);
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



    //ЧАСТЬ 1

    Index* brandIndex = new Index[n];
    StringsIndex* stringsIndex = new StringsIndex[n];
    createIndexes(guitars, n, brandIndex, stringsIndex);

    printGuitars(guitars, n);
    /*printSortedGuitars(guitars, n, brandIndex, stringsIndex);
    searchByBrandRecursive(guitars, n, brandIndex, "F");
    searchByStringsIterative(guitars, n, stringsIndex, 1);*/
    // Редактирование записи по производителю
    /*int targetStrings;
    cout << "\nВведите кол-во струн гитары для редактирования: ";
    cin >> targetStrings;

    int count = printGuitarsByStrings(guitars, stringsIndex, n, targetStrings);

    if (count == 1) {
        for (int i = 0; i < n; i++) {
            if (stringsIndex[i].value == targetStrings) {
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
    }*/

    // Удаление записи по производителю
    //string targetBrand;
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

    // Создание бинарного дерева по атрибут
    BrandTreeNode* brandTree = nullptr;
    StringsTreeNode* stringsTree = nullptr;
    for (int i = 0; i < n; i++) {
        brandTree = insertBrand(brandTree, guitars[i].brand, i);
        stringsTree = insertStrings(stringsTree, guitars[i].strings, i);
    }

    //cout << "Гитары, отсортированные по производителю по возрастанию:\n";
    //inOrderPassBrand(brandTree, guitars);

    /*cout << "Балансировка для производителя:\n";
    int heightBefore = getHeightBrand(brandTree);
    cout << "Высота дерева до балансировки: " << heightBefore << "\n";

    brandTree = balanceBrandTree(brandTree);

    int heightAfter = getHeightBrand(brandTree);
    cout << "Высота дерева после балансировки: " << heightAfter << "\n";*/


    /*cout << "Балансировка для кол-ва струн:\n";
    int heightBefore2 = getHeightStrings(stringsTree);
    cout << "Высота дерева до балансировки: " << heightBefore2 << "\n";

    stringsTree = balanceStringsTree(stringsTree);

    int heightAfter2 = getHeightStrings(stringsTree);
    cout << "Высота дерева после балансировки: " << heightAfter2 << "\n";*/

    //cout << "Гитары, отсортированные по количеству струн по возрастанию:\n";
    //inOrderPassStrings(stringsTree, guitars);

    //cout << "Гитары, отсортированные по производителю по убыванию:\n";
    //unOrderPassBrand(brandTree, guitars);

    //cout << "Гитары, отсортированные по количеству струн по убыванию:\n";
    //unOrderPassStrings(stringsTree, guitars);

    // Поиск гитары по производителю
    //string targetBrand;
    //cout << "\nВведите производителя для поиска: ";
    //getline(cin, targetBrand);
    //treeBinarySearchByBrand(brandTree, guitars, targetBrand);
    //treeIterativeSearchByBrand(brandTree, guitars, targetBrand);

    // Поиск гитары по ключу
    //int targetStrings;
    //cout << "\nВведите кол-во струн для поиска: ";
    //cin >> targetStrings;
    //treeBinarySearchByStrings(stringsTree, guitars, targetStrings);
    //treeIterativeSearchByStrings(stringsTree, guitars, targetStrings);

    //// Вывод данных до удаления
    //cout << "До удаления:\n";
    //inOrderPassBrand(brandTree, guitars);

    ////Удаление по brand
    //string targetBrand;
    //cout << "\nВведите производителя для удаления: ";
    //getline(cin, targetBrand);
    //deleteByBrand(guitars, n, brandTree, stringsTree, targetBrand);

    //// Вывод данных после удаления по производителю
    //cout << "\nПосле удаления по производителю:\n";
    //inOrderPassBrand(brandTree, guitars);


    //// Удаление по strings
    //int targetStrings;
    //cin >> targetStrings;
    //deleteByStrings(guitars, n, brandTree, stringsTree, targetStrings);

    //// Вывод данных после удаления по струнам
    //cout << "\nПосле удаления по кол-ву струн:\n";
    //inOrderPassStrings(stringsTree, guitars);


    //// Освобождение памяти
    //delete[] guitars;

    ////ЧАСТЬ 3
    //printGuitars(guitars, n);
    //Node* head = nullptr;
    //for (int i = 0; i < n; i++) {
    //    insertSorted(head, guitars[i]);
    //}
    //// Добавление записей
    //addNewRecord(head);

    //// Вывод списка по возрастанию
    //printListAscending(head);

    //// Вывод списка по убыванию
    //printListDescending(head);

    // Поиск по производителю
    //string targetBrand = "IBAN2Z";
    //searchByBrand(head, targetBrand);
    //cout << "Гитара по бренду:\n";
    //recursiveSearchByBrand3(head, targetBrand);

    // Поиск по количеству струн
    //int targetStrings = 1;
    //searchByStrings(head, targetStrings);
    /*cout << "Гитара по струнам:\n";
    recursiveSearchByStrings3(head, targetStrings);*/

    //// Удаление по производителю
    //deleteByBrand(head, targetBrand);

    //// Удаление по количеству струн
    //deleteByStrings(head, targetStrings);
    //printListDescending(head);
}