import java.util.*;

public class Minimum
{
  public static void main(String[] args)
  {
    System.out.print("Saisissez trois nombres : ");
    Scanner sc = new Scanner(System.in);
    float usernumber1 = sc.nextFloat();
    float usernumber2 = sc.nextFloat();
    float usernumber3 = sc.nextFloat();

    minimum(usernumber1, usernumber2, usernumber3);
  }

  public static void minimum(float usernumber1, float usernumber2, float usernumber3)
  {
    if ((usernumber1 < usernumber2) && (usernumber1 < usernumber3))
    {
      System.out.println("Le plus petit nomnbre est : "+usernumber1);
    }
    else if ((usernumber2 < usernumber1) && (usernumber2 < usernumber3))
    {
      System.out.println("Le plus petit nomnbre est : "+usernumber2);
    }
    else
      System.out.println("Le plus petit nomnbre est : "+usernumber3);
  }
}
