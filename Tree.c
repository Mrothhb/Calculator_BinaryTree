//==========================================================================
// cs12xcm                         Homework 7            Matt Roth 
//
// February 19 2019	
//--------------------------------------------------------------------------
// File: Tree.c
//
// Description:		The program will represent a Binary Tree, with a Tree node
//		structure, that contains a root node with possible 
//		children nodes to the left and right. Each node in the tree will 
//		contain data and a pointer to the next node in the tree which may be
//		a child or a parent. Nodes and data can be inserted, searched for and 
//		removed from the tree. 
//
//==========================================================================

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string.h>
#include "Tree.h"
using namespace std;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

//debug messages 
static const char ALLOCATE[] = " - Allocating]\n";
static const char DEALLOCATE[] = " has been deallocated]\n";
static const char AND[] = " and ";
static const char COMPARE[] = " - Comparing ";
static const char INSERT[] = " - Inserting ";
static const char TREE[] = "[Tree ";

//=========================================================================
// struct TNode 
//
// Description:		The TNode will create a node in the binary tree that 
//		will hold the data, the occupancy and the hasBeen Deleted flag.
//
//  
// Data Fields:
//     data - the data item to be contained in the node   
//     occupancy - the amount of nodes in the tree
//     hasBeenDeleted - the flag to indicate if an element was deleted
//
// Public functions:
//					TNode - constructor(s) for initialization
//					~TNode - destructor 
//					ostream & Write - the toString  
//					ostream & Write_AllTNodes - toString for TNodes  
//					delete_AllTNodes - delete all the nodes in the tree
//==========================================================================
struct TNode {

	//data fields for the TNode 
	Base * data;
	TNode * left, * right, *parent;
	static long occupancy;
	unsigned long hasBeenDeleted;

	// left child's height - right child's height
	long balance;

	// 1 + height of tallest child, or 0 for leaf
	long height;

/***************************************************************************
% Routine Name : TNode (public)
% File :         Tree.c
% 
% Description :  Initializes the data with element, left, right and parent 
		nodes to null, balance and height to 0. Increment the occupancy 
 ***************************************************************************/
	TNode (Base * element) : data (element), left (0), right (0),
	parent (0), hasBeenDeleted (FALSE), balance (0), height(0) {

		//increase the occupancy with each node created
		occupancy++;

	}
/***************************************************************************
% Routine Name : ~TNode (public)
% File :         Tree.c
% 
% Description :  Deallocated memory deletes the data 
***************************************************************************/
	~TNode (void) {

		//delete the data in the node 
		delete data;

	}
/***************************************************************************
% Routine Name : ostream & Write (public)
% File :         Tree.c
% 
% Description :	The toString for the TNode   
***************************************************************************/

	ostream & Write (ostream & stream) const {
		stream << "at height:  " << height << "  with balance:  "
			<< balance << "  ";

		return data->Write (stream) << "\n";
	}
/***************************************************************************
% Routine Name : ostream & Write_AllTNodes (public)
% File :         Tree.c
% 
% Description :	write out all the TNode data   
***************************************************************************/
	ostream & Write_AllTNodes (ostream & stream) const {

		if (left)
			left->Write_AllTNodes (stream);
		if (!hasBeenDeleted)
			Write (stream);
		if (right)
			right->Write_AllTNodes (stream);

		return stream;
	}
/***************************************************************************
% Routine Name : delete_AllTNodes (public)
% File :         Tree.c
% 
% Description : Deletes all the TNodes in the Tree recursively
***************************************************************************/
	void delete_AllTNodes (void) {
		
		//exit if the node doesnt exist yet
		if(this == NULL){
			return;
		}

		//check for the left node
		if(left != NULL){

			left->delete_AllTNodes();

		}

		//check for the right node 
		if(right != NULL){

			right->delete_AllTNodes();
		}

		//delete this node 
		delete this;
	}

};

//=========================================================================
// class Tree
//
// Description:		The Tree class will act as a Binary Tree to hold 
//		various left and right Nodes that will contain data. The data 
//		and nodes will be accessed via traversal of the tree. 
//
//  
// Data Fields:
//     occupancy - the amount of nodes in the tree   
//     debug_on - initialization of the debugger
//
// Public functions:
//					Tree - constructor(s) for initialization
//					~Tree - destructor 
//					Write - the toString  
//					isEmpty - check if the tree is empty
//					Lookup - search for an element in tree
//					Remove - remove a node from tree
//					Insert - insert an element into the tree
//==========================================================================

