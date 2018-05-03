package si335;
import java.util.*;
import java.lang.*;

public class Memo extends ShortestPathOracle{
  private char[][][][][] Cubert;
  public void setBoardSize(int rows, int cols){
    super.setBoardSize(rows, cols);
    Cubert = new char[rows][cols][rows][cols][];
  }
  public int getLengthOfShortestPath(Pos curr, Pos target){
    int r1 = curr.getRow();
    int c1 = curr.getCol();
    int r2 = target.getRow();
    int c2 = target.getCol();
    char[] p = Cubert[r1][c1][r2][c2];
    if (p != null){
      //System.err.print("Path is already known and is ");
      //for(int i = 0; i < p.length; ++i)
        //System.err.print(p[i]);
      //System.err.println();
      return p.length;
    }
    p = getShortestPath(curr, target);
    //System.err.println("Path was not already known and is " + p.length);
    Cubert[r1][c1][r2][c2] = p;
    Cubert[r2][c2][r1][c1] = reverse(p);
    return p.length;
  }

  private char[] reverse(char[] path){
    char[] newPath = new char[path.length];
    for(int i=0,j=path.length-1; i<path.length; ++i,--j){
      if(path[i] == 'N')
        newPath[j] = 'S';
      else if(path[i] == 'E')
        newPath[j] = 'W';
      else if(path[i] == 'S')
        newPath[j] = 'N';
      else
        newPath[j] = 'E';
    }

    return newPath;
  }

  public char getFirstMoveOnShortestPath(Pos mypos, Dir mydir, Pos target){
    int r1 = mypos.getRow();
    int c1 = mypos.getCol();
    int r2 = target.getRow();
    int c2 = target.getCol();
    char[] p = getShortestPath(mypos, target);
    Cubert[r1][c1][r2][c2] = p;
    Cubert[r2][c2][r1][c1] = reverse(p);
    if (p == null)
      return 'F';
    //System.err.print("Path is already known and is ");
    //for(int i = 0; i < p.length; ++i){
    //  System.err.print(p[i]);
    //}
    //System.err.println();
    return mydir.moveToFace(p[0]);
  }
}
