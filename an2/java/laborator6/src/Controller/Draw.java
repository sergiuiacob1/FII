package Controller;

import View.Canvas;
import View.Toolbar;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;

public class Draw implements ActionListener{
    BufferedImage img;
    Canvas canvas;
    Toolbar toolbar;

    public Draw(BufferedImage img, Canvas canvas, Toolbar toolbar){
        this.img = img;
        this.canvas = canvas;
        this.toolbar = toolbar;
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        new ExecuteDrawing(img, canvas, toolbar, false, 0, 0).run();
    }
}
