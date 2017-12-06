import java.util.*;
import java.lang.*;
import javax.swing.*;
import java.awt.*;
import java.io.File;
import javax.imageio.ImageIO;
import java.io.IOException;

public class DrawingZone extends JPanel
{
  Image img;

  public DrawingZone()
  {
    try
    {
      img = ImageIO.read(new File("truc.jpg"));
      setSize(new Dimension(200,200));
    }
    catch (IOException e)
    {
      e.printStackTrace();
    }
  }

  public void paint(Graphics g)
  {
    displayBackground(g);
    // displayGraduations(g);
    // displayHands(g);
  }

  public void displayBackground(Graphics g)
  {
    g.fillRect(0, 0, getWidth(), getHeight());
    Graphics2D g2 = (Graphics2D) g;
    g2.setStroke(new BasicStroke(50));
    g.drawImage(img, (int)(this.getWidth()*0.1), (int)(this.getHeight()*0.1), (int)(this.getWidth()*0.8), (int)(this.getHeight()*0.8), null);
    //g.drawImage(img, 0, 0, 200, 200, null);
    //g.drawOval((int)(this.getWidth()*0.1), (int)(this.getHeight()*0.1), (int)(this.getWidth()*0.8), (int)(this.getHeight()*0.8));
    g.drawOval(5, 0,290, 260);
  }

  // public void displayGraduations(Graphics g)
  // {
  //
  // }
  //
  // public void displayHands(Graphics g)
  // {
  //
  // }
}
