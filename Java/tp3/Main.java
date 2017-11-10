import java.util.*;

public class Main
{
  public static void main(String[] args)
  {
    Student dude = new Student("Killian", "Wolfger", 10.4);
    Student dude2 = new Student("Loic", "Escales", 8.4);
    Student dude3 = new Student("Laurent", "Doiteau", 8.9);
    Student dude4 = new Student("Leo", "Sudreau", 8.7);
    Student dude5 = new Student("Oliver", "Hampton", 18);

    Vector<Student> v = new Vector<Student>();
    v.addElement(dude);

    System.out.println(v.getElementAt(0));

    //dude.display();
  }
}
