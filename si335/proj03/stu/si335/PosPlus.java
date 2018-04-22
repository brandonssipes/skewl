package si335;
import java.util.*;

/**
 * A class for representing a Pos + value , e.g. for "Food"
 */
public class PosPlus extends Pos			    
{
  private int val;

  /**
   * Constructs a PosPlus object from Pos p and value val
   */
  public PosPlus(Pos p, int val) { super(p); this.val = val; }

  /**
   * returns the value of this food object
   */
  public int getVal() { return val; }

  /**
   * Reads a new food item from scanner sc, e.g. "12 17 6" would produce (row=12,col=17),val=6.
   */
  public static PosPlus read(Scanner sc)
  {
    Pos p = Pos.read(sc);
    return new PosPlus(p,sc.nextInt());
  }

}
