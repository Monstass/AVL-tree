#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <windows.h>

using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;

/*
    Структура дерева
 */
struct avl_node
{
    int key;
    int bulding_year;
    int number_of_rooms;
    double price;
    double total_area;
    double living_area;
    string district;
    string addres;
    struct avl_node* left;
    struct avl_node* right;
}*root;

/*
     Класс дерева
 */
class avlTree
{
public:
    avlTree()
    {
        root = nullptr;
    }
    int height(avl_node*);
    int diff(avl_node*);
    int find_way(avl_node*, int, int);
    avl_node* rr_rotation(avl_node*);
    avl_node* ll_rotation(avl_node*);
    avl_node* lr_rotation(avl_node*);
    avl_node* rl_rotation(avl_node*);
    avl_node* balance(avl_node*);
    avl_node* insert(avl_node*, int, int, int, double,double, 
        double, string, string);
    avl_node* remove(avl_node*, int);
    avl_node* removemin(avl_node*);
    avl_node* findmin(avl_node*);
    void display(avl_node*, int);
    void inorder(avl_node*);
    void show_data(avl_node* ptr, double);
    ~avlTree() 
    {
        delete root;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int key, choice;
    int bulding_year;
    int number_of_rooms;
    double price;
    double total_area;
    double living_area;
    string district;
    string addres;
    int s = 0;
    avlTree tree;

    do
    {
        cout << "\t\t::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
        cout << "\t\t::::1 Вставить новый элемент::::::::::::::::::::" << endl;
        cout << "\t\t::::2 Удалить элемент:::::::::::::::::::::::::::" << endl;
        cout << "\t\t::::3 Вывод дерева на экран:::::::::::::::::::::" << endl;
        cout << "\t\t::::4 Симметричный обход::::::::::::::::::::::::" << endl;
        cout << "\t\t::::5 Высота дерева:::::::::::::::::::::::::::::" << endl;
        cout << "\t\t::::6 Вывод содержимого:::::::::::::::::::::::::" << endl;
        cout << "\t\t::::7 Нахождение длины пути:::::::::::::::::::::" << endl;
        cout << "\t\t::::0 Выход:::::::::::::::::::::::::::::::::::::" << endl;
        cout << "\t\t::::::::::::::::::::::::::::::::::::::::::::::::\n" << endl;

        cout << "\nВыберите нужное действие и нажмите Enter: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Добавление нового элемента" << endl;
            cout << "Введите элемент: ";
            cin >> key;
            cout << "Введите район: ";
            std::getline(cin >> std::ws, district);
            cout << "Введите адрес: ";
            std::getline(cin, addres);
            while (1)
            {
                cout << "Введите количество комнат: ";
                cin >> number_of_rooms;
                if (number_of_rooms > 0)
                {
                    break;
                }
                else
                {
                    cin.clear();
                    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                    cout << "Ошибка ввода" << endl;
                }
            }
            while (1)
            {
                cout << "Введите общую площадь: ";
                cin >> total_area;
                if (total_area > 0)
                {
                    break;
                }
                else
                {
                    cin.clear();
                    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                    cout << "Ошибка ввода" << endl;
                }
            }
            while (1)
            {
                cout << "Введите жилую площадь: ";
                cin >> living_area;
                if (living_area > 0)
                {
                    break;
                }
                else
                {
                    cin.clear();
                    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                    cout << "Ошибка ввода" << endl;
                }
            }
            while (1)
            {
                cout << "Введите год постройки дома: ";
                cin >> bulding_year;
                if (bulding_year > 0)
                {
                    break;
                }
                else
                {
                    cin.clear();
                    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                    cout << "Ошибка ввода" << endl;
                }
            }
            while (1)
            {
                cout << "Введите стоимость: ";
                cin >> price;
                if (price > 0)
                {
                    break;
                }
                else
                {
                    cin.clear();
                    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                    cout << "Ошибка ввода";
                }
            }
            root = tree.insert(root, key, bulding_year, 
                number_of_rooms, price, total_area, living_area, 
                district, addres);
            cout << "Новый элемент добавлен успешно\n" << endl;
            break;
        case 2:
            cout << "Удаление элемента" << endl;
            cout << "Введите элемент: ";
            cin >> key;
            tree.remove(root, key);

            break;
        case 3:
            tree.display(root, 1);

            break;
        case 4:
            tree.inorder(root);

            break;
        case 5:
            cout << "Высота дерева: " << tree.height(root) - 1;

            break;
        case 6:
            double _price;
            while (1)
            {
                cout << "Введите стоимость жилья для получения"
                    " подробной информации: ";
                cin >> _price;
                if (_price > 0)
                {
                    break;
                }
                else
                {
                    cout << "Ошибка ввода" << endl;
                }
            }
            tree.show_data(root, _price);
            
            break;
        case 7:
            cout << "Нахождение пути для элемента: ";
            cin >> key;
            tree.find_way(root, key, s);

            break;
        case 0:
            cout << "\n\tЗавершение программы\n" << endl;
            break;
        default:
            cout << "Неверный ввод\n" << endl;
            break;
        }
        cout << endl;
        system("pause");
        system("cls");
    } while (choice != 0);

    return 0;
}


