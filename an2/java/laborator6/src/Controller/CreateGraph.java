package Controller;

import View.DrawingFrame;
import net.objecthunter.exp4j.Expression;
import net.objecthunter.exp4j.ExpressionBuilder;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class CreateGraph implements ActionListener {
    String expression;
    DrawingFrame frame;
    public CreateGraph(DrawingFrame frame){
        this.frame = frame;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        expression = frame.toolbar.expressionText.getText();
        System.out.println("Expression is : " + expression);
        Expression exp = new ExpressionBuilder(expression)
                .variables("x")
                .build();
        exp.setVariable("x", -20);
        double x0 = -20, y0 = exp.evaluate(), x1, y1;
        Graphics2D g = frame.img.createGraphics();
        g.drawLine(400, 0, 400, 600);
        g.drawLine(0, 300, 800, 300);
        for(int i=0;i<600;i+=20){
            g.drawLine(397, i, 403, i);
        }
        for(int i=0;i<800;i+=20){
            g.drawLine(i, 297, i, 303);
        }
        g.setColor(Color.green);
        for(int i=-19; i<=20; i++){
            exp.setVariable("x", i);
            double result = exp.evaluate();
            x1 = i;
            y1 = result;
            System.out.println("X = " + i + " " + "Y = " + result);
            g.drawLine((int)(400 + (x0 * 10) - 10), (int)(300 - (y0 * 10)), (int)(400 + (x1 * 10) - 10), (int)(300 - (y1 * 10)));
            x0=x1;
            y0=y1;
        }
        frame.canvas.repaint();

    }
}
