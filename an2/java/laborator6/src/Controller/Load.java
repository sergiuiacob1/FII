package Controller;

import View.DrawingFrame;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class Load implements ActionListener {
    public DrawingFrame frame;
    public JFileChooser fileChooser;
    public Load(DrawingFrame frame){
        this.frame = frame;
        fileChooser = new JFileChooser();
        fileChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        System.out.println("Controller.Load..");
        int rVal = fileChooser.showSaveDialog(frame.canvas);
        if(rVal == JFileChooser.APPROVE_OPTION){
            try{
                frame.canvas.im = ImageIO.read(new File(fileChooser.getSelectedFile().getAbsolutePath()));
                frame.canvas.repaint();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
        }
        if(rVal == JFileChooser.CANCEL_OPTION){

        }
    }
}
