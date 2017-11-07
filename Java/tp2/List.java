import java.util.Vector;
import java.util.*;

public class List
{
    public static void main(String []args)
    {
      Vector v = new Vector();
      //String tmp = v.elementAt(1);
      //System.out.println(v.elementAt(1));
      fillVector(v);
      displayVector(v);
    }

    public static void fillVector(Vector list)
    {
      Scanner sc = new Scanner(System.in);
      System.out.print("Combien de fois voulez vous afficher ? : ");
      int nb = sc.nextInt();
      for ( int i=0; i < nb; ++i)
      {
        System.out.print("Entrez le nom n°"+(i+1)+" : ");
        String tmp = sc.next();
        list.addElement(tmp);
      }
    }

    public static void displayVector(Vector list)
    {
      int nb = list.size();
      for ( int i=0; i < nb; ++i)
      {
        System.out.println(list.elementAt(i));
      }
    }
}
