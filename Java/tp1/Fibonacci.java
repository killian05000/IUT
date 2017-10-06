import java.util.*;

public class Fibonacci
{
  public static void main (String [] arg)
  {
    System.out.print("Saisir le rang : ");
    Scanner sc = new Scanner(System.in);
    int rang = sc.nextInt();
    int resultat = 1;
    int prevnombre1 = 1;
    int prevnombre2 = 1;
    for (int i=0; i<=rang; i++)
    {
      if(i<2)
      {
        // prevnombre=0;
        // resultat+=prevnombre;
        System.out.println("t" + i + "=" + resultat);
      }
      else if (i >= 2)
      {
      resultat=prevnombre2+prevnombre1;
      prevnombre2=prevnombre1;
      prevnombre1=resultat;
      System.out.println("t" + i + "=" + resultat);
      }
    }
    //System.out.print("Voici le resultat de la suite de Fibonacci au rang " + rang + " : " + resultat);
  }
}
