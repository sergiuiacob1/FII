package view;

import javax.swing.*;
import java.awt.*;

public class CatalogFrame extends JFrame {
    private CatalogList list;
    private CatalogTable catalogTable;
    private CatalogTree catalogTree;
    private ControlPanel control;
    private String viewMode;

    public CatalogFrame(String viewMode) {
        super("Visual Document Manager");
        this.viewMode = viewMode;
        init(viewMode);
    }

    private void init(String viewMode) {
        DocumentForm form;

        this.getContentPane().setLayout(new BorderLayout());
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        form = new DocumentForm(this);
        this.getContentPane().add(form, BorderLayout.NORTH);

        control = new ControlPanel(this);
        this.getContentPane().add(control, BorderLayout.SOUTH);

        catalogTable = new CatalogTable();
        list = new CatalogList();
        catalogTree = new CatalogTree();

        switch (viewMode) {
            case "list":
                this.getContentPane().add(list, BorderLayout.CENTER);
                break;
            case "table":
                this.add(new JScrollPane(catalogTable.getTable()));
                break;
            case "tree":
                this.add(catalogTree);
                break;
            default:
                System.out.println("Invalid catalog view mode");
                System.exit(-1);

        }

        this.setSize(800, 400);
        //this.pack();
    }

    public void start() {
        this.setVisible(true);
    }

    public CatalogList getList() {
        return list;
    }

    public ControlPanel getControl() {
        return control;
    }

    public String getViewMode() {
        return viewMode;
    }

    public CatalogTable getCatalogTable() {
        return catalogTable;
    }

    public CatalogTree getCatalogTree() {
        return catalogTree;
    }
}