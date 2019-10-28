package controller;

import view.CatalogFrame;
import view.ControlPanel;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;

public class ReportCommand implements ActionListener {
    private CatalogFrame frame;
    private JFileChooser fileSaver;

    public ReportCommand(ControlPanel controlPanel) {
        this.frame = controlPanel.getFrame();
        fileSaver = new JFileChooser();
        fileSaver.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
    }

    public void actionPerformed(ActionEvent e) {
        System.out.println("Select a directory to save the report");
        int rVal = fileSaver.showSaveDialog(frame.getControl());
        if (rVal == JFileChooser.APPROVE_OPTION) {
            System.out.println("Saving in " + fileSaver.getSelectedFile().getAbsolutePath());
            saveReport(fileSaver.getSelectedFile().getAbsolutePath());
        }
        if (rVal == JFileChooser.CANCEL_OPTION) {
            System.out.println("Saving canceled");
        }
    }

    private void saveReport(String path) {
        path += "/catalog_report.html";
        Writer writer;
        try {
            File file = new File(path);
            if (!file.createNewFile()) {
                System.out.println("Failed to create file catalog_report.html");
            }
            writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(path), "utf-8"));
            StringBuilder html = new StringBuilder();
            html.append("<html><body><p>");
            if (frame.getViewMode().equals("list")) {
                for (int i = 0; i < frame.getList().getModel().getSize(); ++i) {
                    html.append(frame.getList().getModel().get(i));
                    html.append("<br>");
                }
            } else {
                for (int i = 0; i < frame.getCatalogTable().getTable().getRowCount(); ++i) {
                    for (int j = 0; j < frame.getCatalogTable().getTable().getColumnCount(); ++j) {
                        html.append(frame.getCatalogTable().getTable().getModel().getValueAt(i, j));
                        html.append(" ");
                    }
                    html.append("<br>");
                }
            }
            html.append("</p></body></html>");
            writer.write(html.toString());
            writer.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