// initialization of static data fields of Tree
long TNode :: occupancy = 0;
bool Tree :: debug_on = 0;


void Tree :: Set_Debug (bool option) {
/***************************************************************************
% Routine Name : Tree :: Tree  (public)
% File :         Tree.c
% 
% Description :  Initializes root pointer to NULL, and occupancy to 0.
***************************************************************************/

	if(option){

		Tree::debug_on = TRUE;
	}

	else{

		Tree::debug_on = FALSE;
	}
}

Tree :: Tree (const char * name) : root (0), tree_name (strdup (name))
/***************************************************************************
% Routine Name : Tree :: Tree  (public)
% File :         Tree.c 
% Description :  Initializes root pointer to NULL, and occupancy to 0.
**************************************************************************/
{
	TNode::occupancy = 0;

	if(debug_on){

		cerr<<(const char*)TREE<<tree_name<<(const char*)ALLOCATE<< "\n";
	}

}

Tree :: ~Tree (void)
/***************************************************************************
% Routine Name : Tree :: ~Tree  (public)
% File :         Tree.c
% 
% Description :  deallocates memory associated with the Tree.  It
%                will also delete all the memory of the elements within
%                the table.
***************************************************************************/

{
	//call this roots delete all the nodes method 
	root->delete_AllTNodes();

	if(debug_on){

		cerr<<(const char*)TREE<<tree_name<<
			(const char*)DEALLOCATE<<"\n";
	}

	//deallocate the name pointer 
	free((void*)tree_name);


}	/* end: ~Tree */

/***************************************************************************
% Routine Name : Tree :: IsEmpty (public)
% File :         Tree.c
% 
% Description :		Check the tree for an occupancy of zero (no nodes)
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% % <return>        TRUE FALSE
***************************************************************************/
unsigned long Tree :: IsEmpty () const {

	//check the occupancy 
	if(TNode::occupancy == 0){

		return TRUE;
	}

	return FALSE;
}

/***************************************************************************
% Routine Name : Tree :: Insert (public)
% File :         Tree.c
% 
% Description :		The insert method will insert a new node into the tree
%			with data from the user. 
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% element            the Base element 
% <return>           TRUE or FALSE
***************************************************************************/
unsigned long Tree :: Insert (Base * element) {

	//temp current working node
	TNode * working = root;

	//loop conditions
	int found = FALSE;
	int update = TRUE;

	//local variables to help calculate the height and balances 
	long left_height = -1;
	long right_height = -1;
	long tallest_height = 1;


	//if this is the first TNode in the structure (null root)
	if(root == NULL){

		if(debug_on){

			cerr<<(const char*)TREE<<tree_name<<(const char*)INSERT<<
				*element<<"]"<<"\n";
		}

		//create the first tree node 
		root = new TNode(element);

		return TRUE;

	}

	//find the correct placement for the incoming element 
	else {

		while (!found){


			//duplicate insert
			if(*element == *(working->data)){

				//check if the element has already been deleted
				if(working->hasBeenDeleted){

					working->hasBeenDeleted = FALSE;
					TNode::occupancy++;
					
				}

				if(debug_on){

					cerr<<(const char*)TREE<<tree_name<<
						(const char*)INSERT<<*element<<"]"<<"\n";
				}

				//delete the extra data 
				delete working->data;

				//replace the element in the current TNode
				working->data = element;

				//increase the occupancy 

				found = TRUE;
			}

			//if the element is greater than the current node
			else if(*element > *(working->data)){


				if(debug_on){

					cerr<<(const char*)TREE<<tree_name<<(const char*)COMPARE
						<<*element<<(const char*)AND
						<<*working->data<<"]"<<"\n";
				}

				//go right 
				if(working->right == NULL){

					if(debug_on){

						cerr<<(const char *)TREE<<tree_name<<(const char *)
							INSERT<<*element<<"]"<<"\n";
					}

					//insert the new node into the tree
					working->right = new TNode(element);

					working->right->parent = working;

					found = TRUE;
				}

				//increment the working node to the right 
				else{

					working = working->right;
				}

			}

			else {

				//go left
				if(working->left ==  NULL){

					if(debug_on){

						cerr<<(const char *)TREE<<tree_name<<(const char *)
							INSERT<<*element<<"]"<<"\n";
					}

					//insert the new node on the left 
					working->left = new TNode(element);

					working->left->parent = working;

					found = TRUE;
				}

				//increment the working node to the left 
				else{

					working = working->left;
				}
			}
		}
	}	

	//go back up the tree and correct the heights and balances
	while(update){

		//if the left child node is non-empty get the height 
		if(working->left != NULL){

			left_height = working->left->height;

		}

		//if the right child node is non-empty get the height 
		if(working->right != NULL){

			right_height = working->right->height;
		}

		//set the working nodes height 
		working->balance = left_height - right_height;

		//check for the tallest child node 	
		if(left_height > right_height){

			tallest_height = left_height;
		}

		else {

			tallest_height = right_height;
		}

		//increment the height of the working node 
		working->height = ++tallest_height;

		working = working->parent;

		//once the root is reached terminate loop
		if(working == NULL){

			update = FALSE;
		}		
	}

	return TRUE;
}

