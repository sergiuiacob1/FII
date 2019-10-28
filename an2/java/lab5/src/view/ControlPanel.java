package view;

import controller.*;

import javax.swing.*;

public class ControlPanel extends JPanel {
    private final CatalogFrame frame;
    private JButton loadBtn, saveBtn, reportBtn, openBtn, useShell;

    ControlPanel(CatalogFrame frame) {
        this.frame = frame;
        loadBtn = new JButton("Load");
        saveBtn = new JButton("Save");
        reportBtn = new JButton("Report");
        openBtn = new JButton("Open");
        useShell = new JButton("Use shell");
        init();
    }

    private void init() {
        add(loadBtn);
        add(saveBtn);
        add(reportBtn);
        add(openBtn);
        add(useShell);

        loadBtn.addActionListener(new LoadCommand(this));
        saveBtn.addActionListener(new SaveCommand(this));
        reportBtn.addActionListener(new ReportCommand(this));
        openBtn.addActionListener(new OpenCommand(this));
        useShell.addActionListener(new UseShellCommand(this));
    }

    public CatalogFrame getFrame() {
        return frame;
    }
}
