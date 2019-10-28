package Controller;

import View.DrawingFrame;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;
import java.util.Vector;
import javax.swing.Timer;

public class DotsDelay {
    DrawingFrame frame;
    int i = 0, maxs = 0;
    Graphics2D g;
    Vector<Double> vcx = new Vector<>();
    Vector<Double> vcy = new Vector<>();
    Vector<Double> vx = new Vector<>();
    Vector<Double> vy = new Vector<>();
    int maxWidth;
    int maxHeigth;

    public DotsDelay(DrawingFrame frame) {
        this.frame = frame;
        g = frame.canvas.im.createGraphics();
        //
        maxWidth = 800;
        maxHeigth = 600;
        //System.out.println(frame.canvas.getWidth() + " " + frame.canvas.getHeight());
        for(int i=0;i<10;i++){
            Random random = new Random();
            int x = random.nextInt(frame.canvas.getWidth()/8);
            int y = random.nextInt(frame.canvas.getHeight()/8);
            //System.out.println(x + " " + y);
            vcx.add((double) x); maxs = Math.max(x, maxs);
            vcy.add((double) y);
        }
        //
        int npts = maxs;
        for(int i=1;i<=npts;i++){
            vx.add((double)i);
        }

        for( double x : vx ){
            double y = interpolate(x, true);
            vy.add(y);
        }
        //
        Timer timer = new Timer(50, new MyTimerActionListener());
        timer.start();
    }

    private double interpolate(double x, boolean b) {
            int size = vcx.size();
            int k = 0;
            if( x >= vcx.elementAt(size - 2)){
                k = size - 2;
            } else {
                while( x > vcx.elementAt(k + 1)) k++;
            }
            //
            double xL = vcx.elementAt(k), yL = vcy.elementAt(k), xR = vcx.elementAt(k+1), yR = vcy.elementAt(k+1);
            if ( !b )
            {
                if ( x < xL ) yR = yL;
                if ( x > xR ) yL = yR;
            }
            double dydx = ( yR - yL ) / ( xR - xL );
            return yL + dydx * ( x - xL );
    }

