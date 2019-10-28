package Controller;

import View.DrawingFrame;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class Save implements ActionListener{
    DrawingFrame frame;
    private JFileChooser fileSaver;

    public Save(DrawingFrame frame){
        this.frame = frame;
        fileSaver = new JFileChooser();
        fileSaver.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        System.out.println("Select a directory.");
        int rVal = fileSaver.showSaveDialog(frame.canvas);
        if(rVal == JFileChooser.APPROVE_OPTION){
            System.out.println("Saving in " + fileSaver.getSelectedFile().getAbsolutePath());
            //
               try{
                   File outputfile = new File(fileSaver.getSelectedFile().getAbsolutePath());
                   ImageIO.write(frame.img, "png", outputfile);
               } catch (IOException e1) {
                   e1.printStackTrace();
               }
            //
        }
        if(rVal == JFileChooser.CANCEL_OPTION){
            System.out.println("Canceled");
        }
    }
}
