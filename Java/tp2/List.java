import java.util.*;

public class List
{
    public static void main(String []args)
    {
      Vector<String> v = new Vector<String>();

      fillVector(v);

      System.out.println();
      System.out.print("Unordered list : ");
      displayVector(v);

      orderList(v);
      System.out.print("Ordered list : ");
      displayVector(v);

      int size = v.size();
      deleteDuplicates(v);
      int newSize = v.size();
      if (newSize < size)
      {
      System.out.print("List without duplicates : ");
      displayVector(v);
      }
    }

    public static void fillVector(Vector list)
    {
      boolean test=false;
      while (!test)
      {
        try
        {
          Scanner sc = new Scanner(System.in);
          System.out.print("How many elements do you want to enter ? ");
          int nb = sc.nextInt();
          sc.nextLine();
          if (nb>0)
          {
            System.out.println();
            for ( int i=0; i < nb; ++i)
            {
              System.out.print("Enter the element n°"+(i+1)+" : ");
              String tmp = sc.nextLine();
              list.addElement(tmp);
            }
            test = true;
          }
        }
        catch(InputMismatchException e)
        {
          System.out.println();
          System.out.println("A data type error have been occured !");
          System.out.println("--------------Try again--------------");
          System.out.println();
        }
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
      int nbDuplicates =0;
      for ( int i=0; i < list.size(); ++i)
      {
        for ( int k=0; k < list.size(); ++k)
        {
          if (((list.elementAt(i)).equals(list.elementAt(k))) && (k!= i))
          {
            list.removeElementAt(k);
            nbDuplicates++;
          }
        }
      }
      System.out.println("There is "+nbDuplicates+" duplicates");
    }
}
