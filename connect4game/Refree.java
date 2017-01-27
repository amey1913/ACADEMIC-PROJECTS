/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package connect4game;

/**
 *
 * @author Amey
 */
public class Refree implements Runnable
{
    
    // This class is careted to provide Referee Functionality and inplements 
    // Runnable interface for multithreading
    
    private final Board playBoard;
    
    public Refree(Board b)
    {
        playBoard = b;
    }
    
    @Override
    public void run()
    {
        playBoard.monitor_board(); // call monitor board method of Board class.
    }      
}
