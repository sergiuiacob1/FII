package controller;

import view.CatalogFrame;
import view.ControlPanel;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.XMLEncoder;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class SaveCommand implements ActionListener {
    private CatalogFrame frame;
    private JFileChooser fileSaver;

    public SaveCommand(ControlPanel controlPanel) {
        this.frame = controlPanel.getFrame();
        fileSaver = new JFileChooser();
        fileSaver.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
    }

    public void actionPerformed(ActionEvent e) {
        System.out.println("Select a directory to save the file");
        int rVal = fileSaver.showSaveDialog(frame.getControl());
        if (rVal == JFileChooser.APPROVE_OPTION) {
            System.out.println("Saving in " + fileSaver.getSelectedFile().getAbsolutePath());
            saveCatalog(fileSaver.getSelectedFile().getAbsolutePath());
        }
        if (rVal == JFileChooser.CANCEL_OPTION) {
            System.out.println("Saving canceled");
        }
    }

    private void saveCatalog(String path) {
        path += "/catalog.xml";
        XMLEncoder encoder;
        try {
            encoder = new XMLEncoder(new BufferedOutputStream(new FileOutputStream(path)));
            encoder.writeObject(frame.getList());
            encoder.writeObject(frame.getCatalogTable());
            encoder.writeObject(frame.getCatalogTree());
            encoder.close();
//            FileOutputStream fileOut = new FileOutputStream(path);
//            ObjectOutputStream out = new ObjectOutputStream(fileOut);
//            out.writeObject(frame.getList());
//            out.writeObject(frame.getCatalogTable());
//            out.writeObject(frame.getCatalogTree());
//            out.close();
//            fileOut.close();
            System.out.println("Wrote CatalogList in " + path);
        } catch (IOException i) {
            i.printStackTrace();
        }
    }
}