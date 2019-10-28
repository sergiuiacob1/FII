package controller;

import view.CatalogFrame;
import view.ControlPanel;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class UseShellCommand implements ActionListener {
    private CatalogFrame catalogFrame;

    public UseShellCommand(ControlPanel controlPanel) {
        this.catalogFrame = controlPanel.getFrame();
    }

    public void actionPerformed(ActionEvent e) {
        catalogFrame.setVisible(false); //you can't see me!
        //catalogFrame.dispose(); //Destroy the JFrame object
        System.out.println("Start writing commands...");
    }
}
