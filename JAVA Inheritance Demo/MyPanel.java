package assignment3;

import java.awt.Color;
import java.awt.Graphics;
import java.security.SecureRandom;
import javax.swing.JPanel;

/*
 * @author Amey
 */

public class MyPanel extends JPanel
{
    
    // This class is used to Create Panel Class used to draw all Shapes.
    
    private SecureRandom randNo = new SecureRandom();   //Used for generating random numbers.
    private MyLine[] lines;
    private MyRectangle[] rects;
    private MyOval[] ovals;
    private int numberOfShapes;
    
    int x1, y1, x2, y2;
    Color color, fillColor;
    
    public MyPanel()
    {
        setBackground(Color.WHITE);
        numberOfShapes = 7; //Max number of individual shapes to be generated.

        lines = new MyLine[randNo.nextInt(numberOfShapes) + 1];
        rects = new MyRectangle[randNo.nextInt(numberOfShapes) + 1];
        ovals = new MyOval[randNo.nextInt(numberOfShapes) + 1];
        
        for(int counter = 0; counter < lines.length; counter++)
        {
            x1 = randNo.nextInt(100) + 1;
            y1 = randNo.nextInt(100) + 1;
            x2 = randNo.nextInt(400) + 1;
            y2 = randNo.nextInt(400) + 1;
            
            color = new Color(randNo.nextInt(255), randNo.nextInt(255), randNo.nextInt(255));

            lines[counter] = new MyLine(x1, y1, x2, y2, color); //Creates line objects array
        }
        
        for(int counter = 0; counter < rects.length; counter++)
        {
            x1 = randNo.nextInt(200);
            y1 = randNo.nextInt(200);
            x2 = randNo.nextInt(100);
            y2 = randNo.nextInt(100);
            
            color = new Color(randNo.nextInt(255), randNo.nextInt(255), randNo.nextInt(255));
            fillColor = new Color(randNo.nextInt(255), randNo.nextInt(255), randNo.nextInt(255));

            rects[counter] = new MyRectangle(x1, y1, x2, y2, color, fillColor); //Creates rectangle objects array
        }
        
        for(int counter = 0; counter < ovals.length; counter++)
        {
            x1 = randNo.nextInt(300);
            y1 = randNo.nextInt(300);
            x2 = randNo.nextInt(100);
            y2 = randNo.nextInt(100);
            
            color = new Color(randNo.nextInt(255), randNo.nextInt(255), randNo.nextInt(255));
            fillColor = new Color(randNo.nextInt(255), randNo.nextInt(255), randNo.nextInt(255));

            ovals[counter] = new MyOval(x1, y1, x2, y2, color, fillColor);  //Creates oval objects array
        }
    }
    
    public void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        int counter, maxR, minR, maxG, minG, maxB, minB;
       
        maxR = 0; 
        minR = 0; 
        maxG = 0;
        minG = 0;
        maxB = 0; 
        minB = 0;
        
        // Creates Printable object array of length which is total of lines + rectangles + ovals
        Printable[] p = new Printable[lines.length + rects.length + ovals.length];
       
        // Fills up Printable array.
        for(counter = 0; counter < lines.length; counter++)
        {
            p[counter] = lines[counter];
        }
        
        for(counter = lines.length; counter < lines.length + rects.length; counter++)
        {
            p[counter] = rects[counter - lines.length];
        }

        for(counter = (lines.length + rects.length); 
                counter < lines.length + rects.length + ovals.length; counter++)
        {
            p[counter] = ovals[counter - (lines.length + rects.length)];
        }
        
        p = sortArray(p);   //Calls sortArray method to sort the Printable array.      
         
        System.out.printf("Generated Colors:\n");
     
        for(Printable currentShape : p)    
        { 
            MyShape s = (MyShape) currentShape;
            s.draw(g);
            // Calculates Min and Max for Generated Colors.
            maxR = getGreater(maxR, s.getColor().getRed());
            maxG = getGreater(maxG, s.getColor().getGreen());
            maxB = getGreater(maxB, s.getColor().getBlue());

            minR = getLesser(minR, s.getColor().getRed());
            minG = getLesser(minG, s.getColor().getGreen());
            minB = getLesser(minB, s.getColor().getBlue());
            if(s instanceof MyOval || s instanceof MyRectangle)
            {
                MyBoundedShape bs = (MyBoundedShape) currentShape;
                
                // Calculates Min and Max for Generated Fill Colors.
                maxR = getGreater(maxR, bs.getfillColor().getRed());
                maxG = getGreater(maxG, bs.getfillColor().getGreen());
                maxB = getGreater(maxB, bs.getfillColor().getBlue());

                minR = getLesser(minR, bs.getfillColor().getRed());
                minG = getLesser(minG, bs.getfillColor().getGreen());
                minB = getLesser(minB, bs.getfillColor().getBlue());
            }
        }  
        
        System.out.printf("Colors Summary:\n"
                + "The Range of Color Red was from %d to %d.\n"
                + "The Range of Color Green was from %d to %d.\n"
                + "The Range of Color Blue was from %d to %d.\n"
                , minR, maxR, minG, maxG, minB, maxB);
        
        for(Printable currentShape : p)  
        { 
            currentShape.print();   //Calls Print Method for all objects.
        }            
    }
        
    private int getGreater(int x, int y)
    {
        //Returns Greater number in x and y.
        int ret;
        
        if(x < y)
        {
            ret = y;
        }
        else
        {
            ret = x;
        }
        
        return ret;
    }
    
    private int getLesser(int x, int y)
    {
        //Returns Lesser number in x and y.
        int ret;
        
        if(x == 0)
        {
            ret = y;
        }
        else
        {
            if(x > y)
            {
                ret = y;
            }
            else
            {
                ret = x;
            }
        }
        return ret;
    }
    
    private Printable[] sortArray(Printable[] p)  
    {
        // Following logic is used to sort the Printable array using Insertion Sort Algorithm.
        int j, i;  
        Printable temp; 

        for (j = 1; j < p.length; j++) 
        {
            temp = p[j];
            MyShape s = (MyShape) temp;
                
            for(i = j - 1; (i >= 0) && (s.compareTo(p[i]) == -1); i--) //Calls Compare to method of Comparable Interface.
            {
                    p[ i+1 ]  = p[ i ];
            }
            p[ i+1 ] = temp;
        }
        
        return p;   // Returns a Sorted Array.
    }
}
