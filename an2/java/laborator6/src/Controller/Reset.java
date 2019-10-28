package Controller;

import View.Canvas;
import View.DrawingFrame;
import View.Toolbar;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;

public class Reset implements ActionListener {
    BufferedImage img;
    View.Canvas canvas;
    Toolbar toolbar;
    DrawingFrame frame;

    public Reset(BufferedImage img, Canvas canvas, Toolbar toolbar, DrawingFrame frame){
        this.img = img;
        this.canvas = canvas;
        this.toolbar = toolbar;
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        System.out.println("Controller.Reset");
        Graphics2D g = img.createGraphics();
        g.clearRect(0, 0, canvas.getWidth(), canvas.getHeight());
        g.dispose();
        canvas.repaint();
    }
}
