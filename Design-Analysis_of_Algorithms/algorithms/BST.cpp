#include <iostream>

using namespace std;

typedef struct node{
	int key;
	struct node* lchild;
	struct node* rchild;
} node;

node* newNode(int val);
node* insert(node* n, int val);
node* search(node* n, int val);
node* findMin(node* n);
node* findMax(node* n);
void preOrder(node* n);
void inOrder(node* n);
void postOrder(node* n);
void findPreSuc(node* root, node*& pre, node*& suc, int val);
node* deleteNode(node* root, int val);
node* trimTree(node* root, int min, int max);
		
int main(int argc, char** argv){
	// create empty BST
	node* root = NULL;
	
	int len;
	cout << "How many nodes? ";
	cin >> len;
	
	int nodeList[len];
	
	cout << "\nEnter " << len << " keys: "; 
	for(int i=0; i<len; i++)
		cin >> nodeList[i];
	
	root = insert(root,nodeList[0]);
	for(int i=1; i<len; i++){
		insert(root,nodeList[i]);
	}
	
	cout << "\nPreorder traversal: ";
	preOrder(root);
	cout << endl;
	
	cout << "Inorder traversal: ";
	inOrder(root);
	cout << endl;

	cout << "Postorder traversal: ";
	postOrder(root);
	cout << endl;
	
	cout << "\nTrim tree between 40 and 70\n";
	root = trimTree(root,40,70);
	cout << "New tree (inorder): ";
	inOrder(root);
	cout << endl;
	

	while(root != NULL){
		cout << "\nDeleting node " << root->key << endl;
		root = deleteNode(root,root->key);
		cout << "New tree (inorder): ";
		inOrder(root);
		cout << endl;
	}

	return 0;
}

node* newNode(int val){
	node* n = new node;
	n->key = val;
	n->lchild = n->rchild = NULL;
	return n;
}

node* insert(node* n, int val){
	if(n==NULL)
		return newNode(val);
	
	else if(val < n->key)
		n->lchild = insert(n->lchild,val);
	
	else
		n->rchild = insert(n->rchild,val);
	
	return n;
}

node* search(node* n, int val){
	if(n==NULL)
		return NULL;
	if(n->key==val)
		return n;
	else{
		if(val < n->key)
			search(n->lchild,val);
		else
			search(n->rchild,val);
	}
}

node* findMin(node* n){
	if(n==NULL)
		return NULL;
	
	if(n->lchild==NULL)
		return n;
	
	findMin(n->lchild);
}

node* findMax(node* n){
	if(n==NULL)
		return NULL;
	
	if(n->rchild==NULL)
		return n;
	
	findMax(n->rchild);
}

void preOrder(node* n){
	if(n==NULL)
		return;
	
	cout << n->key << " ";
	preOrder(n->lchild);
	preOrder(n->rchild);
}

void inOrder(node* n){
	if(n==NULL)
		return;
	
	inOrder(n->lchild);
	cout << n->key << " ";
	inOrder(n->rchild);
}

void postOrder(node* n){
	if(n==NULL)
		return;
	
	postOrder(n->lchild);
	postOrder(n->rchild);
	cout << n->key << " ";
}

void findPreSuc(node* root, node*& pre, node*& suc, int val){
	if(root==NULL)
		return;
	if(root->key == val){
		if(root->lchild != NULL){
			node* tmp = root->lchild;
			while(tmp->rchild)
				tmp = tmp->rchild;
			pre = tmp;
		}
		
		if(root->rchild != NULL){
			node* tmp = root->rchild;
			while(tmp->lchild)
				tmp = tmp->lchild;
			suc = tmp;
		}
		return;
	}
	
	if(root->key > val){
		suc = root;
		findPreSuc(root->lchild,pre,suc,val);
	}
	else{
		pre = root;
		findPreSuc(root->rchild,pre,suc,val);
	}
}

node* deleteNode(node* root, int val){
	// base case
	if(root==NULL)
		return root;
	
	if(val < root->key)
		root->lchild = deleteNode(root->lchild,val);
	else if(val > root->key)
		root->rchild = deleteNode(root->rchild,val);
	else{
		// node with only one or no child
		if(root->lchild==NULL){
			node* temp = root->rchild;
			delete root;
			return temp;
		}
		else if(root->rchild==NULL){
			node* temp = root->lchild;
			delete root;
			return temp;
		}
		
		// node with two children
		// find inorder successor
		else{
			node* succ = findMin(root->rchild);
		
			// copy successor's key to current node
			root->key = succ->key;
		
			// delete successor
			root->rchild = deleteNode(root->rchild, succ->key);
		}
	}
	return root;
}

node* trimTree(node* root, int min, int max){
	if(root==NULL)
		return NULL;
	
	root->lchild = trimTree(root->lchild,min,max);
	root->rchild = trimTree(root->rchild,min,max);
	
	if(root->key < min){
		node* r = root->rchild;
		delete root;
		return r;
	}
	if(root->key > max){
		node* l = root->lchild;
		delete root;
		return l;
	}
	return root;
}
