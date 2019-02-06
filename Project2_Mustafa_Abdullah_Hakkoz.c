#include<stdlib.h>
#include<stdio.h>

struct TTNodeType {
	int data;
	struct TTNodeType * right, *middle, * left;
};
typedef struct TTNodeType TTNodeType;

// PART(A)
TTNodeType* insert(int key, TTNodeType *p){
    TTNodeType *temp = NULL;
    
	if(p==NULL){														//if tree is empty
        p = malloc(sizeof(TTNodeType));
        p->data = key;
        p->left = p->right = p->middle = NULL;
        return p;
    }

    else if(key < p->data){
        p->left=insert(key, p->left);
    }
    
    else if(key > p->data && key <= (p->data)^2){
    	p->middle=insert(key, p->middle);
	}
    
    else if(key > (p->data)^2){
        p->right=insert(key, p->right);
    }
	
	return p;
}

//PART(B)

// returns a pointer to node with the minimum key in the BST.
TTNodeType* findMin (TTNodeType *p)
{
	if (p != NULL)
		 while (p->left != NULL) p=p->left;
	return p; 
}

// returns a pointer to node replacing the node removed.
TTNodeType* removeNode (int key, TTNodeType *p)
{
	TTNodeType* tmpPtr;
	
	if (p == NULL)  {                                                      //empty tree
		printf("empty tree");
		return p;
	}
	
	//node with key found!!!
	else if(key == p->data) { 	
		if(p->left == NULL && p->middle == NULL && p->right == NULL){
			return NULL;
		}
		if(p->left != NULL && p->middle != NULL && p->right != NULL){	//if node has three children
			tmpPtr=findMin(p->right);	                      			//find smallest key of right subtree of node with key
		     p->data=tmpPtr->data; 	                          			//replace removed data by smallest key of right subtree
		     p->right=removeNode(tmpPtr->data,p->right);	
		}
				
		else if (p->left!=NULL && p->right!=NULL) {		    //if node has two children (left and right) 
		     tmpPtr=findMin(p->right);	                      //find smallest key of right subtree of node with key
		     p->data=tmpPtr->data; 	                          //replace removed data by smallest key of right subtree
		     p->right=removeNode(tmpPtr->data,p->right);	
		}
		
		else if (p->left!=NULL && p->middle!=NULL) {		       					//if node has two children (left and middle)
		     tmpPtr=findMin(p->middle);	                          //find smallest key of right subtree of node with key
		     p->data=tmpPtr->data; 	                          //replace removed data by smallest key of middle subtree
		     p->middle=removeNode(tmpPtr->data,p->middle);	
		}
		
		else if (p->middle!=NULL && p->right!=NULL) {		       					//if node has two children (middle and right)
		     tmpPtr=findMin(p->right);	                          //find smallest key of right subtree of node with key
		     p->data=tmpPtr->data; 	                          //replace removed data by smallest key of right subtree
		     p->right=removeNode(tmpPtr->data,p->right);	
		}
		
	    else if (p->middle == NULL && p->right == NULL) { 		//if node has only left child
			tmpPtr=p->left; 
			free(p);    
			return tmpPtr;
		}
				
		else if (p->left == NULL && p->right == NULL){				//if node has only middle child
			tmpPtr=p->middle; 
			free(p);     
			return tmpPtr;		
		}  		
		
		else if (p->left == NULL && p->middle == NULL){				//if node has only right child		 
			tmpPtr=p->right;   
			free(p); 
			return tmpPtr;		
		}  	
		
	}	

		
	//start to traverse 
	else if (key < p->data){
		p->left=removeNode(key,p->left);
		
	}
	
	else if (key > p->data && key <= (p->data)^2){
		p->middle=removeNode(key,p->middle); 
	}

	else if (key > (p->data)^2){
		p->right=removeNode(key,p->right); 
	}
	
	
	return p;				            	
}

//Part(C)
void find (TTNodeType *p, int key)
{ 
	if (p != NULL){
		if (key < p->data) 
			find(p->left, key); 
		
		else if (key == p->data)
			printf ("\nKey found: %d", p->data);
				
		else if(key > p->data && key <= (p->data)^2) 
			find(p->middle, key);
				
		else if (key > (p->data)^2)
			find(p->right, key);  
		  
				
	}
	else
		printf ("\nKey NOT found...");  
}

//print tree LNMR
void print(TTNodeType* tree){
    if (tree){
    	print(tree->left);
    	printf("%d ",tree->data);
        print(tree->middle);       
        print(tree->right);
       
    }
}

main(void){
	
  FILE *inpf;
  inpf=fopen("input.txt","r");
  
  TTNodeType *tree=NULL;
  int i, j, key, keyFound;
  
  while (!feof(inpf)) {
  	fscanf(inpf,"%d",&i);
	tree=insert(i, tree);
  }
  printf ("Ternary tree has been builded by reading input file: ");
  print(tree); 
  
  do{
  	printf ("\nTo remove a key press 1, to find a key press 2: "); 
  	scanf("%d",&j);
  	
  	switch (j){
	  case 1: 
  		printf("\nEnter the key you want to remove: ");
  		scanf("%d",&key);
  		tree=removeNode(key, tree);
  		printf("\nCurrent Tree: ");
  		print(tree); 
  		break;
	  
	  
	  case 2:
		printf("\nEnter the key you want to find: ");
	  	scanf("%d",&key);
	  	find(tree, key);
	  	break;
	
	  default:
		printf("\nInvalid Choice...");
	
	}
		
  }while(1);
  
}


