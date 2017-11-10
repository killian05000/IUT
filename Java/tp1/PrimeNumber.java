import java.util.*;
import java.lang.*;

public class PrimeNumber
{
  public static void main(String[] args)
  {
    System.out.print("Entrer un nombre positif à tester : ");
    Scanner keyboard = new Scanner(System.in);
    
    int userNumber = keyboard.nextInt();

    if (userNumber <= 0)
    {
      System.out.println("Le nome doit être > 0 ! ");
      return;
    }

    if (isPrimeNumber(userNumber))
      System.out.println(userNumber+" est un nombre premier");
    else
      System.out.println(userNumber+" n'est pas un nombre premier");

    for (int i=1; i <=100; ++i)
    {
      if (isPrimeNumber(i))
        System.out.println(i);
    }
  }

    public static boolean isPrimeNumber(int number)
    {
      for (int i =2; i < number; ++i)
        if (number%i==0)
          return false;

      return true;
    }
}
