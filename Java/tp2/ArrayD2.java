import java.util.*;
import java.math.*;
import java.text.*;

public class ArrayD2
{
  public static void main(String[] args)
  {
    double[][] arrayTM;
    int[] arrayMonth;
    double[] arrayTemperature;
    System.out.print("Sur combien d'année porte votre étude : ");
    Scanner sc = new Scanner(System.in);
    int nbA = sc.nextInt();

    arrayMonth = new int[nbA*12];
    arrayTemperature = new double[nbA*12];
    arrayTM = new double[nbA][12];

    fillTempTab(arrayTM);
    //fillTempTab(arrayTemperature);



    dispTempTab(arrayTM);
    //dispTempTab(arrayTemperature);

    //System.out.print("Saisissezun numéros de mois : ");
    //int nbM = sc.nextInt();
    //dispMonthValue(arrayTemperature, nbM);
  }

  public static double[][] fillTempTab(double[][] arrayTM)
  {
    for (int i=0; i < arrayTM.length; ++i)
    {
      for (int k=0; k < arrayTM[0].length; ++k)
      {
      int tmp = (int)((20+Math.random()*(20))*10);
      double tmp2 = tmp/10.0;

      arrayTM[i][k] = tmp2;
      }
    }
    return arrayTM;
  }

  // public static double[] fillTempTab(double[] arrayTemperature)
  // {
  //   for (int i=0; i < arrayTemperature.length; ++i)
  //   {
  //     int tmp = (int)((20+Math.random()*(20))*10);
  //     double tmp2 = tmp/10.0;
  //     arrayTemperature[i] = tmp2;
  //   }
  //   return arrayTemperature;
  // }

  public static void dispTempTab(double[][] array)
  {
    for (int i=0; i < array.length; ++i)
    {
      for (int k=0; k < array[0].length; ++k)
      {
          System.out.println((k+1)+" : "+array[i][k]);
      }
    }
  }

  // public static void dispTempTab(double[] array)
  // {
  //   for (int i=0; i < array.length; ++i)
  //     System.out.println(i+1+" : "+array[i]);
  // }
  //
  // public static void dispMonthValue(double[] array, int nbM)
  // {
  //   int tmp = array.length;
  //   for(int i=0; i < (tmp/12); ++i)
  //   {
  //     System.out.println("La valeur du mois "+nbM+" pour l'année "+(i+1)+" est de "+array[(nbM-1)+(12*i)] + " ---- id month = "+((nbM)+(12*i)));
  //   }
  // }
}
