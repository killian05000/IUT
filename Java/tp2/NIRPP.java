import java.util.*;
import java.lang.*;

public class NIRPP
{
  public static void main(String[] args)
  {
    System.out.print("Saisissez votre NIRPP : ");
    Scanner sc = new Scanner(System.in);
    String NIR = sc.nextLine();

    if (NIR.length() != 13)
    {
      System.out.println("Un NIRPP est composé de 13 chiffres, vous n'en avez fournis que "+NIR.length());
      return;
    }

    System.out.print("Saisissez votre code de control : ");
    int CC = sc.nextInt();

    if (verif(NIR,CC))
    {
      System.out.println("Le code "+CC+" est bien valide pour le NIRPP "+NIR);
      information(NIR);
    }
    else
      System.out.println("Code errone !");
  }

  public static boolean verif(String NIR, int CC)
  {
    String tmp=NIR;
    long soustraction=0;

    if (NIR.charAt(6)=='A')
    {
      tmp = NIR.replace('A', '0');
      soustraction = 1000000;
    }
    else if (NIR.charAt(6)=='B')
    {
      tmp = NIR.replace('B', '0');
      soustraction = 2000000;
    }

    long NIRPP = Long.parseLong(tmp);
    NIRPP-=soustraction;

    float rightCode = 97-(NIRPP%97);

    if (rightCode != CC)
      return false;

    return true;
  }

  public static void information(String NIR)
  {
    if(NIR.charAt(0)=='1')
      System.out.println("Vous êtes un homme");
    else if (NIR.charAt(0)=='2')
      System.out.println("Vous êtes une femme");
    else
      System.out.println("Vous êtes une espece inconnu");

    String mois[] = {"janvier","fevrier","mars","avril","mai","juin","juillet","aout","septembre","octobre","novembre","decembre"};
    int NIRmonth = (Integer.parseInt(NIR.substring(3,5)))-1; // la deuxieme borne du substring est pas incluse


    System.out.println("Vous etes né le 19"+NIR.substring(1,3)+" en "+mois[NIRmonth]);
    System.out.println("Vous êtes né dans le "+NIR.substring(5,7)+" dans la comune n°"+NIR.substring(7,10));
    System.out.println("Votre numero d'ordre est le "+NIR.substring(10,13));
  }
}
