import java.util.*;

public class List
{
  public static void main(String[] args)
  {
    List = new Vector();
    //Scanner sc = new Scanner(System.in);
    fillVector();
  }

  public static void fillVector()
  {
    Scanner sc = new Scanner(System.in);
    System.out.print("Saisissez des noms : ");
    String nom = sc.next();
    String nom2 = sc.next();
    System.out.println(nom+" et "+nom2);
  }
}
