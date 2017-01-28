package assignment3;

import javax.swing.JFrame;

/*
 * @author Amey
 */

public class Assignment3 
{
    
    // This is a main class used to Create a Frame and Add the Panel to the frame.
    public static void main(String[] args) 
    {
        MyPanel panel = new MyPanel();  //Initializing MyPanel Class object
        JFrame app = new JFrame(); //Initializing JFrame Class object
        app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
        app.add(panel); //Adding Panel Object to JFrame 
        app.setSize(700, 700);
        app.setVisible(true);
    }
}
