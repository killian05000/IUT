import java.util.*;
import java.math.*;

public class ArrayD2
{
  public static void main(String[] args)
  {
    double[][] arrayTM;

    System.out.print("Sur combien d'année porte votre étude : ");
    Scanner sc = new Scanner(System.in);
    int nbA = sc.nextInt();

    arrayTM = new double[nbA][12];

    fillTempTab(arrayTM);
    dispTempTab(arrayTM);

    System.out.print("Saisissez un numéro de mois pour obtenir toutes ses temperatures au fil des ans : ");
    int nbM = sc.nextInt();
    System.out.println();
    dispMonthValue(arrayTM, nbM);
    System.out.println();

    System.out.print("Saisissez un numéro de mois pour obtenir sa plus haute et sa plus basse temperature : ");
    nbM = sc.nextInt();
    System.out.println();
    dispHigherLowerTemperature(arrayTM, nbM);
  }

  public static double[][] fillTempTab(double[][] arrayTM)
  {
    for (int i=0; i < arrayTM.length; ++i)
    {
      for (int k=0; k < arrayTM[0].length; ++k)
      {
      int tmp = (int)((-20+Math.random()*(60))*10);
      double tmp2 = tmp/10.0;
      arrayTM[i][k] = tmp2;
      }
    }
    return arrayTM;
  }

  public static void dispTempTab(double[][] array)
  {
    for (int i=0; i < array.length; ++i)
    {
      for (int k=0; k < array[0].length; ++k)
      {
          System.out.println((i+1)+":"+(k+1)+" = "+array[i][k]);
      }
      System.out.println();
    }
  }

  public static void dispMonthValue(double[][] array, int nbM)
  {
    for (int i=0; i < array.length; ++i)
    {
          System.out.println("La valeur du mois "+nbM+" pour l'année "+(i+1)+" est de "+array[i][nbM-1]);
    }
  }

  public static void dispHigherLowerTemperature(double[][] array, int nbM)
  {
    double lowertmp=array[0][nbM-1];
    double highertmp=array[0][nbM-1];
    for (int i=0; i < array.length; ++i)
    {
        if (array[i][nbM-1] < lowertmp)
          lowertmp = array[i][nbM-1];
        if (array[i][nbM-1] > highertmp)
          highertmp = array[i][nbM-1];
    }
    System.out.println("La plus haute temperature pour le mois n°"+nbM+" est de "+highertmp+" degrés.");
    System.out.println("La plus basse temperature pour le mois n°"+nbM+" est de "+lowertmp+" degrés.");
  }
}
