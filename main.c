#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int key;
	char name[255];
	struct Node *left;
	struct Node *right;
	int height;
};

int max(int a, int b);

int height(struct Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int max(int a, int b)
{
	return (a > b)? a : b;
}

struct Node* newNode(int key, const char*name)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	strcpy(node->name,name);
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return(node);
}


struct Node *rightRotate(struct Node *y)
{
	struct Node *x = y->left;
	struct Node *T2 = x->right;


	x->right = y;
	y->left = T2;


	y->height = max(height(y->left), height(y->right))+1;
	x->height = max(height(x->left), height(x->right))+1;

	return x;
}


struct Node *leftRotate(struct Node *x)
{
	struct Node *y = x->right;
	struct Node *T2 = y->left;


	y->left = x;
	x->right = T2;


	x->height = max(height(x->left), height(x->right))+1;
	y->height = max(height(y->left), height(y->right))+1;


	return y;
}


int getBalance(struct Node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

struct Node* insert(struct Node* node, int key, const char*name)
{

	if (node == NULL)
		printf("Add Successfull\n");
		return(newNode(key,name));

	if (key < node->key)
		node->left = insert(node->left, key, name);
	else if (key > node->key)
		node->right = insert(node->right, key, name);
	else
		return node;


	node->height = 1 + max(height(node->left), height(node->right));


	int balance = getBalance(node);

	// If this node becomes unbalanced, then there are 4 cases

	// Left Left Case
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right Case
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right Case
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}

/* Given a non-empty binary search tree, return the
node with minimum key value found in that tree.
Note that the entire tree does not need to be
searched. */
struct Node * minValueNode(struct Node* node)
{
	struct Node* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}

// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
struct Node* deleteNode(struct Node* root, int key, const char*name)
{
	// STEP 1: PERFORM STANDARD BST DELETE

	if (root == NULL)
		return root;

	// If the key to be deleted is smaller than the
	// root's key, then it lies in left subtree
	if ( key < root->key )
		root->left = deleteNode(root->left, key, name);

	// If the key to be deleted is greater than the
	// root's key, then it lies in right subtree
	else if( key > root->key )
		root->right = deleteNode(root->right, key, name);

	// if key is same as root's key, then This is
	// the node to be deleted
	else
	{
		// node with only one child or no child
		if( (root->left == NULL) || (root->right == NULL) )
		{
			struct Node *temp = root->left ? root->left : root->right;

			// No child case
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case
			*root = *temp; // Copy the contents of
							// the non-empty child
			free(temp);
		}
		else
		{
			// node with two children: Get the inorder
			// successor (smallest in the right subtree)
			struct Node* temp = minValueNode(root->right);

			// Copy the inorder successor's data to this node
			root->key = temp->key;

			// Delete the inorder successor
			root->right = deleteNode(root->right, temp->key, temp->name);
		}
	}

	// If the tree had only one node then return
	if (root == NULL)
	return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
	root->height = 1 + max(height(root->left), height(root->right));

	// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
	// check whether this node became unbalanced)
	int balance = getBalance(root);

	// If this node becomes unbalanced, then there are 4 cases

	// Left Left Case
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	// Left Right Case
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

void preOrder(struct Node *root)
{
	if(root != NULL)
	{
		printf(" %d ", root->key);
		preOrder(root->left);
		preOrder(root->right);
	}
}
void inOrder(struct Node *root)
{
	if(root != NULL)
	{
		inOrder(root->left);
		printf(" %d ", root->key);
		inOrder(root->right);
	}
}
void postOrder(struct Node *root)
{
	if(root != NULL)
	{
		postOrder(root->left);
		postOrder(root->right);
		printf(" %d ", root->key);
	}
}

void display(struct Node* ptr,struct Node* r, const char *name){
	if(ptr!=NULL){
		display(ptr->right,r,name);
		printf("\n");
		if(ptr==r){
			printf("Root ->");
		}
		printf(" %d %s \n",ptr->key, ptr->name);
		display(ptr->left,r,name);
	}
}

void print(struct Node *root){
  if(root!=NULL) {
  	//preorder
    printf("- %d %s \n",root->key,root->name);
    print(root->left);
    print(root->right);
  }

}

void printmenu(){

	puts("----------------------------");
	puts("RECRUITMENT FOR NEW EMPLOYEE");
	puts("----------------------------");
	puts("");
	puts("1. View All Employee");
	puts("2. Add New Employee");
	puts("3. Remove Employee");
	puts("4. Preview Employee By");
	puts("5. Help");
	puts("6. Exit");
	puts("");
}
// int main()
// {
// struct Node *root = NULL;
// 	printf("==============================================\n");
// 	printf("              AVL Tree By Kstar               \n");
// 	printf("==============================================\n");
// 	int item,c;
// 	char name[255];
// 	while(1){
// 		printf("\n1--Insert\n2--delete\n3--inorder\n4--preorder\n5--postorder\n6--Tree Representation\n7--exit\n");
// 		printf("Enter Choice:-->  ");
// 		scanf("%d",&c);
// 		if(c==7){
// 			break;
// 		}
// 		switch(c){
// 			case 1:
// 			printf("Enter Value:- ");
// 			scanf("%d",&item);
// 			printf("\nInput Employee' s Name [3..50]: ");
// 			getchar();
// 			scanf("%[^\n]s",name);
// 			getchar();
// 			root = insert(root,item);
// 			break;
// 			case 2:
// 			printf("Enter Value:- ");
// 			scanf("%d",&item);
// 			root = deleteNode(root,item);
// 			break;
// 			case 3:
// 			printf("\n");
// 			printf("Inorder transversal of AVL Tree");
// 			inOrder(root);
// 			printf("\n");
// 			break;
// 			case 4:
// 			printf("\n");
// 			printf("Preorder transversal of AVL Tree");
// 			preOrder(root);
// 			printf("\n");
// 			break;
// 			case 5:
// 			printf("\n");
// 			printf("Postorder transversal of AVL Tree");
// 			postOrder(root);
// 			printf("\n");
// 			break;
// 			case 6:
// 			printf("\n");
// 			printf("Balanaced AVL TREE");
// 			display(root,1 ,root);
// 			printf("\n");
// 			break;
// 			default:
// 			printf("Wrong Choice ");
// 			break;
// 		}
// 	}
// 	return 0;
// }

struct Node *searchNode(struct Node *node, int key) {
  if(node) {
    if(key == node->key) {
      return node;
    } else if(key < node->key) {
      return searchNode(node->left, key);
    } else if(key > node->key) {
      return searchNode(node->right, key);
    }
  }

  return 0;
}



int main(){
    struct Node *root = NULL;
	int input,input1,key;
	char name[255];
	puts("");
	while(1){
	printmenu();
	printf(">> Input choice :");
	scanf("%d",&input);

		if(input==1){
			if(root==NULL){
				puts("--- There is No Employee in The Tree ---");
			}
			else{
				puts("");
  				puts("Employee List :");
				// display(root,1 ,root, name);
				print(root);
			}
		}
		else if(input==2){
			while(1){
				printf("\nInput Employee' s Name [3..50]: ");
				getchar();
				scanf("%[^\n]s",name);
				getchar();
				if(strlen(name)<3 || strlen(name)>50){
						puts("Name Too Short or Too Long");
				}
				else{
					while(1){
						printf("Input Employee' s ID [0..100]: ");
					scanf("%d",&key);
					if(key<0 || key>100){
						puts("ID Doesn't Exist");
					}
					else if(searchNode(root,key)==NULL){
						root=insert(root,key,name);
						break;
					}
					else if(searchNode(root,key)!=NULL){
						puts("Employee's ID Cannot be the Same, Please Input Other ID");
					}
				}
				break;
			}
		}
	}
		else if(input==3){
			while(1){
			printf("Input Employee's ID That You Want to Be Removed[0..100]: ");
			scanf("%d",&key);
			struct tree *node;
		if (node==NULL){
        puts("--- The ID Doesn't Exist ---");
    	}
	    else{

		root = deleteNode(root,key,name);
			puts("--- The ID Has Been Removed ---");
			break;
		}
	}
}
		else if(input==4){
			printf("\n1. InOrder");
			printf("\n2. PreOrder");
			printf("\n3. PostOrder");

			printf("\nEnter Your Choice: ");
			scanf("%d",&input1);

			if(input1==1){
				if(root==NULL){
					puts("--- There is No ID in The Tree ---");
			}else {
				printf("\n\nInOrder:");
				inOrder(root);
			}
			}else if (input1==2){
				if(root==NULL){
					puts("--- There is No ID in The Tree ---");
				}else {
					printf("\n\nPreOrder:");
					preOrder(root);
			}
			}else if (input1 == 3){
				if(root==NULL){
					puts("--- There is No ID in The Tree ---");
				}else {
					printf("\n\nPostOrder:");
					postOrder(root);
				}
			}
		}
		else if(input==9){
			exit(0);
		}
	}
	return 0;

	}


