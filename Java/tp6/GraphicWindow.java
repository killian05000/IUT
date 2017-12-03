import java.util.*;
import javax.swing.JFrame;

public class GraphicWindow extends JFrame
{
  DrawingZone DrawZ;
  public GraphicWindow()
  {
    this.setSize(300,300);
    this.setLocationRelativeTo(null);
    this.setResizable(false);
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    this.setVisible(true);
    this.setContentPane(DrawZ);
  }
}
