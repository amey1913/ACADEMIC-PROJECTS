/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment3;

import java.awt.Color;
import java.awt.Graphics;
/**
 * @author Priyanka
 */
public class MyLine extends MyShape
{
    // This class is used to Create and manipulate the Line Shape.
    
    private int x2;
    private int y2;
    
    public MyLine(int x1, int x2, int y1, int y2, Color color)
    {
        super(x1, y1, color);
        this.x2 = x2;
        this.y2 = y2;
    }
    
    public double getLength()
    {
        // Calculates and returns Length of the Line
        double sq1, sq2, x, y, length;
        x = (double)this.getX2() - this.getX1();
        y = (double)this.getY2() - this.getY1();

        sq1 = Math.pow(x, 2);
        sq2 = Math.pow(y, 2);

        length = Math.sqrt(sq1 + sq2);
        
        return Math.round(length * 100.0) / 100.0;
    }
    
    private double getSlope()
    {
        // Calculates and returns Slope of the Line
        double x, y, slope;
        x = Math.abs((double)this.getX2() - this.getX1());
        y = Math.abs((double)this.getY2() - this.getY1());

        slope = y / x;
        
        return Math.round(slope * 100.0) / 100.0;
    }
    
    public int getX2()
    {
        return this.x2;
    }
    public int getY2()
    {
        return this.y2;
    }
    
    @Override
    public void draw(Graphics g)
    {
        // Overrrides the Draw method of MyShape Parent class to Draw a Line.
        g.setColor(super.getColor());
        g.drawLine(super.getX1(), super.getY1(), x2, y2);
        System.out.printf("<R, G, B>: <%d, %d, %d>\n"
                                            , super.getColor().getRed()
                                            , super.getColor().getGreen()
                                            , super.getColor().getBlue());
    }
    
    @Override
    public void print()
    {        
        // Overrrides the Print method of Printable Interface implemented by parent class
        // MyShape to Print Line Details.
         System.out.printf("\nLine Details:\n"
                    + "x1: %d, y1: %d, x2: %d, y2: %d\n"
                    + "Color <R, G, B>: <%d, %d, %d>\n"
                    + "Length: %.2f, Slope: %.2f\n"
                    , super.getX1(), super.getY1(), getX2(), getY2() 
                    , super.getColor().getRed(), super.getColor().getGreen()
                    , super.getColor().getBlue(), getLength(), getSlope());
    }
    
    @Override
    public int compareTo(Printable p)
    {
        // Overrrides the compareTo method of Comparaable Interface inplemented by parent class
        // MyShape to Compare other Shape Objects with line length.
        
        double val = 0.00;

        if(p instanceof MyLine)
        {
            MyLine line = (MyLine) p;
            val = line.getLength();
        }
        else if(p instanceof MyRectangle)
        {
            MyRectangle rect = (MyRectangle) p;
            val = rect.getArea();
        }
        else if(p instanceof MyOval)
        {
            MyOval oval = (MyOval) p;
            val = oval.getArea();
        }
        
        if (this.getLength() > val)
            return(1);
        else if (this.getLength() < val)
                return(-1);
           
        return(0);
    }
}
