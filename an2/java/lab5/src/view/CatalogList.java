package view;

import javax.swing.*;

public class CatalogList extends JList implements java.io.Serializable {
    private DefaultListModel model;

    public CatalogList() {
        model = new DefaultListModel<ListModel>();
        String title = "<html><i><font color='blue'>" +
                "Catalog Documents" + "</font></i></html>";
        this.setBorder(BorderFactory.createTitledBorder(title));
        this.setModel(model);
    }

    public void addDocument(String item) {
        model.addElement(item);
    }

    @Override
    public DefaultListModel getModel() {
        return model;
    }
}
