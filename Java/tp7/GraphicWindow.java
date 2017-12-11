import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class GraphicWindow extends JFrame implements ActionListener
{
  GraphicWindow(String s)
  {
    super(s);
    this.setSize(600,400);
    this.setLocationRelativeTo(null);
    this.setResizable(false);
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    this.setVisible(true);

    JMenuBar menuBar = new JMenuBar();
    menuBar.add(menuBar);
    JMenu menu = new JMenu("Fihier");
    menuBar.add(menu);
    JMenuItem item = new JMenuItem("Quitter");
    menu.add(item);
    item.setActionCommand("menu_quitter");
    item.addActionListener(this);
  }

  public void actionPerformed(ActionEvent evenement)
  {
    if (evenement.getActionCommand().equals("menu_quitter"))
      System.out.println("MENU QUITTER");
  }
}


// FenetreSwing(String s)
// {
//   super(s);
//   setSize(400,300);
//   setVisible(true);
//   JMenuBar menuBar = new JMenuBar();
//   setJMenuBar(menuBar);
//   JMenu menu = new JMenu("Fichier");
//   menuBar.add(menu);
//   JMenuItem item =new JMenuItem("Quitter");
//   menu.add(item);
//   item.setActionCommand("menu_quitter");
//   item.addActionListener(this);
// }
