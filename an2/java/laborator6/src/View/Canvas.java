package View;

import Controller.ExecuteDrawing;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.Serializable;

public class Canvas extends JPanel implements Serializable{
    public BufferedImage im;
    public DrawingFrame frame;
    Canvas canvas;
    public Canvas(BufferedImage img, DrawingFrame frame) {
        this.im = img;
        this.frame = frame;
        canvas = this;
        this.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent e) {
                System.out.println("YEES");
                new ExecuteDrawing(im, canvas, frame.toolbar, true,  e.getX(), e.getY()).run();
            }
        });
    }
    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        //setBackground(Color.gray);
        g.setColor(Color.gray);
        g.fillRect ( 0, 0, im.getWidth(), im.getHeight() );
        g.drawImage(im, 0, 0, this);
    }

    @Override
    public Dimension getPreferredSize() {
        return new Dimension(im.getWidth(), im.getHeight());
    }
}
