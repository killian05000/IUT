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
    displayList(v,"Here is the list of the registered students : ");
    gradesOrderedList(v);
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

  public static void displayList(Vector<Student> list, String message)
  {
    System.out.println(message);
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
    System.out.println("The best student is "+(list.elementAt(studentRank)).firstName+" "+(list.elementAt(studentRank)).lastName+" with an average of "+(list.elementAt(studentRank)).average);
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
    System.out.println("The worse student is "+(list.elementAt(studentRank)).firstName+" "+(list.elementAt(studentRank)).lastName+" with an average of "+(list.elementAt(studentRank)).average);
  }

  public static void lowerThan(Vector<Student> list)
  {
    double step=10;
    step = toolBox.ASK.askDouble("Enter a grade (you will get a list of the students with a lower one) : ");

    for ( int i=0; i < list.size(); ++i)
    {
      if ((list.elementAt(i)).average < step)
        (list.elementAt(i)).displayFormal();
    }
  }

  // only works for the first letter of the first name. It requires to be a lowercase
  public static void namesOrderedList(Vector<Student> list)
  {
    Vector<Student> orderedList = new Vector<Student>();
    Student tmp;
    int listSize = list.size();
    for ( int k=0; k < listSize; ++k)
    {
      tmp = list.elementAt(0);
      int rank = 0;
      for ( int i=0; i < list.size(); ++i)
      {
        if (((list.elementAt(i)).firstName).charAt(0) < tmp.firstName.charAt(0))
        {
          tmp = list.elementAt(i);
          rank = i;
        }
      }
      orderedList.addElement(tmp);
      list.removeElementAt(rank);
    }

    for ( int i=0; i < orderedList.size(); ++i)
    {
      list.addElement(orderedList.elementAt(i));
    }
    displayList(list,"Here is the names ordered list of the sutends : ");
  }

  public static void NOL(Vector<Student> list)
  {
    Vector<Student> orderedList = new Vector<Student>();
    Student tmp;
    int listSize = list.size();
    for ( int k=0; k < listSize; ++k)
    {
      tmp = list.elementAt(0);
      int rank = 0;
      for ( int i=0; i < list.size(); ++i)
      {
        if (((list.elementAt(i)).firstName).compareTo(tmp.firstName) >= 0)
        {
          tmp = list.elementAt(i);
          rank = i;
        }
      }
      orderedList.addElement(tmp);
      list.removeElementAt(rank);
    }

    for ( int i=0; i < orderedList.size(); ++i)
    {
      list.addElement(orderedList.elementAt(i));
    }
    displayList(list,"Here is the names ordered list of the sutends : ");
  }

  public static void gradesOrderedList(Vector<Student> list)
  {
    Vector<Student> orderedList = new Vector<Student>();
    Student tmp;
    int listSize = list.size();

    for ( int k=0; k < listSize; ++k)
    {
      tmp = list.elementAt(0);
      int rank = 0;
      for ( int i=0; i < list.size(); ++i)
      {
        if (((list.elementAt(i)).average) > tmp.average)
        {
          tmp = list.elementAt(i);
          rank = i;
        }
      }
      orderedList.addElement(tmp);
      list.removeElementAt(rank);
    }

    for ( int i=0; i < orderedList.size(); ++i)
    {
      list.addElement(orderedList.elementAt(i));
    }

    displayList(list,"Here is the grades ordered list of the sutends : ");
  }
}
