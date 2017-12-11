import java.util.*;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.*;

class GraphicWindow extends JFrame implements ActionListener
{
  GraphicWindow(String s)
  {
    super(s);
    setSize(600,400);
    setLocationRelativeTo(null);
    setResizable(false);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    JMenuBar menuBar = new JMenuBar();
    JMenu menu = new JMenu("File");
    JMenuItem item;
    setJMenuBar(menuBar);
    menuBar.add(menu);

      item = new JMenuItem("Load");
      menu.add(item);
      item.addActionListener(this);

      item = new JMenuItem("Save");
      menu.add(item);
      item.addActionListener(this);
      menu.add(new JSeparator());

      item = new JMenuItem("Quit");
      menu.add(item);
      item.addActionListener(this);

    menu = new JMenu("Color");
    menuBar.add(menu);

      item = new JMenuItem("Black");
      menu.add(item);
      item.addActionListener(this);

      item = new JMenuItem("Red");
      menu.add(item);
      item.addActionListener(this);

      item = new JMenuItem("Blue");
      menu.add(item);
      item.addActionListener(this);
      menu.add(new JSeparator());

      item = new JMenuItem("Pick");
      menu.add(item);
      item.addActionListener(this);
  }

  public void actionPerformed(ActionEvent evenement)
  {
              ///////// MENU FILE /////////

    if (evenement.getActionCommand().equals("Load"))
    {
      System.out.println("MENU LOAD");

      JFileChooser selector = new JFileChooser();
      selector.addChoosableFileFilter(new FileNameExtensionFilter("txt files", "txt"));
      int result = selector.showOpenDialog(null);

      if (result == JFileChooser.APPROVE_OPTION)
      {
        System.out.println("Chosen file : " + selector.getSelectedFile().getAbsolutePath());
      }
    }
    if (evenement.getActionCommand().equals("Save"))
    {
      System.out.println("MENU SAVE");
    }
    if (evenement.getActionCommand().equals("Quit"))
    {
      System.out.println("MENU QUIT ATTEMPT");
      int result = JOptionPane.showConfirmDialog(null, "Voulez vous quitter ?", "Quitter", JOptionPane.YES_NO_OPTION, JOptionPane.ERROR_MESSAGE);
      if( result == JOptionPane.YES_OPTION )
        {
          System.out.println("MENU QUIT");
          System.exit(0);
        }
    }

              ///////// MENU COLOR /////////

    if (evenement.getActionCommand().equals("Black"))
    {
      System.out.println("MENU2 BLACK");
    }
    if (evenement.getActionCommand().equals("Red"))
    {
      System.out.println("MENU2 RED");
    }
    if (evenement.getActionCommand().equals("Blue"))
    {
      System.out.println("MENU2 BLUE");
    }
    if (evenement.getActionCommand().equals("Pick"))
    {
      System.out.println("MENU2 PICK");
    }
  }
}
