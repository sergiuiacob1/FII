package View;

import View.Canvas;
import View.ControlPanel;
import View.Toolbar;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

public class DrawingFrame extends JFrame{
    public Canvas canvas;
    public Toolbar toolbar;
    ControlPanel controlPanel;
    public  BufferedImage img = new BufferedImage(800, 600, BufferedImage.TYPE_3BYTE_BGR);

    public DrawingFrame(){
        super("Drawing master");
        init();
    }
    //
    private void init(){
        this.getContentPane().setLayout(new BorderLayout());
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        canvas = new Canvas(img, this);
        //new InteractionThread(img, canvas).start();
        this.getContentPane().add(canvas, BorderLayout.CENTER);
        //
        toolbar = new Toolbar(img,canvas);
        this.getContentPane().add(toolbar, BorderLayout.NORTH);
        //
        controlPanel = new ControlPanel(img, canvas, toolbar, this);
        this.getContentPane().add(controlPanel, BorderLayout.SOUTH);
        //
        this.setSize(800, 1000);

    }
    //
    public void start() {
        this.setVisible(true);
        //canvas.start();
    }
}
