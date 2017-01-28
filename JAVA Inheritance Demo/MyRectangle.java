package assignment3;

import java.awt.Color;
import java.awt.Graphics;

/*
 * @author Amey
 */
public class MyRectangle extends MyBoundedShape
{
    // This class is used to Create and manipulate Rectangle Shape.
    
    public MyRectangle(int x1, int y1, int length, int width,  Color color, Color fillColor)
    {
        super(x1, y1, length, width, color, fillColor);
    }

    public double getArea()
    {
        // calculates the Area of a rectangle
        double area;
        area = super.getLength() * super.getWidth();
        
        return Math.round(area * 100.0) / 100.0;
    }
    
    public double getPerimeter()
    {
        // calculates the Perimeter of a rectangle
        double perimeter;
        perimeter = 2 * (super.getLength() + super.getWidth());
        
        return Math.round(perimeter * 100.0) / 100.0;
    }
    
        

    @Override
    public void draw(Graphics g)
    {
        // Overrrides the Draw method of MyShape Parent class to draw a Rectangle.
        
        g.setColor(super.getColor());
        g.drawRect(super.getX1(), super.getY1(), super.getLength(), super.getWidth());
        
        g.setColor(super.getfillColor());
        g.fillRect(super.getX1(), super.getY1(), super.getLength(), super.getWidth());
        
        System.out.printf("<R, G, B>: <%d, %d, %d>\n"
                                            , super.getColor().getRed()
                                            , super.getColor().getGreen()
                                            , super.getColor().getBlue());
        System.out.printf("<R, G, B>: <%d, %d, %d>\n"
                                            , super.getfillColor().getRed()
                                            , super.getfillColor().getGreen()
                                            , super.getfillColor().getBlue());
    }
    
    @Override
    public void print()
    {
        // Overrrides the Print method of Printable Interface implemented by parent class
        // MyShape to Print Rectangle Details.
        
        System.out.printf("\nRectangle Details:\n"
                + "x1: %d, y1: %d, Length: %d, Width: %d\n"
                + "Color <R, G, B>: <%d, %d, %d>\n"
                + "Area: %.2f, Perimeter: %.2f\n"
                , super.getX1(), super.getY1(), getLength(), getWidth() 
                , super.getColor().getRed(), super.getColor().getGreen()
                , super.getColor().getBlue(), getArea(), getPerimeter());
    }
    
    @Override
    public int compareTo(Printable p)
    {
        // Overrrides the compareTo method of Comparaable Interface implemented by parent class
        // MyShape to Compare other Shape Object with Rectangle Area.
        
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
        
        if (this.getArea() > val)
            return(1);
        else if (this.getArea() < val)
                return(-1);
           
        return(0);
    }
}