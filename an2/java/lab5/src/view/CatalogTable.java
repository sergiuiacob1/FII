package view;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.util.Vector;

public class CatalogTable extends JList implements java.io.Serializable {
    private DefaultTableModel model;
    private JTable table;

    public CatalogTable() {
        model = new DefaultTableModel();
        table = new JTable(model);
        model.addColumn("File Name");
        model.addColumn("File Path");
        model.addColumn("Publish Year");
    }

    public void addDocument(Vector<String> item) {
        model.addRow(item);
    }

    public JTable getTable() {
        return table;
    }

    public void removeData() {
        model.setRowCount(0);
    }
}