    //
    class MyTimerActionListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            Random rand = new Random();
            int rnd = rand.nextInt(maxs);
            double x = vx.elementAt(rnd) * 8;
            double y = vy.elementAt(rnd) * 8;
            System.out.println("1.X = " + x + " " + "Y = " + y);
            System.out.println(maxHeigth + " " + maxWidth);
            if(x > maxWidth){
                x = maxWidth - 20;
            }
            if(y > maxHeigth){
                y = maxHeigth - 20;
            }
            if(x < 0){
                x = 20;
            }
            if(y < 0){
                y = 20;
            }
            System.out.println("2.X = " + x + " " + "Y = " + y);
            g.setColor(Color.red);
            g.fillOval((int)x, (int)y, 10, 10);
            frame.canvas.repaint();
            i++;
            if (i == 50) {
                ((Timer) e.getSource()).stop();
                DrawLines();
            }
        }
    }
        private void DrawLines() {
            g.clearRect(0, 0, frame.canvas.getWidth(), frame.canvas.getHeight());
            frame.canvas.repaint();
            Stroke strk = new BasicStroke(4);
            g.setStroke(strk);
            g.setColor(Color.YELLOW);
            int npts = maxs;
            for(int i=1;i<npts;i++){
                        double x0;
                        double y0;
                        double x1;
                        double y1;
                        x0 = (vx.elementAt(i-1))*8;
                        y0 = (vy.elementAt(i-1))*8;
                        x1 = (vx.elementAt(i))*8;
                        y1 = (vy.elementAt(i))*8;
                        if(x0 > maxWidth){
                            x0 = maxWidth - 20;
                        }
                        if(y0 > maxHeigth){
                            y0 = maxHeigth - 20;
                        }
                        if(x0 < 0){
                            x0 = 20;
                        }
                        if(y0 < 0){
                            y0 = 20;
                        }
                        if(x1 > maxWidth){
                            x1 = maxWidth - 20;
                        }
                        if(y1 > maxHeigth){
                            y1 = maxHeigth - 20;
                        }
                        if(x1 < 0){
                            x1 = 20;
                        }
                        if(y1 < 0){
                            y1 = 20;
                        }
                        g.drawLine((int)x0, (int)y0, (int)x1, (int)y1);
                        //System.out.println(x0  + " " + y0);// + " " + x1 + " " + y1);
                    }
                    double x0;
                    double y0;
                    double x1;
                    double y1;
                    x0 = (vx.elementAt(0))*8;
                    y0 = (vy.elementAt(0))*8;
                    x1 = (vx.elementAt(vx.size()-1))*8;
                    y1 = (vy.elementAt(vx.size()-1))*8;
                    if(x0 > maxWidth){
                        x0 = maxWidth - 20;
                    }
                    if(y0 > maxHeigth){
                        y0 = maxHeigth - 20;
                    }
                    if(x0 < 0){
                        x0 = 20;
                    }
                    if(y0 < 0){
                        y0 = 20;
                    }
                    if(x1 > maxWidth){
                        x1 = maxWidth - 20;
                    }
                    if(y1 > maxHeigth){
                        y1 = maxHeigth - 20;
                    }
                    if(x1 < 0){
                        x1 = 20;
                    }
                    if(y1 < 0){
                        y1 = 20;
                    }
                    g.drawLine((int)x0, (int)y0, (int)x1, (int)y1);
                    System.out.println("Ajuns");
                    g.dispose();

                    frame.canvas.repaint();
        }

    public void paintSVG(Graphics2D g2) {
        Stroke strk = new BasicStroke(4);
        g2.setStroke(strk);
        g2.setColor(Color.YELLOW);
        int npts = maxs;
        for(int i=1;i<npts;i++){
            double x0;
            double y0;
            double x1;
            double y1;
            x0 = (vx.elementAt(i-1))*8;
            y0 = (vy.elementAt(i-1))*8;
            x1 = (vx.elementAt(i))*8;
            y1 = (vy.elementAt(i))*8;
            if(x0 > maxWidth){
                x0 = maxWidth - 20;
            }
            if(y0 > maxHeigth){
                y0 = maxHeigth - 20;
            }
            if(x0 < 0){
                x0 = 20;
            }
            if(y0 < 0){
                y0 = 20;
            }
            if(x1 > maxWidth){
                x1 = maxWidth - 20;
            }
            if(y1 > maxHeigth){
                y1 = maxHeigth - 20;
            }
            if(x1 < 0){
                x1 = 20;
            }
            if(y1 < 0){
                y1 = 20;
            }
            g2.drawLine((int)x0, (int)y0, (int)x1, (int)y1);
            //System.out.println(x0  + " " + y0);// + " " + x1 + " " + y1);
        }
        double x0;
        double y0;
        double x1;
        double y1;
        x0 = (vx.elementAt(0))*8;
        y0 = (vy.elementAt(0))*8;
        x1 = (vx.elementAt(vx.size()-1))*8;
        y1 = (vy.elementAt(vx.size()-1))*8;
        if(x0 > maxWidth){
            x0 = maxWidth - 20;
        }
        if(y0 > maxHeigth){
            y0 = maxHeigth - 20;
        }
        if(x0 < 0){
            x0 = 20;
        }
        if(y0 < 0){
            y0 = 20;
        }
        if(x1 > maxWidth){
            x1 = maxWidth - 20;
        }
        if(y1 > maxHeigth){
            y1 = maxHeigth - 20;
        }
        if(x1 < 0){
            x1 = 20;
        }
        if(y1 < 0){
            y1 = 20;
        }
        g2.drawLine((int)x0, (int)y0, (int)x1, (int)y1);
        System.out.println("Ajuns");
    }
}