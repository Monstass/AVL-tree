#include <iostream>

using namespace std;

/*
	��������� ������
 */
struct avl_node
{
	int data;
	struct avl_node* left;
	struct avl_node* right;
}*root;

/*
	 ����� ������
 */
class avlTree
{
public:
	int height(avl_node*);
	int diff(avl_node*);
	int even(avl_node*);
	int find_way(avl_node*, int);
	avl_node* rr_rotation(avl_node*);
	avl_node* ll_rotation(avl_node*);
	avl_node* lr_rotation(avl_node*);
	avl_node* rl_rotation(avl_node*);
	avl_node* balance(avl_node*);
	avl_node* insert(avl_node*, int);
	avl_node* remove(avl_node*, int);
	avl_node* removemin(avl_node*);
	avl_node* findmin(avl_node*);
	void display(avl_node*, int);
	void inorder(avl_node*);
	avlTree()
	{
		root = nullptr;
	}
};

bool rootNum = false;
int leftEven = 0;
int rightEven = 0;
int s = 0;

int main()
{
	setlocale(LC_ALL, "Russian");
	int key, choice;
	avlTree tree;

	do
	{
		cout << "\t\t::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::1 �������� ����� �������::::::::::::::::::::" << endl;
		cout << "\t\t::::2 ������� �������:::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::3 ����� ������ �� �����:::::::::::::::::::::" << endl;
		cout << "\t\t::::4 ������������ �����::::::::::::::::::::::::" << endl;
		cout << "\t\t::::5 ������ ������:::::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::6 ����� �����������:::::::::::::::::::::::::" << endl;
		cout << "\t\t::::7 ���������� ����� ����:::::::::::::::::::::" << endl;
		cout << "\t\t::::0 �����:::::::::::::::::::::::::::::" << endl;
		cout << "\t\t::::::::::::::::::::::::::::::::::::::::::::::::\n" << endl;

		cout << "\n�������� ������ �������� � ������� Enter: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "���������� ������ ��������" << endl;
			cout << "������� �������: ";
			cin >> key;
			root = tree.insert(root, key);
			cout << "����� ������� �������� �������\n" << endl;

			break;
		case 2:
			cout << "�������� ��������" << endl;
			cout << "������� �������: ";
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
			cout << tree.height(root) - 1;

			break;
		case 6:

		case 7:
			cout << "���������� ���� ��� ��������: ";
			cin >> key;
			tree.find_way(root, key);

			break;
		case 0:
			cout << "\n\t���������� ���������\n" << endl;
			break;
		default:
			cout << "�������� ����\n" << endl;
			break;
		}
		cout << endl;
		system("pause");
		system("cls");
	} while (choice != 0);

	return 0;
}


/*
 * Height of tree Tree
 */
int avlTree::height(avl_node* temp)
{
	int h = 0;
	if (temp != nullptr)
	{
		int l_height = height(temp->left);
		int r_height = height(temp->right);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}

/*
 ������ ������
 */
int avlTree::diff(avl_node* temp)
{
	int l_height = height(temp->left);
	int r_height = height(temp->right);
	int b_factor = l_height - r_height;
	return b_factor;
}

/*
 * Right- Right Rotation
 */
avl_node* avlTree::rr_rotation(avl_node* parent)
{
	avl_node* temp;
	temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}
/*
 * Left- Left Rotation
 */
avl_node* avlTree::ll_rotation(avl_node* parent)
{
	avl_node* temp;
	temp = parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}

/*
  Left - Right Rotation
 */
avl_node* avlTree::lr_rotation(avl_node* parent)
{
	avl_node* temp;
	temp = parent->left;
	parent->left = rr_rotation(temp);
	return ll_rotation(parent);
}

/*
  Right- Left Rotation
 */
avl_node* avlTree::rl_rotation(avl_node* parent)
{
	avl_node* temp;
	temp = parent->right;
	parent->right = ll_rotation(temp);
	return rr_rotation(parent);
}

/*
  Balancing tree Tree
 */
avl_node* avlTree::balance(avl_node* temp)
{
	int bal_factor = diff(temp);
	if (bal_factor > 1)
	{
		if (diff(temp->left) > 0)
			temp = ll_rotation(temp);
		else
			temp = lr_rotation(temp);
	}
	else if (bal_factor < -1)
	{
		if (diff(temp->right) > 0)
			temp = rl_rotation(temp);
		else
			temp = rr_rotation(temp);
	}
	return temp;
}

/*
 �������� ������� � ������
 */
avl_node* avlTree::insert(avl_node* root, int value)
{
	if (root == nullptr)
	{
		root = new avl_node;
		root->data = value;
		root->left = nullptr;
		root->right = nullptr;
		return root;
	}
	else if (value < root->data)
	{
		root->left = insert(root->left, value);
	}
	else if (value >= root->data)
	{
		root->right = insert(root->right, value);
	}
	return balance(root);
}

/*
   �������� ��������
 */
avl_node* avlTree::remove(avl_node* ptr, int value)
{
	if (!ptr) return 0;
	if (value < ptr->data)
		ptr->left = remove(ptr->left, value);
	else if (value > ptr->data)
		ptr->right = remove(ptr->right, value);
	else //  k == p->key 
	{
		avl_node* q = ptr->left;
		avl_node* r = ptr->right;
		cout << "������� ������";
		delete ptr;
		if (!r) return q;
		avl_node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(ptr);
}

/*
	����� �������
*/
avl_node* avlTree::findmin(avl_node* ptr) // ����� ���� � ����������� ������ � ������ p 
{
	return ptr->left ? findmin(ptr->left) : ptr;
}

/*
	������� �������
*/
avl_node* avlTree::removemin(avl_node* ptr) // �������� ���� � ����������� ������ �� ������ p
{
	if (ptr->left == 0)
		return ptr->right;
	ptr->left = removemin(ptr->left);
	return balance(ptr);
}


/*
  ����� ������
 */
void avlTree::display(avl_node* ptr, int level)
{
	int i;
	if (ptr != nullptr)
	{
		display(ptr->right, level + 1);
		cout << endl;
		if (ptr == root)
			cout << "������ -> ";
		for (i = 0; i < level && ptr != root; i++)
			cout << "        ";
		cout << ptr->data;
		display(ptr->left, level + 1);
	}
}

/*
 ������������ �����
 */
void avlTree::inorder(avl_node* tree)
{
	if (tree == nullptr)
	{
		return;
	}
	inorder(tree->left);
	cout << tree->data << "  ";
	inorder(tree->right);
}

int avlTree::find_way(avl_node* tree, int value)
{
	s++;
	if (!tree) return 0;
	if (value < tree->data)
		find_way(tree->left, value);
	else if (value > tree->data)
		find_way(tree->right, value);
	else //  value == ptr->data
	{
		cout << "�����: " << s - 1;
		s = 0;
	}
}