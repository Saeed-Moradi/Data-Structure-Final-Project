//#include "pch.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;
struct node
{
	double key;
	node *left;
	node *right;
	int height;
}; 
int height(node *n)
{
	if (n == NULL)
		return 0;
	return n->height;
}
int max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}
node* newNode(double key)
{
	node* n = new node();
	n->key = key;
	n->left = NULL;
	n->right = NULL;
	n->height = 1;
	return(n);
} 
node* leftRotate(node* parent)
{
	node* kid = parent->right;
	node* grandchild = kid->left;
	kid->left = parent;
	parent->right = grandchild;
	parent->height = max(height(parent->left), height(parent->right)) + 1;
	kid->height = max(height(kid->left), height(kid->right)) + 1;
	return kid;
}
node* rightRotate(node* dad)
{
	node* kid = dad->left;
	node* grandchild = kid->right;
	kid->right = dad;
	dad->left = grandchild;
	dad->height = max(height(dad->left), height(dad->right)) + 1;
	kid->height = max(height(kid->left), height(kid->right)) + 1;
	return kid;
}
int getBalance(node *n)
{
	if (n == NULL)
		return 0;
	return height(n->left) - height(n->right);
} 
bool findValue(node* , double);
node* insert(node* n, double key)
{
	if (n == NULL) 
	{
		cout << "added" << endl;
		return(newNode(key));
	}
	if (key < n->key)
		n->left = insert(n->left, key);
	else if (key > n->key)
		n->right = insert(n->right, key);
	else  
		return n;

	n->height = 1 + max(height(n->left),
		height(n->right));
	int balance = getBalance(n);
	if (balance < -1 && key > n->right->key)
	{
		cout << "balancing " << setprecision(1) << fixed << n->key << endl;
		return leftRotate(n);
	}
	if (balance < -1 && key < n->right->key)
	{
		n->right = rightRotate(n->right);
		cout << "balancing " << setprecision(1) << fixed << n->key << endl;
		return leftRotate(n);
	}
	if (balance > 1 && key < n->left->key)
	{
		cout << "balancing " << setprecision(1) << fixed << n->key << endl;
		return rightRotate(n);
	}
	if (balance > 1 && key > n->left->key)
	{
		n->left = leftRotate(n->left);
		cout << "balancing " << setprecision(1) << fixed << n->key << endl;
		return rightRotate(n);
	}
	return n;
}
node* minValueNode(node* n)
{
	node* current = n;

	while (current->left != NULL)
		current = current->left;

	return current;
}
bool findValue(node*, double);
node* deleteNode(node* root, double key)
{
	if (key < root->key)
	{
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->key)
	{
		root->right = deleteNode(root->right, key);
	}
	else
	{
		if ((root->left == NULL) || (root->right == NULL))
		{
			node *temp = root->left ?
				root->left :
				root->right;  
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else  
				*root = *temp;  		  
			free(temp);
		}
		else
		{ 
			node* temp = minValueNode(root->right);
			root->key = temp->key;  
			root->right = deleteNode(root->right,temp->key);
		}
	}
	if (root == NULL)
		return root;
	root->height = 1 + max(height(root->left),height(root->right));
	int balance = getBalance(root); 
	if (balance > 1 && getBalance(root->left) >= 0)
	{
		cout << "balancing " << setprecision(1) << fixed << root->key << endl;
		return rightRotate(root);
	}
	if (balance > 1 && getBalance(root->left) < 0)
	{
		cout << "balancing " << setprecision(1) << fixed << root->key << endl;
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if (balance < -1 && getBalance(root->right) <= 0)
	{
		cout << "balancing " << setprecision(1) << fixed << root->key << endl;
		return leftRotate(root);
	}
	if (balance < -1 && getBalance(root->right) > 0)
	{
		cout << "balancing " << setprecision(1) << fixed << root->key << endl;
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}
bool findValue(node* root , double v)
{
	node* temp = root;
	while (temp)
	{
		if (temp->key > v)
		{
			temp = temp->left;
		}
		else if (temp->key < v)
		{
			temp = temp->right;
		}
		else
		{
			return true;
		}
	}
	return false;
}
void find(node* root, double v)
{
	double minDifference = 1000;
	double minOflargest = -1;
	double m = NULL;
	node* temp = root;
	while (temp)
	{
		if (temp->key > v)
		{
			if (temp->key - v < minDifference)
			{
				minOflargest = temp->key;
			}
			temp = temp->left;
		}
		else if (temp->key < v)
		{
			temp = temp->right;
		}
		else
		{
			cout << setprecision(1) << fixed << v << endl;
			return;
		}
	}
	if (minOflargest == -1)
	{
		cout << "not found" << endl;
	}
	else
	{
		cout << setprecision(1) << fixed << minOflargest << endl;
	}
}
int main()
{
	node* root = NULL;
	double value;
	string command;
	int number;
	int a = 0;
	cin >> number;
	while (number != 0)
	{
		cin >> command;
		if (command == "add")
		{
			cin >> value;
			bool find = findValue(root, value);
			if (find == true)
			{
				cout << "already in there" << endl;
			}
			else
			{
				root = insert(root, value);
			}
		}
		if (command == "remove")
		{
			cin >> value;
			bool b = findValue(root, value);
			if (b == false)
			{
				cout << "does not exist" << endl;
			}
			else
			{
				if (b == true && a == 0)
				{
					cout << "removed" << endl;
					a++;
				}
				root = deleteNode(root, value);
			}
		}
		if (command == "find")
		{
			cin >> value;
			find(root, value);
		}
		number--;
		a = 0;
	}
}
