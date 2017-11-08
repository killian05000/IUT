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
      //displayVector(v);
      //orderList(v);
      displayVector(v);
      deleteDuplicates(v);
      System.out.println();
      displayVector(v);
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
      System.out.println();
    }

    public static void displayVector(Vector list)
    {
      int nb = list.size();
      for ( int i=0; i < nb; ++i)
      {
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
      int nb = list.size();
      for ( int i=0; i < nb; ++i)
      {
        String tmp = (String)list.elementAt(i);
        for ( int k=1; k < nb; ++k)
        {
          String tmp2 = (String)list.elementAt(k);
          //System.out.println("2nd for i:"+i+" / k:"+k+" --> compare : "+list.elementAt(i)+" and "+list.elementAt(k));
          System.out.println("2nd for i:"+i+" / k:"+k+" --> compare : "+tmp+" and "+tmp2);
          if (tmp == tmp2)
          {
            System.out.println("i:"+i+" / k:"+k+" --> "+list.elementAt(k)+" is gonna be deleted");
            list.removeElementAt(k);
            System.out.println("i:"+i+" / k:"+k+" --> "+list.elementAt(k)+" replaced it");
            nb-=1;
          }
        }
      }
    }
}

// int nb = list.size();
// for ( int i=0; i < nb; ++i)
// {
//   String tmp = (String)list.elementAt(i);
//   //System.out.print(list.elementAt(i)+" with : ");
//   for ( int k=1; k < nb; ++k)
//   {
//     String tmp2 = (String)list.elementAt(k);
//     //System.out.print(list.elementAt(k)+" / ");
//     //System.out.println("bip i:"+i+" / k:"+k);
//     if (list.elementAt(i) == list.elementAt(k))
//     {
//       //System.out.println("bip i:"+i+" | k:"+k);
//       System.out.println("i:"+i+" / k:"+k+" --> "+list.elementAt(k));
//       list.removeElementAt(k);
//       System.out.println("i:"+i+" / k:"+k+" --> "+list.elementAt(k));
//     }