/***************************************************************************
% Routine Name : Tree :: Lookup (public)
% File :         Tree.c
% 
% Description :		This method will search the Tree for an item 
%
% Parameters descriptions :
% 
% name               description
% ------------------ -----------------------------------------------------
 element	         The Base element     
% <return>           A pointer to the data 
***************************************************************************/
const Base * Tree :: Lookup (const Base * element) const {

	//temp current working node
	TNode * working = root;


	//if there isnt a root node yet
	if(root == NULL){

		return NULL;

	}

	//find the node and data matching the parameter
	else {

		while (TRUE){

			//return null when the current node is null
			if(working == NULL){

				return NULL;
			}

			//return the data is the item matches
			if(*element == *(working->data)){

				//check if the data has been deleted 
				if(working->hasBeenDeleted){

					return NULL;
				}

				return working->data;

			}

			//check if the item is greate than or less than parameter 
			else if(*element > *(working->data)){


				if(debug_on){

					cerr<<(const char *)TREE<<tree_name<<(const char *)
						COMPARE<<*element<<(const char *)AND<<*working->data<<
						"]"<<"\n";
				}


				//shift to the right node down the tree
				working = working->right;

			}

			else{

				//shift to the left node down the tree 
				working = working->left;

			}
		}
	}	

}

/***************************************************************************
% Routine Name : Tree :: Remove (public)
% File :         Tree.c
% 
% Description :		This method will remove a Node from the Tree
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% element	         The Base element     
% <return>           A pointer to the data 
***************************************************************************/
Base * Tree :: Remove (const Base * element) {

	//temp current working node
	TNode * working = root;


	//if there isnt a root node yet
	if(root == NULL){

		return NULL;

	}

	//find the node and data matching the parameter
	else {

		while (TRUE){

			//return null when the current node is null
			if(working == NULL){

				return NULL;
			}

			//return the data if the item matches
			if(*element == *(working->data)){

				//check if the element has been deleted already
				if(working->hasBeenDeleted){

					return NULL;
				}

				//shallow delete 
				working->hasBeenDeleted = TRUE;

				//decrease the occupancy of the tree 
				TNode::occupancy--;

				return working->data;

			}

			//check if the item is greate than or less than parameter 
			else if(*element > *(working->data)){

				if(debug_on){

					cerr<<(const char *)TREE<<tree_name<<(const char *)COMPARE
					<<*element<<(const char *)AND<<*working->data<<"]"<<"\n";
				}


				//shift to the right node down the tree
				working = working->right;

			}

			else{

				//shift to the left node down the tree 
				working = working->left;

			}
		}
	}	

	return NULL;
}

ostream & Tree :: Write (ostream & stream) const
/***************************************************************************
% Routine Name : Tree :: Write (public)
% File :         Tree.c
% 
% Description : This function will output the contents of the Tree table
%               to the stream specificed by the caller.  The stream could be
%               cerr, cout, or any other valid stream.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% stream             A reference to the output stream.
% <return>           A reference to the output stream.
***************************************************************************/
{
	stream << "Tree " << tree_name << ":\n"
		<< "occupancy is " << TNode :: occupancy << " elements.\n";

	return (root) ? root->Write_AllTNodes (stream) : stream;
}       /* end: Write */

