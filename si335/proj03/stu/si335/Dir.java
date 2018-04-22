package si335;
import java.util.*;

/* NOTE: Bug fix of 5/3/17 - fixed getMoveTowards to return 'B' when it has to make a 180 */

/**
 * This class represents a compass direction, i.e. N, E, S, W
 */
public class Dir
{
  /**
   * Construct a Dir object.
   * @param dir The direction as character N, E, S or W.
   */
  public Dir(char dir) { mydir = char2int(dir); }

  
  /**
   * Read a Dir object (as N,E,S,W) from Scanner.
   * @param sc The scanner the direction character is read from.
   */
  public static Dir read(Scanner sc) { String s = sc.next(); return new Dir(s.charAt(0)); }

  /**
   * Returns the position resulting from one step in this direction from position p.
   * @param p The point that the one step starts from.
   */
  public Pos stepFrom(Pos p) { return step(p,mydir); }

  /**
   * Returns a "move" (i.e. L=left, R=right, F=forwards, B=backwards) that gets you closer to the target.
   * @param mypos The position you're currently at.
   * @param target The position you'd like to get to.
   * @return a "move" (i.e. L=left, R=right, F=forwards, B=backwards) that you could 
   *         make given your current direction (this) and position (mypos) that would get you
   *         closer to the target.
   */
  public char getMoveTowards(Pos mypos, Pos target)
  {
    return dirTowards(mypos,int2char(this.mydir),target);
  }

  public char moveToFace(char dir)
  {
    int target = char2int(dir);
    if (mydir == target) return 'F';
    else if ((mydir + 1) % 4 == target) return 'R';
    else if ((mydir + 2) % 4 == target) return 'B';
    else if ((mydir + 3) % 4 == target) return 'L';
    return 'F';
  }
  
  /** 
   * Returns the direction you would be heading after making "move" from the current direction.
   * @param move One of L=left, R=right, F=forwards, B=backwards.
   */
  public Dir turn(char move) { return new Dir(turn(this.mydir,move)); }

  /**
   * Represents the direction as one of the strings "N", "E", "S", or "W".
   */
  public String toString() { return "" + int2char(mydir); }


  
  private static Pos[] delta = { new Pos(-1,0), new Pos(0,1), new Pos(1,0), new Pos(0,-1) };
  private static char[] dir2char = { 'N', 'E', 'S', 'W' };

  private int mydir;
  private Dir(int dir) { mydir = int2int(dir); }
  

  public static int char2int(char c)
  {
    return (c == 'N' ? 0 : (c == 'E' ? 1 : (c == 'S' ? 2 : 3)));
  }
  private static int int2int(int i) { return i >= 0 ? i % 4 : 4 + (i%4); }
  public static char int2char(int i)
  {
    return dir2char[int2int(i)];
  }
  private static Pos step(Pos p, int dir) { return p.sum(delta[int2int(dir)]); }
  private static Pos step(Pos p, char dir) { return p.sum(delta[char2int(dir)]); }
  private static int turn(int dir, char turnDir)
  {
    if (turnDir == 'F') return int2int(dir);
    if (turnDir == 'R') return int2int(dir + 1);
    if (turnDir == 'B') return int2int(dir + 2);
    if (turnDir == 'L') return int2int(dir + 3);
    return char2int(turnDir);
  }
  private static int turn(char dir, char turnDir)
  {
    return turn(char2int(dir),turnDir);
  }

  private static char dirTowards(Pos mypos, char mydir, Pos target)
  {
    int dr = Math.abs(mypos.getRow() - target.getRow());
    int dc = Math.abs(mypos.getCol() - target.getCol());
    char tdir;
    if (dr > dc)
      tdir = mypos.getRow() > target.getRow() ? 'N' : 'S';
    else
      tdir = mypos.getCol() > target.getCol() ? 'W' : 'E';
    int m = char2int(mydir), t = char2int(tdir);
    if (m == t) return 'F';
    else if ((m + t) % 4 == 2) return 'B';
    else if ((m + 1) % 4 == t) return 'R';
    else return 'L';
  }


  // public static void main(String[] args)
  // {
  //   for(int i = 0; i < 4; i++)
  //     System.out.print(int2char(i) + " ");
  //   System.out.println();
  //   for(int i = 0; i < 4; i++)
  //     System.out.print(char2int(int2char(i)) + " ");
  //   System.out.println();

  //   String s = "LFRBNSEW";
  //   for(int i = 0; i < 4; i++)
  //     for(int j = 0; j < s.length(); j++)
  // 	;
  // }
}
