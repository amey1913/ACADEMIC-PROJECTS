package assignment3;

import java.awt.Color;
import java.awt.Graphics;
/*
 * @author Amey
 */
public abstract class MyShape implements Printable, Comparable<Printable>
{
    // This is Parent Class that implements Printable, Comparable interfaces.
    // Comparable interface is used to compare to Printable Objects
    
    private int x1;
    private int y1;
    private Color color;
    
    public MyShape(int x1, int y1, Color color)
    {
        this.x1 = x1;        
        this.y1 = y1;
        this.color = color;        
    }
    public int getX1()
    {
        return x1;
    }
    public int getY1()
    {
        return y1;
    }
    
    public Color getColor()
    {
        return color;
    }
    
    // The abstract draw method is declared to be implemented by other Shape Classes.
    public abstract void draw(Graphics g);
}
