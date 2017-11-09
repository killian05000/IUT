import java.util.Vector;
import java.util.*;

public class List
{
    public static void main(String []args)
    {
      Vector<String> v = new Vector<String>();

      boolean test=false;
      while (!test)
      {
        try
        {
        fillVector(v);
        test = true;
        }
        catch(InputMismatchException e)
        {
          System.out.println();
          System.out.println("Erreur de typage survenue !");
          System.out.println("---------Réessayez---------");
          System.out.println();
        }
      }

      System.out.println();
      System.out.print("Liste non ordonnée : ");
      displayVector(v);

      orderList(v);
      System.out.print("Liste ordonnée : ");
      displayVector(v);

      int size = v.size();
      deleteDuplicates(v);
      int newSize = v.size();
      if (newSize < size)
      {
      System.out.print("Liste sans doublon : ");
      displayVector(v);
      }
    }

    public static void fillVector(Vector list)
    {
      Scanner sc = new Scanner(System.in);
      System.out.print("Combien d'élements voulez vous entrer ? : ");
      int nb = sc.nextInt();
      System.out.println();
      for ( int i=0; i < nb; ++i)
      {
        System.out.print("Entrez le nom n°"+(i+1)+" : ");
        String tmp = sc.next();
        list.addElement(tmp);
      }
    }

    public static void displayVector(Vector list)
    {
      for ( int i=0; i < list.size(); ++i)
      {
        if (i == (list.size()-1))
          System.out.print(list.elementAt(i));
        else
          System.out.print(list.elementAt(i)+" / ");
      }
      System.out.println();
    }

    public static void orderList(Vector list)
    {
      Collections.sort(list);
    }

    public static void deleteDuplicates(Vector list)
    {
      for ( int i=0; i < list.size(); ++i)
      {
        for ( int k=0; k < list.size(); ++k)
        {
          if (((list.elementAt(i)).equals(list.elementAt(k))) && (k!= i))
          {
            list.removeElementAt(k);
          }
        }
      }
    }
}
