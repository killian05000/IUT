import java.util.*;
import java.lang.*;

public class NIRPP
{
  public static void main(String[] args)
  {
    System.out.print("Saisissez votre NIRPP : ");
    Scanner sc = new Scanner(System.in);
    String NIR = sc.nextLine();
    System.out.print("Saisissez votre code de control : ");
    int CC = sc.nextInt();

    if (verif(NIR,CC))
      System.out.println("Le code "+CC+" est bien valide pour le NIRPP "+NIR);
    else
      System.out.println("Code errone !");

    information(NIR);
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

    String mois[] = {"Janvier","Fevrier","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Decembre"};

    int NIRmonth = (Integer.parseInt(NIR.substring(3,5)))-1; // la deuxieme borne du substring est pas incluse


    System.out.println("Vous etes né le 19"+NIR.substring(1,3)+" en "+mois[NIRmonth]);
  }
}
