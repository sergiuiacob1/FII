package controller;

import view.CatalogFrame;
import view.DocumentForm;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AddCommand implements ActionListener {
    private CatalogFrame catalogFrame;
    private DocumentForm form;

    public AddCommand(DocumentForm form) {
        this.catalogFrame = form.getFrame();
        this.form = form;
    }

    public void actionPerformed(ActionEvent e) {
        if (!form.areFieldsCompleted()) return;
        if (catalogFrame.getViewMode().equals("list"))
            catalogFrame.getList().addDocument(form.toString());
        else if (catalogFrame.getViewMode().equals("table"))
            catalogFrame.getCatalogTable().addDocument(form.getObjectInput());
        else
            catalogFrame.getCatalogTree().addDocument(form.toString());
    }
}
