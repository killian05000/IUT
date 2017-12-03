import java.util.*;
import javax.swing.JPanel;
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
    }
    catch (IOException e)
    {
      e.printStackTrace();
    }
  }
}
