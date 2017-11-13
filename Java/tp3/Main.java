import java.util.*;
import toolBox.ASK.*;

public class Main
{
  public static void main(String[] args)
  {
    Vector<Student> v = new Vector<Student>();
    fillList(v);
    displayList(v);
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
      System.out.println("------------------------");
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
}
