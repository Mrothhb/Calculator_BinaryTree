/****************************************************************************

Matthew Roth, A15685519
CSE 12, Winter 2019
February 19, 2019
cs12xcm
Assignment 7

File Name:      Tree.java
Description:    The program will represent a Binary Tree, with a Tree node
		structure, that contains a root node with possible 
		children nodes to the left and right. Each node in the tree will 
		contain data and a pointer to the next node in the tree which may be
		a child or a parent. Nodes and data can be inserted, searched for and 
		removed from the tree. 
***************************************************************************/

/**
 * The Tree class will act as a Binary Tree to hold 
 * various left and right Nodes that will contain data. The data 
 * and nodes will be accessed via traversal of the tree. 	
 *
 * */
public class Tree<Whatever extends Base> extends Base {

	/* data fields */
	private TNode root;
	private long occupancy; 
	private String treeName;

	/* debug flag */
	private static boolean debug;

	/* debug messages */
	private static final String ALLOCATE = " - Allocating]\n";
	private static final String AND = " and ";
	private static final String COMPARE = " - Comparing ";
	private static final String INSERT = " - Inserting ";
	private static final String TREE = "[Tree ";

	/**
	 * 	the public constructor to initialize the data fields 
	 *
	 * @param  name		the name of the Tree 
	 *
	 * */
	public Tree (String name) {

		//initialize the private data variables 
		this.treeName = name;
		this.occupancy = 0;
		root = null;

		if(debug){

			System.err.println(TREE + treeName + ALLOCATE);
		}

	}
	
	/**
	 * turn off the debug  mode
	 *
	 */
	public static void debugOff () {

		//set debug to off
		debug = false;
	}
	
	/**
	 * turn on the debug mode 
	 *
	 */
	public static void debugOn () {

		//set the debug to on	
		debug = true;
	}

	/**
	 * Returns the tree's name
	 * @return name of the tree
	 *
	 */
	public String getName() {

		return treeName;
	}

	public boolean isEmpty () {

		if(this.occupancy == 0){
			return true;
		}

		return false;
	}
	
	/**
	 * this method will insert a new node into
	 * the tree with a data entry 
	 * 
	 * @param element the item to insert 
	 * @return true false
	 *
	 */
	public boolean insert (Whatever element) {

		//temp current working node
		TNode working = root;

		//loop conditions
		boolean found = false;
		boolean update = true;

		//local variables to help calculate the height and balances 
		long left_height = -1;
		long right_height = -1;
		long tallest_height = 1;


		//if this is the first TNode in the structure (null root)
		if(root == null){


			
			if(debug){

				System.err.println(TREE + treeName +
				INSERT + element.getName() + "]");
			}

			//create the first tree node 
			root = new TNode(element);

			return true;

		}


		//find the correct placement for the incoming element 
		else {

			while (!found){
				
					
				//duplicate insert
				if(element.equals(working.data)){

					//check if the element has already been deleted
					if(working.hasBeenDeleted){
						
						//resest the hasBeenDeleted tag
						working.hasBeenDeleted = false;
						
						//increse the occupancy
						occupancy++;
						
						
					}

					if(debug){

						System.err.println(TREE + treeName +
						INSERT + element.getName() + "]");
					}
						
					//replace the element in the current TNode
					working.data = element;

					found = true;
				}
			
				//if the element is greater than the current node
				else if(element.isGreaterThan(working.data)){

						
				if(debug){
						System.err.println(TREE + treeName +
						COMPARE + element.getName() + AND 
						+ working.data.getName() + "]");
				}


					//go right 
					if(working.right == null){

						if(debug){
							System.err.println(TREE + treeName +
							INSERT + element.getName() + "]");
						}

						//insert the new node into the tree
						working.right = new TNode(element);

						working.right.parent = working;

						found = true;
					}

					//increment the working node to the right 
					else{

						working = working.right;
					}

				}

				else {

					//go left
					if(working.left ==  null){

						if(debug){

							System.err.println(TREE + treeName +
							INSERT + element.getName() + "]");
						}

						//insert the new node on the left 
						working.left = new TNode(element);

						working.left.parent = working;

						found = true;
					}

					//increment the working node to the left 
					else{

						working = working.left;
					}
				}
			}
		}	

		//go back up the tree and correct the heights and balances
		while(update){

			//if the left child node is non-empty get the height 
			if(working.left != null){

				left_height = working.left.height;

			}

			//if the right child node is non-empty get the height 
			if(working.right != null){

				right_height = working.right.height;
			}

			//set the working nodes height 
			working.balance = left_height - right_height;

			//check for the tallest child node 	
			if(left_height > right_height){

				tallest_height = left_height;
			}

			else {

				tallest_height = right_height;
			}

			//increment the height of the working node 
			working.height = ++tallest_height;

			working = working.parent;

			//once the root is reached terminate loop
			if(working == null){

				update = false;
			}		
		}

		return true;
	}
	
