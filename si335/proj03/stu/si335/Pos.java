package si335;
import java.util.*;

/**
 * A class for representing row/column positions.
 */
public class Pos
{
  private int row, col;

  /**
   * Constructs a position from row r and column c.
   */
  public Pos(int r, int c) { row = r; col = c; }

  /**
   * Constructs a position from Pos p
   */
  public Pos(Pos p) { row = p.getRow(); col = p.getCol(); }

  /**
   * returns the row for this position.
   */
  public int getRow() { return row; }

  /**
   * returns the column for this position.
   */
  public int getCol() { return col; }

  /**
   * Returns a string representation, e.g. "12 28".
   */
  public String toString() { return row + " " + col; }

  /**
   * Tests for equality of row/col coordinates between two positions.
   */
  public boolean equals(Pos p) {
    return row == p.row && col == p.col; }

  /**
   * Tests for equaltiy of a Pos with an arbitraty object.
   * This is important for use in some collections.
   */
  public boolean equals(Object o)
  {
    try { return ((Pos)o).equals(this); } catch(Exception e) { return false; }
  }

  /**
   * Returns the "manhatttan distance" between "this" position and p.
   * This distance is the sum of the absolute values of the differences in
   * row coordinates and column cooridinates.
   */
  public int distance(Pos p)
  { return Math.abs(this.row - p.row) + Math.abs(this.col - p.col); }

  /**
   * Returns a new point whose row is the sum of this's row and p's row, and column likewise.
   * E.g.g (row=2,col=7) + (row=10,col=4) gives (row=12,col=11).
   */
  public Pos sum(Pos p) { return new Pos(row + p.row, col + p.col); }

  /**
   * Reads a new position from scanner sc, e.g. "12 17" would produce (row=12,col=17).
   */
  public static Pos read(Scanner sc)
  {
    int r = sc.nextInt();
    int c = sc.nextInt();
    return new Pos(r,c);
  }

  /**
   * Returns a hashcode for Pos objects that is OK for our Project3 application.
   * This allows for HashMap's and HashSet's of Pos objects.
   */
  public int hashCode()
  {
    int val = (row % 10000)*10000 + (col % 10000);
    return val;
  }
}
