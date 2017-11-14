import java.util.*;
import toolBox.ASK.*;

public class Main
{
  public static void main(String[] args)
  {
    Vector<Student> v = new Vector<Student>();
    fillList(v);
    bestStudent(v);
    worseStudent(v);
    System.out.println();
    displayList(v);
    namesOrderedList(v);
    lowerThan(v);

  }

  public static void fillList(Vector<Student> list)
  {
    int nb=0;
    while (nb<=0)
    {
      nb = toolBox.ASK.askInt("How many students do you want to register ? ");
      System.out.println();
    }

    for ( int i=0; i < nb; ++i)
    {
      String fname = toolBox.ASK.askString("Student n°"+(i+1)+" First name : ");
      String lname = toolBox.ASK.askString("Student n°"+(i+1)+" Last name : ");
      Double average = toolBox.ASK.askDouble("Student n°"+(i+1)+" Average : ");
      System.out.println();
      System.out.println("---------------------------------------");
      System.out.println();
      Student tmp = new Student(fname,lname,average);
      list.addElement(tmp);
    }
  }

  public static void displayList(Vector<Student> list)
  {
    System.out.println("Here is the list of the registered students : ");
    for ( int i=0; i < list.size(); ++i)
    {
        (list.elementAt(i)).displayFormal();
    }
    System.out.println();
  }

  public static void bestStudent(Vector<Student> list)
  {
    double firstAverage=(list.elementAt(0)).average;
    double compareAverage=(list.elementAt(0)).average;
    int studentRank=0;
    for ( int i=0; i < list.size(); ++i)
    {
      compareAverage = (list.elementAt(i)).average;

      if (compareAverage > firstAverage)
      {
        firstAverage = compareAverage;
        studentRank = i;
      }
    }
    System.out.println("The student with the best grade is "+(list.elementAt(studentRank)).firstName+" "+(list.elementAt(studentRank)).lastName+" with an average of "+(list.elementAt(studentRank)).average);
  }

  public static void worseStudent(Vector<Student> list)
  {
    double worseAverage=(list.elementAt(0)).average;
    double compareAverage=(list.elementAt(0)).average;
    int studentRank=0;
    for ( int i=0; i < list.size(); ++i)
    {
      compareAverage = (list.elementAt(i)).average;

      if (compareAverage < worseAverage)
      {
        worseAverage = compareAverage;
        studentRank = i;
      }
    }
    System.out.println("The student with the worse grade is "+(list.elementAt(studentRank)).firstName+" "+(list.elementAt(studentRank)).lastName+" with an average of "+(list.elementAt(studentRank)).average);
  }

  public static void lowerThan(Vector<Student> list)
  {
    double step=10;
    System.out.print("Enter a grade (you will get a list of the students with a lower one) : ");
    Scanner sc = new Scanner(System.in);
    step = sc.nextDouble();

    for ( int i=0; i < list.size(); ++i)
    {
      if ((list.elementAt(i)).average < step)
        (list.elementAt(i)).displayFormal();
    }
  }

  public static void namesOrderedList(Vector<Student> list)
  {
    Vector<Student> orderList = new Vector<Student>();
    for ( int i=0; i < list.size(); ++i)
    {
      if (((list.elementAt(i)).lname).charAt(0) > ((list.elementAt(0)).lname).charAt(0))
        orderList.addElement((list.elementAt(i)));
      else
        orderList.addElement((list.elementAt(0)));
    }
    System.out.println("The ordered list of the sutends : ");
    orderList.displayList();
  }
}
