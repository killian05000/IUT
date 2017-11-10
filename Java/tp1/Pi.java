import java.util.*;
import java.lang.*;

public class Pi
{
  public static void main(String[] args)
  {
    double n = Integer.parseInt(args[0]);
    
    if ((args.length != 1) && (n <=0))
    {
      System.out.println("Fournisser une valeur en argument.");
      return;
    }

    double tmp=0;

    for (int i=1; i <= n; ++i)
    {
      tmp += 1/Math.pow(i,2);
    }

    double pi = Math.sqrt(6*tmp);
    System.out.println("La valeur de PI approchée à "+n+" itérations : "+pi);
  }
}
