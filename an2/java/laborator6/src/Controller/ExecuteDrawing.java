package Controller;
import View.Canvas;
import View.Toolbar;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.util.Random;

public class ExecuteDrawing{
     BufferedImage img;
     JPanel canvas;
     Toolbar toolbar;
    boolean clicked;
    int ex, ey;
    public ExecuteDrawing(BufferedImage img, Canvas canvas, Toolbar toolbar, boolean clicked, int ex, int ey) {
        this.img = img;
        this.canvas = canvas;
        this.toolbar = toolbar;
        this.clicked = clicked;
        this.ex = ex;
        this.ey = ey;
    }
    public void run() {
        Random rand = new Random();
        if(clicked){
            Graphics2D g = img.createGraphics();
            int x0 = ex;
            int y0 = ey;
            Stroke strk = new BasicStroke(rand.nextInt(6));
            g.setStroke(strk);
            g.setColor(new Color(rand.nextInt(200) + 50, rand.nextInt(200) + 50, rand.nextInt(200) + 50, rand.nextInt(128) + 50));
            g.fill(new RegularPolygon(x0, y0, rand.nextInt(40) + 5, rand.nextInt(20) + 2));
            g.dispose();
            canvas.repaint();
        } else {
            int sides = Integer.parseInt(toolbar.sidesText.getText().toString());
            int shapes = Integer.parseInt(toolbar.shapeText.getText().toString());
            int stroke = Integer.parseInt(toolbar.strokeText.getText().toString());
            //
            //canvas.repaint();
            System.out.println("Sides : " + sides);
            System.out.println("Shapes : " + shapes);
            System.out.println("Stroke : " + stroke);
            Graphics2D g = img.createGraphics();
            Stroke strk = new BasicStroke(stroke);
            g.setStroke(strk);
            shapes = Math.min(18, shapes);
            for(int i=1;i<=shapes;i++){
                g.setColor(new Color(rand.nextInt(200) + 50, rand.nextInt(200) + 50, rand.nextInt(200) + 50, rand.nextInt(128) + 50));
                g.draw(new RegularPolygon(rand.nextInt(img.getWidth()), rand.nextInt(img.getHeight()), rand.nextInt(70), sides));
            }
            g.dispose();
            canvas.repaint();
        }
    }
}