	/**
	 * this method will search the Tree for 
	 * a specified element 
	 *
	 * @param element the item to search for 
	 * @return the data of the item or null
	 */
	public Whatever lookup (Whatever element) {

		//temp current working node
		TNode working = root;


		//if there isnt a root node yet
		if(root == null){

			return null;

		}

		//find the node and data matching the parameter
		else {

			while (true){
				
				//return null when the current node is null
				if(working == null){

					return null;
				}
				
				//return the data is the item matches
				if(element.equals(working.data)){
					
					//check if the data has been deleted 
					if(working.hasBeenDeleted){

						return null;
					}

					return working.data;

				}

				//check if the item is greate than or less than parameter 
				else if(element.isGreaterThan(working.data)){

						
				if(debug){

						System.err.println(TREE + treeName +
						COMPARE + element.getName() + AND 
						+ working.data.getName() + "]");
				}

					
					//shift to the right node down the tree
					working = working.right;

				}

				else{
					
					//shift to the left node down the tree 
					working = working.left;

				}
			}
		}	

	}
	
	/**
	 * this method will remove an element from 
	 * the Tree
	 *
	 * @param element the item to remove
	 * @return the data of the item removed
	 */
	public Whatever remove (Whatever element) {

	    //temp current working node
		TNode working = root;


		//if there isnt a root node yet
		if(root == null){

			return null;

		}

		//find the node and data matching the parameter
		else {

			while (true){
				
				//return null when the current node is null
				if(working == null){

					return null;
				}
				
				//return the data if the item matches
				if(element.equals(working.data)){
					
					//check if the element has been deleted already
					if(working.hasBeenDeleted){

						return null;
					}

					//shallow delete 
					working.hasBeenDeleted = true;
	
					--occupancy;

					return working.data;

				}

				//check if the item is greate than or less than parameter 
				else if(element.isGreaterThan(working.data)){
						
				if(debug){

						System.err.println(TREE + treeName +
						COMPARE + element.getName() + AND 
						+ working.data.getName() + "]");
				}

					
					//shift to the right node down the tree
					working = working.right;

				}

				else{
					
					//shift to the left node down the tree 
					working = working.left;

				}
			}
		}	

	}

	/**
	 * Creates a string representation of this tree. This method first
	 * adds the general information of this tree, then calls the
	 * recursive TNode function to add all nodes to the return string 
	 *
	 * @return  String representation of this tree 
	 */
	public String toString () {

		String string = "Tree " + treeName + ":\noccupancy is ";
		string += occupancy + " elements.";

		if(root != null)
			string += root.writeAllTNodes();

		return string;
	}
	
	/**
	 * the TNode inner class will serve as a new node 
	 * to be created within the Tree. The nodes will 
	 * hold data that can be obtained and manipulated 
	 * through function calls.
	 */
	private class TNode {
		
		//the data in the node and it's parents and children 
		public Whatever data;
		public TNode left, right, parent;
		public boolean hasBeenDeleted;

		/* left child's height - right child's height */
		public long balance;
		/* 1 + height of tallest child, or 0 for leaf */
		public long height;

		/**
		 * the constructor with a parameter to
		 * initialize the data fields and all 
		 * values relevant to the node in the tree
		 * @param element the item to store 
		 */
		public TNode (Whatever element) {

			//initialize the data variables to null and zero 
			this.data = element;
			this.left = null;
			this.right = null;
			this.parent = null;
			this.balance = 0;
			this.height = 0;
			this.hasBeenDeleted = false;

			//increment the occupancy a new node has been created
			occupancy++;

		}

		/**
		 * Creates a string representation of this node. Information
		 * to be printed includes this node's height, its balance,
		 * and the data its storing.
		 *
		 * @return  String representation of this node 
		 */

		public String toString () {
			return "at height:  " + height + "  with balance: " +
				balance + "  " + data;
		}

		/**
		 * Writes all TNodes to the String representation field. 
		 * This recursive method performs an in-order
		 * traversal of the entire tree to print all nodes in
		 * sorted order, as determined by the keys stored in each
		 * node. To print itself, the current node will append to
		 * tree's String field.
		 */
		public String writeAllTNodes () {
			String string = "";
			if (left != null)
				string += left.writeAllTNodes ();
			if (!hasBeenDeleted) 
				string += "\n" + this;          
			if (right != null)
				string += right.writeAllTNodes ();

			return string;
		}
	}
}
