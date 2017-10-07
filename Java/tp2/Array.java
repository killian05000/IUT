import java.util.*;

public class Array
{
  public static void main(String[] args)
  {
    double[] array;
    System.out.print("Saisissez la taille du tableau : ");
    Scanner sc = new Scanner(System.in);
    int sizeArray = sc.nextInt();
    array = new double[sizeArray];

    fillTab(array, sizeArray);

    for (int i=0; i < sizeArray; ++i)
      System.out.println(array[i]);

    temperature(array);

    System.out.print("Saisissez une temperature a repérer : ");
    double temp = sc.nextDouble();

    int resTemp = compare(array, temp);
    System.out.println("Il y a "+resTemp+" mois ayant enregistré une temperature de "+temp+" degrés");
  }

  public static double[] fillTab(double[] array, int sizeArray)
  {
    Scanner sc2 = new Scanner(System.in);
    double tmp;
    for (int i=0; i < sizeArray; ++i)
    {
      System.out.print("Saisissez la valeur n°"+(i+1)+": ");
      tmp = sc2.nextDouble();
      array[i] = tmp;
    }
    return array;
  }

  public static void temperature(double[] array)
  {
    int nTemperatures=0;
    int pTemperatures=0;
    for (int i=0; i < array.length; ++i)
    {
      if (array[i] < 0)
        nTemperatures+=1;
      else
        pTemperatures+=1;
    }
    System.out.println("Nombre de mois à temperature négative : "+nTemperatures);
    System.out.println("Nombre de mois à temperature négative : "+pTemperatures);
  }

  public static int compare(double[] array, double temp)
  {
    int equalTemp=0;
    for (int i=0; i < array.length; ++i)
    {
      if (array[i] == temp)
        equalTemp+=1;
    }
    return equalTemp;
  }
}
