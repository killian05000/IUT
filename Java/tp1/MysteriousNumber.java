import java.util.*;

public class MysteriousNumber
{
  public static void main (String [] args)
  {
    int c = (Integer.parseInt(args[0])+1;
    Scanner sc = new Scanner(System.in);
    int n=0;
    n = (int)(Math.random()*c);
    int life=5;

    System.out.print("Saisissez un nombre : ");
    int userValue = sc.nextInt();
    do
    {
      if (userValue>n)
      {
        life-=1;
        System.out.print("C'est trop grand, réessayez : ");
        userValue = sc.nextInt();
      }
      else if (userValue<n)
      {
        life-=1;
        System.out.print("C'est trop petit, réessayez : ");
        userValue = sc.nextInt();
      }
    } while (userValue!=n && life>0);
    if (life==0)
      System.out.println("Vous avez épuisé toutes vos vies, c'es perdu !");
    else if (userValue==n)
      System.out.println("Bravo, le nombre secret est bien "+n+" !");
  }
}
