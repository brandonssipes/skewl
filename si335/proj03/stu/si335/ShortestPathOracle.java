package si335;
import java.util.*;
import java.lang.*;

/**
 * This class provides methods for computing distance and shortest
 * paths on wormworld boards that actually take the barriers into
 * account.
 */
public class ShortestPathOracle
{
  private boolean[][] board;
  private int rows = -1, cols;

  /**
   * Initializes the ShortestPathOracle to the given board dimensions.
   * @param rows Number of rows on board.
   * @param cols Number of cols on board.
   */
  public void setBoardSize(int rows, int cols)
  {
    this.rows = rows;
    this.cols = cols;
    board = new boolean[rows][cols];
    for(int i = 0; i < rows; i++)
      for(int j = 0; j < cols; j++)
	board[i][j] = false;
  }

  /**
   * Notify ShortestPathOracle of a barrier.
   * @param kind Either 'r' or 'd', the two kinds of barriers in the game.
   * @param p The start position of the barrier.
   * @param len The length of the barrier.
   */
  public void addBarrier(char kind, Pos p, int len)
  {
    if (rows == -1) throw new RuntimeException("ShortestPathOracle's setBoardSize must be called before any other method!");
    int r = p.getRow();
    int c = p.getCol();
    if (kind == 'r')
      for(int i = 0; i < len; i++)
	board[r][c + i] = true;
    else
      for(int i = 0; i < len; i++)
	board[r + i][c] = true;
  }

  
  private boolean isLegal(Pos p)
  {
    int r = p.getRow(), c = p.getCol();
    return 0 <= r && r < rows && 0 <= c && c < cols && !board[r][c];
  }
  
  
    // return distance and first move
  private class DistMove { int dist; char move; public DistMove(int d, char m) { dist = d; move = m; } }
  private class DistPos extends Pos
  {
    public int dist;
    char moveFromParent;
    public DistPos(Pos p, int d, char c)
    {
      super(p);
      dist = d;
      moveFromParent = c;
    }
    public  DistPos move(char dir)
    {
      Dir d = new Dir(dir);
      return new DistPos(d.stepFrom(this),this.dist+1,dir);
    }
  }

  /**
   * Returns the length of the shortest path from position curr to position target.
   */
  public int getLengthOfShortestPath(Pos curr, Pos target)
  {
    if (rows == -1) throw new RuntimeException("ShortestPathOracle's setBoardSize must be called before any other method!");
    char[] p = getShortestPath(curr,target);
    return p == null ? 99999999 : p.length;
  }

  /**
   * Returns the first "move" on a shortest path.
   * Specifically, starting from position mypos and direction mydir, returns the first
   * move (L,R,F,B) on a shortest path to position target.
   */
  public char getFirstMoveOnShortestPath(Pos mypos, Dir mydir, Pos target)
  {
    if (rows == -1) throw new RuntimeException("ShortestPathOracle's setBoardSize must be called before any other method!");
    char[] p = getShortestPath(mypos,target);
    if (p == null)
      return 'F';
    return mydir.moveToFace(p[0]);    
  }

  /**
   * Returns a shortest path from position curr to position target.
   * The returned path is an array of compass direction steps (i.e. N,E,S,W) to
   * get from curr to target.  Note that if you are at curr and pointing in dirction
   * Dir mydir, then mydir.moveToFace(cdir), where cdir is a compass direction, gives
   * the "move" L,R,F,B you would take to go in direction cdir.
   */ 
  public char[]  getShortestPath(Pos curr, Pos target)
  {
    if (rows == -1) throw new RuntimeException("ShortestPathOracle's setBoardSize must be called before any other method!");
    if (curr.equals(target)) throw new RuntimeException("ShortestPathOracle error! curr and target are the same!");
    if (!isLegal(target))
    {
      return null;
    }
    HashMap<DistPos,DistPos> parent = new HashMap<DistPos,DistPos>();
    Queue<DistPos> Q = new LinkedList<DistPos>();
    DistPos root = new DistPos(curr,0,'X');
    Q.add(root);
    parent.put(root,root);
    DistPos goal = null;
    while(!Q.isEmpty())
    {
      DistPos x = Q.remove();
      if (target.equals(x)) { goal = x; break; } 
      DistPos[] candidate = { x.move('N'), x.move('E'), x.move('S'), x.move('W') };
      for(int i = 0; i < 4; i++)
	if (isLegal(candidate[i]) && !parent.containsKey(candidate[i]))
	{
	  Q.add(candidate[i]);
	  parent.put(candidate[i],x);
	}
    }
    if (goal == null)
      return null;
    char[] res = new char[goal.dist];
    DistPos now = goal;
    while(now.moveFromParent != 'X')
    {
      res[now.dist - 1] = now.moveFromParent;
      now = parent.get(now);
    }
    return res;
  }
}