/*------------
  Длина дерева
-------------- */
int avlTree::height(avl_node* ptr)
{
    int h = 0;
    if (ptr != nullptr)
    {
        int l_height = height(ptr->left);
        int r_height = height(ptr->right);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

/*---------------
    Баланс фактор 
 ----------------*/
int avlTree::diff(avl_node* ptr)
{
    int l_height = height(ptr->left);
    int r_height = height(ptr->right);
    int b_factor = l_height - r_height;
    return b_factor;
}
/*--------------
   Левый поворот
 ---------------*/
avl_node* avlTree::rr_rotation(avl_node* ptr)
{
    avl_node* temp;
    temp = ptr->right;
    ptr->right = temp->left;
    temp->left = ptr;
    return temp;
}
/*---------------
   Правый поворот
 ----------------*/
avl_node* avlTree::ll_rotation(avl_node* ptr)
{
    avl_node* temp;
    temp = ptr->left;
    ptr->left = temp->right;
    temp->right = ptr;
    return temp;
}

/*------------------------
  Большой правый поворот
 -----------------------*/
avl_node* avlTree::lr_rotation(avl_node* ptr)
{
    avl_node* temp;
    temp = ptr->left;
    ptr->left = rr_rotation(temp);
    return ll_rotation(ptr);
}

/*---------------------
  Большой левый поворот
 ----------------------*/
avl_node* avlTree::rl_rotation(avl_node* ptr)
{
    avl_node* temp;
    temp = ptr->right;
    ptr->right = ll_rotation(temp);
    return rr_rotation(ptr);
}

/*-------------------
  Балансировка дерева
---------------------*/
avl_node* avlTree::balance(avl_node* ptr)
{
    int bal_factor = diff(ptr);
    if (bal_factor > 1)
    {
        if (diff(ptr->left) > 0)
            ptr = ll_rotation(ptr);
        else
            ptr = lr_rotation(ptr);
    }
    else if (bal_factor < -1)
    {
        if (diff(ptr->right) > 0)
            ptr = rl_rotation(ptr);
        else
            ptr = rr_rotation(ptr);
    }
    return ptr;
}

/*---------------------------
    Добавить элемент в дерево
-----------------------------*/
avl_node* avlTree::insert(avl_node* ptr, int value, 
    int bulding_year, int number_of_rooms, double price, 
    double total_area, double living_area, string district, 
    string addres)
{
    if (ptr == nullptr)
    {
        ptr = new avl_node;
        ptr->key = value;
        ptr->bulding_year = bulding_year;
        ptr->number_of_rooms = number_of_rooms;
        ptr->price = price;
        ptr->total_area = total_area;
        ptr->living_area = living_area;
        ptr->district = district;
        ptr->addres = addres;
        ptr->left = nullptr;
        ptr->right = nullptr;
        return ptr;
    }
    else if (value < ptr->key)
    {
        ptr->left = insert(ptr->left, value, bulding_year, 
            number_of_rooms, price, total_area, living_area,
            district, addres);
    }
    else if (value >= ptr->key)
    {
        ptr->right = insert(ptr->right, value, bulding_year,
            number_of_rooms, price, total_area, living_area,
            district, addres);
    }
    return balance(ptr);
}

/*------------------
   Удаление Элемента
 -------------------*/
avl_node* avlTree::remove(avl_node* ptr, int value)
{
    if (!ptr)
    {
        cout << "Элемент не найден";
        return 0;
    }
    if (value < ptr->key)
        ptr->left = remove(ptr->left, value);
    else if (value > ptr->key)
        ptr->right = remove(ptr->right, value);
    else //  k == p->key 
    {
        avl_node* q = ptr->left;
        avl_node* r = ptr->right;
        cout << "Элемент удален";
        delete ptr;
        if (!r) return q;
        avl_node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(ptr);
}

/*---------------
    Найти минимум
-----------------*/
avl_node* avlTree::findmin(avl_node* ptr) // поиск узла с минимальным ключом в дереве p 
{
    return ptr->left ? findmin(ptr->left) : ptr;
}

/*-----------------
    Удалить минимум
-------------------*/
avl_node* avlTree::removemin(avl_node* ptr) // удаление узла с минимальным ключом из дерева p
{
    if (ptr->left == 0)
        return ptr->right;
    ptr->left = removemin(ptr->left);
    return balance(ptr);
}
/*------------
  Вывод дерева
 -------------*/
void avlTree::display(avl_node* ptr, int level)
{
    int i;
    if (ptr != nullptr)
    {
        display(ptr->right, level + 1);
        cout << endl;
        if (ptr == root)
            cout << "Дерево -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout << "        ";
        cout << ptr->key;
        display(ptr->left, level + 1);
    }
}
/*-------------------
    Симметричный обход
---------------------*/
void avlTree::inorder(avl_node* ptr)
{
    if (ptr == nullptr)
    { 
        return;
    }  
    inorder(ptr->left);
    cout << ptr->key << "  ";
    inorder(ptr->right);
}
/*------------------
    Нахождение длины
--------------------*/
int avlTree::find_way(avl_node* ptr, int value, int s)
{
    s++;
    if (!ptr) return 0;
    if (value < ptr->key)
        find_way(ptr->left, value, s);
    else if (value > ptr->key)
        find_way(ptr->right, value, s);
    else //  value == ptr->data
    {
        cout << "Длина: " << s - 1;
        s = 0;
    }
}
/*------------------
    Вывод информации
--------------------*/
void avlTree::show_data(avl_node* ptr, double price)
{
    if (ptr == nullptr)
    {
        return;
    }
    show_data(ptr->left, price);
    if (ptr->price == price)
    {
        cout << endl << "Данные о жилом помещении " << ptr->key 
            << endl;
        cout << "Район: " << ptr->district << endl;
        cout << "Адрес: " << ptr->addres << endl;
        cout << "Количество комнат: " << ptr->number_of_rooms << 
            endl;
        cout << "Общая площадь: " << ptr->total_area << endl;
        cout << "Жилая площадь: " << ptr->living_area << endl;
        cout << "Год постройки дома: " << ptr->bulding_year << 
            endl;
        cout << "Стоимость: " << std::fixed <<
            std::setprecision(2) << ptr->price << endl;
    }
    show_data(ptr->right, price);
}