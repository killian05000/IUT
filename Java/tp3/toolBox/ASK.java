package toolBox;
import java.util.*;

public class ASK
{
  public static void main(String[] args)
  {
    int answer = askInt("un Int : ");
    System.out.println(answer);
    double answer2 = askDouble("un Double : ");
    System.out.println(answer2);
    String answer3 = askString("ton nom : ");
    System.out.println(answer3);
  }

  public static int askInt(String question)
  {
    boolean test=false;
    int answer=0;
    while (!test)
    {
      try
      {
          Scanner sc = new Scanner(System.in);
          System.out.print(question);
          answer = sc.nextInt();
          test=true;
      }
      catch(InputMismatchException e)
      {
        System.out.println();
        System.out.println("A data type error have been occured !");
        System.out.println("              Try again              ");
        System.out.println();
      }
    }
    return answer;
  }

  public static double askDouble(String question)
  {
    boolean test=false;
    double answer=0;
    while (!test)
    {
      try
      {
          Scanner sc = new Scanner(System.in);
          System.out.print(question);
          answer = sc.nextDouble();
          test=true;
      }
      catch(InputMismatchException e)
      {
        System.out.println();
        System.out.println("A data type error have been occured !");
        System.out.println("Mb u forgot to use ',' instead of '.'");
        System.out.println("--------------Try again--------------");
        System.out.println();
      }
    }
    return answer;
  }

  public static String askString(String question)
  {
    boolean test=false;
    String answer="";
    while (!test)
    {
      try
      {
          Scanner sc = new Scanner(System.in);
          System.out.print(question);
          answer = sc.nextLine();
          test=true;
      }
      catch(InputMismatchException e)
      {
        System.out.println();
        System.out.println("A data type error have been occured !");
        System.out.println("--------------Try again--------------");
        System.out.println();
      }
    }
    return answer;
  }
}
