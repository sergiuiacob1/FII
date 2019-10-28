package view;

import controller.AddCommand;

import javax.swing.*;
import java.util.Vector;

public class DocumentForm extends JPanel {
    private final CatalogFrame frame;
    private JLabel titleLabel, pathLabel, yearLabel;
    private JTextField docTitleText, docPathText;
    private JButton addButton;
    private JSpinner yearField = new JSpinner(new SpinnerNumberModel(1950, 1900, 2018, 1));

    DocumentForm(CatalogFrame catalogFrame) {
        this.frame = catalogFrame;
        init();
    }

    private void init() {
        this.setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
        pathLabel = new JLabel("Path in the local file system");
        titleLabel = new JLabel("Title of the document");
        yearLabel = new JLabel("Publication Year");

        addButton = new JButton("Add to repository");
        docTitleText = new JTextField();
        docPathText = new JTextField();

        this.add(titleLabel);
        this.add(docTitleText);
        this.add(pathLabel);
        this.add(docPathText);
        this.add(yearLabel);
        this.add(yearField);
        this.add(addButton);

        addButton.addActionListener(new AddCommand(this));
    }

    public Boolean areFieldsCompleted() {
        return !docTitleText.getText().equals("") && !docPathText.getText().equals("");
    }

    @Override
    public String toString() {
        return docTitleText.getText() + ", " + yearField.getValue().toString() + "[" + docPathText.getText() + "]";
    }

    public CatalogFrame getFrame() {
        return frame;
    }

    public Vector<String> getObjectInput() {
        Vector<String> rez = new Vector<>();
        rez.add(docTitleText.getText());
        rez.add(docPathText.getText());
        rez.add(yearField.getValue().toString());
        return rez;
    }
}
