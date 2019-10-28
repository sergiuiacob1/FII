package View;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

public class Toolbar extends JPanel{
    JLabel sidesLabel, shapeLabel, strokeLabel;
    public JTextField sidesText;
    public JTextField shapeText;
    public JTextField strokeText;
    JLabel expressionLabel;
    public JTextField expressionText;
    JButton draw, drawGraph, start;
    Canvas canvas;
    BufferedImage img;
    //
    Toolbar(BufferedImage img, Canvas canvas){
        this.img = img;
        this.canvas = canvas;
        init();
    }
    //
    private void init(){
        this.setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        sidesLabel = new JLabel("Number of sides : ");
        shapeLabel = new JLabel("Number of shapes : ");
        strokeLabel = new JLabel("Stroke : ");
        expressionLabel = new JLabel("Expression : ");
        //
        sidesText = new JTextField(10);
        //sidesText.setHorizontalAlignment(SwingConstants.LEFT);
        shapeText = new JTextField(10);
        //shapeText.setHorizontalAlignment(JTextField.CENTER);
        strokeText = new JTextField(10);
        //strokeText.setHorizontalAlignment(JTextField.CENTER);
        //
        expressionText = new JTextField(10);
        //
        draw = new JButton("Draw");
        drawGraph = new JButton("Draw graph");
        start = new JButton("Start/Stop");
        draw.addActionListener(new Controller.Draw(img, canvas, this));
        drawGraph.addActionListener(new Controller.CreateGraph(canvas.frame));
        start.addActionListener(new Controller.CreatePlot(canvas.frame));
        c.insets = new Insets(2,0,2,0);
        c.gridx = 0;
        c.gridy = 0;
        this.add(sidesLabel, c);
        c.gridx = 1;
        c.gridy = 0;
        this.add(sidesText, c);
        c.gridx = 0;
        c.gridy = 1;
        this.add(shapeLabel, c);
        c.gridx = 1;
        c.gridy = 1;
        this.add(shapeText, c);
        c.gridx = 0;
        c.gridy = 2;
        this.add(strokeLabel, c);
        c.gridx = 1;
        c.gridy = 2;
        this.add(strokeText, c);
        c.gridx = 1;
        c.gridy = 3;
        this.add(draw, c);
        c.insets = new Insets(0, 40, 0, 0);
        c.gridx = 7;
        c.gridy = 1;
        this.add(expressionLabel, c);
        c.insets = new Insets(0, 0, 0, 0);
        c.gridx = 9;
        c.gridy = 1;
        this.add(expressionText, c);
        c.gridx = 9;
        c.gridy = 3;
        this.add(drawGraph, c);
        c.insets = new Insets(0, 50, 0, 0);
        c.gridx = 11;
        c.gridy = 1;
        this.add(start, c);
    }
}
