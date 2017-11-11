import java.util.*;

public class Main
{
  public static void main(String[] args)
  {
    // Student dude = new Student("Killian", "Wolfger", 10.4);
    // Student dude2 = new Student("Loic", "Escales", 8.4);
    // Student dude3 = new Student("Laurent", "Doiteau", 8.9);
    // Student dude4 = new Student("Leo", "Sudreau", 8.7);
    // Student dude5 = new Student("Oliver", "Hampton", 18);

    Vector<Student> v = new Vector<Student>();
    fillList(v);
    displayList(v);
  }

  public static void fillList(Vector<Student> list)
  {
    int nb=0;
    while (nb<=0)
    {
      try
      {
          Scanner sc = new Scanner(System.in);
          System.out.print("How many students do you want to register ? ");
          nb = sc.nextInt();
          sc.nextLine();
      }
      catch(InputMismatchException e)
      {
        System.out.println();
        System.out.println("A data type error have been occured !");
        System.out.println("--------------Try again--------------");
        System.out.println();
      }
    }

    boolean test=false;
    for ( int i=0; i < nb; ++i)
    {
      test=false;
      while (!test)
      {
        try
        {
          Scanner sc = new Scanner(System.in);
          System.out.print("Student n°"+(i+1)+" First name : ");
          String fname = sc.next();
          System.out.print("Student n°"+(i+1)+" Last name : ");
          String lname = sc.next();
          System.out.print("Student n°"+(i+1)+" Average : ");
          Double average = sc.nextDouble();
          System.out.println();
          Student tmp = new Student(fname,lname,average);
          list.addElement(tmp);
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
    }
  }

  public static void displayList(Vector<Student> list)
  {
    for ( int i=0; i < list.size(); ++i)
    {
        (list.elementAt(i)).displayFormal();
    }
    System.out.println();
  }
}
