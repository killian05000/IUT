import java.util.*;

public class Student
{
  public String firstName;
  public String lastName;
  public double average;

  public Student(String _firstName, String _lastName, double _average)
  {
    firstName = _firstName;
    lastName = _lastName;
    average = _average;
  }

  public void display()
  {
    System.out.println(firstName+" "+lastName+"'s average is "+average);
  }

  public void displayFormal()
  {
    System.out.println(firstName+" / "+lastName+" / "+average);
  }
}
