/****************************************************************************

Matthew Roth, A15685519
CSE 12, Winter 2019
February 19, 2019
cs12xcm
Assignment 7

File Name:      Driver.java

Description:    The driver will implement and demonstrate the Tree 
	program. The Driver has an inner class UCSDStudent to test the
	Tree program. 
***************************************************************************/

import java.io.*;

/**
 * This class will test the Tree program. The main
 * data fields are the name and the student number. 
 */
class UCSDStudent extends Base {
		
		//the name of the student and number for student 
        private String name;
        private long studentnum;
		
		/**
		 * the constructor to take name and student
		 * number as parameters
		 */
        public UCSDStudent (String nm, long stunum) {
                name = new String (nm);
                studentnum = stunum;
        }
		
		/**
		 * 
		 *	return the name of the student
		 */
        public String getName () {
                return name;
        }
		
		/**
		 * the equals method to compare objects 
		 * of the UCSDStudent type 
		 *
		 */
        public boolean equals (Object object) {
		
		//check if the object is same type as this
		if (this == object)
			return true;
		
		//check if instanceof UCSDStudent  		
		if (!(object instanceof UCSDStudent))
			return false;
		
		//cast to a UCSDStudent 
		UCSDStudent otherVar = (UCSDStudent) object;
		
		return name.equals (otherVar.getName ());

        }
		
		/**
		 * this method will check which name is 
		 * higher precedence
		 *
		 */
        public boolean isGreaterThan (Base base) {
                return (name.compareTo (base.getName ()) > 0) ? true : false;
        }

		/**
		 * the toString method to return a string 
		 * representation of the object
		 *
		 */
        public String toString () {
                return "name:  " + name + "  studentnum:  " + studentnum;
        }
}

//PROVIDED CODE BELOW
public class Driver {
        private static final short NULL = 0;

        public static void main (String [] args) {
        
                /* initialize debug states */
                Tree.debugOff();

                /* check command line options */
                for (int index = 0; index < args.length; ++index) {
                        if (args[index].equals("-x"))
                                Tree.debugOn();
                }


                /* The real start of the code */
                SymTab<UCSDStudent> symtab = 
                                new SymTab<UCSDStudent>("UCSDStudentTree");
                String buffer = null;
                char command;
                long number = 0;

                System.out.println ("Initial Symbol Table:\n" + symtab);

                while (true) {
                        command = NULL; // reset command each time in loop
                        System.out.print ("Please enter a command:  " + 
                                "((a)llocate, is(e)mpty, (i)nsert, (l)ookup,"+
                                " (r)emove, (w)rite):  ");

                        try {
                        command = MyLib.getchar ();
                        MyLib.clrbuf (command); // get rid of return

                        switch (command) {
                        case 'a':
                                System.out.print
                                ("Please enter name of new Tree to " +
                                 "allocate:  ");
                                
                                buffer = MyLib.getline ();// formatted input
                                symtab = new SymTab<UCSDStudent>(buffer);
                                break;
			case 'e':
				if(symtab.isEmpty()){
					System.out.println("Tree is empty.");
				} else {
					System.out.println("Tree is "+
						"not empty.");
				}
				break;

                        case 'i':
                                System.out.print
                                ("Please enter UCSD student name to insert:  ");

                                buffer = MyLib.getline ();// formatted input

                                System.out.print
                                        ("Please enter UCSD student number:  ");

                                number = MyLib.decin ();
                                MyLib.clrbuf (command); // get rid of return

                                // create student and place in symbol table
                                symtab.insert(new UCSDStudent (buffer, number));
                                break;

                        case 'l': { 
                                UCSDStudent found;      // whether found or not

                                System.out.print
                                ("Please enter UCSD student name to lookup:  ");
                                buffer = MyLib.getline ();// formatted input

                                UCSDStudent stu = new UCSDStudent (buffer, 0);
                                found = symtab.lookup (stu);
                                
                                if (found != null) {
                                        System.out.println("Student found!");
                                        System.out.println(found);
                                }
                                else
                                        System.out.println ("student " + buffer
                                                + " not there!");
                                }
                                break;
                        
                        case 'r': { 
                                UCSDStudent removed; // data to be removed

                                System.out.print
                                ("Please enter UCSD student name to remove:  ");

                                buffer = MyLib.getline ();

                                UCSDStudent stu = new UCSDStudent (buffer, 0);

                                removed = symtab.remove(stu);

                                if (removed != null) {
                                        System.out.println("Student removed!"); 
                                        System.out.println(removed);
                                }
                                else
                                        System.out.println ("student " + buffer
                                                + " not there!");
                                }
                                break;

                        case 'w':
                                System.out.println("The Symbol Table " +
                                "contains:\n" + symtab);
                        }
                        }
                        catch (EOFException eof) {
                                break;
                        }
                }
                System.out.println("\nFinal Symbol Table:\n" + symtab);
        }
}
