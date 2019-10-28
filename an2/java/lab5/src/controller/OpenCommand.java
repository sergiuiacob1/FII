package controller;

import view.CatalogFrame;
import view.ControlPanel;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class OpenCommand implements ActionListener {
    private CatalogFrame frame;
    private JFileChooser fileOpener;

    public OpenCommand(ControlPanel controlPanel) {
        if (controlPanel != null)
            this.frame = controlPanel.getFrame();
        fileOpener = new JFileChooser();
        fileOpener.setFileSelectionMode(JFileChooser.FILES_ONLY);
    }

    public void actionPerformed(ActionEvent e) {
        System.out.println("Select a file to open");
        int rVal = fileOpener.showOpenDialog(frame.getControl());
        if (rVal == JFileChooser.APPROVE_OPTION) {
            System.out.println("Opening " + fileOpener.getSelectedFile().getAbsolutePath());
            openFile(fileOpener.getSelectedFile().getAbsolutePath());
        }
        if (rVal == JFileChooser.CANCEL_OPTION) {
            System.out.println("Open canceled");
        }
    }

    public void openFile(String path) {
        try {
            Desktop desktop = Desktop.getDesktop();
            desktop.open(new File(path));
        } catch (IOException e) {
            System.out.println("Opening failed");
        }
    }
}
