import java.util.*;
import si335.*;

public class Greedy
{
  public static void main(String[] args) throws Exception
  {
    Scanner sc = new Scanner(System.in);
    Greedy brain = new Greedy();
    brain.readPreamble(sc);
    ArrayList<Pos> path = brain.planPath();
    brain.playGame(sc,path);
  }
  
  private ArrayList<PosPlus> food;
  private int rows, cols, dur, len;
  private Dir mydir;
  private Pos mypos = null;
  private ShortestPathOracle BLANK;

  public Greedy()
  {
    food = new ArrayList<PosPlus>();    
    BLANK = new ShortestPathOracle();
  }

  /**
   * readPreamble(sc) - reads (and to some extent processes) all server messages
   * up to and including the "start" message.
   */
  public void readPreamble(Scanner sc)
  {
    Pos p;
    int k;
    while(mypos == null)
    {
      String op = sc.next();
      switch(op.charAt(0))
      {
      case 'g': // "game" message
	rows = sc.nextInt();
	cols = sc.nextInt();
	dur = sc.nextInt();
	len = sc.nextInt();
        BLANK.setBoardSize(rows, cols);
	break;
      case 'r': // "right" barrier (my greedy just ignores this!)
	p = Pos.read(sc);
	k = sc.nextInt();
        BLANK.addBarrier('r', p, k);
	break;
      case 'd': // "down" barrier (my greedy just ignores this!)
	p = Pos.read(sc);
	k = sc.nextInt();
        BLANK.addBarrier('d', p, k);
	break;
      case 'o': // "food" (use a PolsPlus where val = food value)
	food.add(PosPlus.read(sc));
	break;
      case 's': // "start" i.e. get my position & directionx
	mypos = Pos.read(sc);
	mydir = Dir.read(sc);
      break;
      }
    }
  }

  /**
   * findBest - find the closest unvisited food.
   * Specifically, return array [ibest,bestDist], where "ibest" is the index
   * in the food array of the element that is the closest "unvisited" food
   * position.  "bestDist" is the distance from "curr" to this food position.
   */
  int[] findBest(Pos curr, boolean[] visited, int N)
  {
    int ibest = -1, bestDist = 99999999;
    for(int j = 0; j < N; j++)
      if (!visited[j])
      {
        int nextDist = BLANK.getLengthOfShortestPath(curr, food.get(j));
	//int nextDist = curr.distance(food.get(j)); // "manhattan distance"!!!
	if (nextDist < bestDist)
	{
	  ibest = j;
	  bestDist = nextDist;
	}
      }

    return new int[] {ibest,bestDist};
  }
  
  /**
   * planPath - returns a "path" consistin of the food locations we plan
   * to visit, in order.  Here this is done by a simple greedy algorithm
   * that chooses the "next" food location to visit by choosing the unvisited
   * food location that is closest to the "current" location.
   */
  public ArrayList<Pos> planPath()
  {
    // visited[i] tells us whether food[i] has been "visited" by our path
    int N = food.size();
    boolean[] visited = new boolean[N];
    for(int i = 0; i < N; i++)
      visited[i] = false;

    ArrayList<Pos> path = new ArrayList<Pos>();
    Pos curr = mypos;
    int length = 0;
    for(int i = 0; i < N; i++)
    {
      // find the "best" (i.e. closest) unvisited food best[0] = index of best, best[1] = distance
      int[] best = findBest(curr,visited,N);
      length += best[1]; 
      if (length > dur) break;
      
      // the "best" food location becomes the next location in the path (and our new current location)
      curr = food.get(best[0]);
      path.add(curr);
      visited[best[0]] = true;
    }
    return path;
  }

  /**
   * playGame(sc,path) - interacts with the server to "play" the game.  In this case, we follow a
   * predetermined path consisting of the food locations we want to visit, in the order we want to
   * visit them.
   */
  public void playGame(Scanner sc, ArrayList<Pos> path) throws Exception
  {
    int i_target = 0, lastAck = 0;
    char move;
    while(true)
    {
      char op = sc.next().charAt(0);
      switch(op)
      {
      case 'k': // "Ack" 0:sucess, >0:sucess & got food (number is value), -1:fail - hit wall, -2:faile - hit worm
	lastAck = sc.nextInt();
	if (lastAck >= 0)
	  mypos = mydir.stepFrom(mypos);
	if (i_target < path.size() && mypos.equals(path.get(i_target)))  // if we've reached the current target, move to the next
	  i_target++;
	break;
      case 'x': // "x" a piece of food was eaten - maybe by you, maybe not
	food.remove(Pos.read(sc));
	break;
      case 'm': // "move" the server asked us to make a move
	int round = sc.nextInt();
	if (lastAck < 0)
	  move = 'R'; // if the way ahead is blocked, turn right!
	else if (food.size() == 0 || i_target >= path.size())
	  move = 'F'; // if no food remains or finished with path, charge ahead!
	else
          move = BLANK.getFirstMoveOnShortestPath(mypos, mydir, path.get(i_target));
	  //move = mydir.getMoveTowards(mypos,path.get(i_target)); // move towards the current target
	mydir = mydir.turn(move); // update direction based on the turn
	System.out.println(move); // send our move back to the server
	break;
      case 'w': // "worm" - tells us the head of worm "id" is at position p (my greedy just ignores this!)
	Pos p = Pos.read(sc);
	int id = sc.nextInt();
	break;
      default: // the server said something we don't understand!
	throw new Exception("Unknown op '" + op + "' from server!");
      }
    }
  }
}
