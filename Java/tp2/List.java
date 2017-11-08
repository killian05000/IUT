import java.util.Vector;
import java.util.*;

public class List
{
    public static void main(String []args)
    {
      Vector<String> v = new Vector<String>();
      //String tmp = v.elementAt(1);
      //System.out.println(v.elementAt(1));
      fillVector(v);
      displayVector(v);
      deleteDuplicates(v);
      displayVector(v);
    }

    public static void fillVector(Vector list)
    {
      Scanner sc = new Scanner(System.in);
      System.out.print("Combien d'élements voulez vous entrer ? : ");
      int nb = sc.nextInt();
      for ( int i=0; i < nb; ++i)
      {
        System.out.print("Entrez le nom n°"+(i+1)+" : ");
        String tmp = sc.next();
        list.addElement(tmp);
      }
      System.out.println();
    }

    public static void displayVector(Vector list)
    {
      int nb = list.size();
      for ( int i=0; i < nb; ++i)
      {
        System.out.println(list.elementAt(i));
      }
      System.out.println();
    }

    public static void deleteDuplicates(Vector list)
    {
      int nb = list.size();
      for ( int i=0; i < nb; ++i)
      {
        String tmp = (String)list.get(i);
        for ( int k=0; k < nb; k++)
        {
          String tmp2 = (String)list.get(i);
          if ((tmp == tmp2) && (list.indexOf(tmp) != list.indexOf(tmp2)))
          {
            list.removeElementAt(k);
          }
        }
      }
    }
}
