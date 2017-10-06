import java.util.*;

public class Ldc
{
  public static void main(String [] args)
  {
    System.out.print("Il y a "+args.length+" arguments : ");
    for (int i=0; i < args.length; i++)
    {
      System.out.print(args[i]+" ");
    }
    System.out.println();
  }
}
