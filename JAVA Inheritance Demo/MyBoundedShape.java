package assignment3;

import java.awt.Color;

/*
 * @author Priyanka
 */
public abstract class MyBoundedShape extends MyShape
{
    // This class is used to include Bounded Shape properties like length, height and fill Color.
    private int length; 
    private int width;
    private Color fillColor;
    
    public MyBoundedShape(int x1, int y1, int length, int width, Color color, Color fillColor)
    {
        super(x1, y1, color);
        this.length = length;
        this.width = width;
        this.fillColor = fillColor;
    }
    
    public int getLength()
    {
        return this.length;
    }
    public int getWidth()
    {
        return this.width;
    }
    
    public Color getfillColor()
    {
        return this.fillColor;
    }
}
