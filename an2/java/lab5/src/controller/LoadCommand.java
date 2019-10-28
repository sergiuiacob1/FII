package controller;

import view.*;

import javax.swing.*;
import javax.swing.tree.DefaultMutableTreeNode;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.XMLDecoder;
import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Vector;

public class LoadCommand implements ActionListener {
    private CatalogFrame frame;
    private JFileChooser fileChooser;

    public LoadCommand(ControlPanel panel) {
        this.frame = panel.getFrame();

        fileChooser = new JFileChooser();
        fileChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
    }

    public void actionPerformed(ActionEvent e) {
        int rVal = fileChooser.showOpenDialog(frame.getControl());
        if (rVal == JFileChooser.APPROVE_OPTION) {
            System.out.println("Loading " + fileChooser.getSelectedFile().getAbsolutePath() + "...");
            loadCatalog(fileChooser.getSelectedFile().getAbsolutePath());
        }
        if (rVal == JFileChooser.CANCEL_OPTION) {
            System.out.println("Loading canceled");
        }
    }

    private void loadCatalog(String path) {
        CatalogList rez = new CatalogList();
        CatalogTable rezTable = new CatalogTable();
        CatalogTree rezTree = new CatalogTree();
        Vector<String> toAdd;
        try {
            XMLDecoder decoder;
            decoder = new XMLDecoder(new BufferedInputStream(new FileInputStream(path)));
            rez = (CatalogList) decoder.readObject();
            rezTable = (CatalogTable) decoder.readObject();
            rezTree = (CatalogTree) decoder.readObject();
//            FileInputStream fileIn = new FileInputStream(path);
//            ObjectInputStream in = new ObjectInputStream(fileIn);
//            rez = (CatalogList) in.readObject();
//            rezTable = (CatalogTable) in.readObject();
//            rezTree = (CatalogTree) in.readObject();
//            in.close();
//            fileIn.close();
        } catch (IOException i) {
            //i.printStackTrace();
            System.out.println("You may only select a CatalogList!");
        }
//        catch (ClassNotFoundException c) {
//            System.out.println("Class not found");
//            c.printStackTrace();
//        }
        frame.getList().getModel().removeAllElements();
        frame.getCatalogTable().removeData();

        for (int i = 0; i < rez.getModel().getSize(); ++i)
            frame.getList().addDocument(rez.getModel().get(i).toString());

        for (int i = 0; i < rezTable.getTable().getRowCount(); ++i) {
            toAdd = new Vector<>();
            for (int j = 0; j < rezTable.getTable().getColumnCount(); ++j) {
                toAdd.add(rezTable.getTable().getModel().getValueAt(i, j).toString());
            }
            frame.getCatalogTable().addDocument(toAdd);
        }

        for (int i = 0; i < rezTree.getModel().getChildCount(rezTree.getModel().getRoot()); ++i) {
            DefaultMutableTreeNode top = (DefaultMutableTreeNode) frame.getCatalogTree().getModel().getRoot();
            DefaultMutableTreeNode newNode = new DefaultMutableTreeNode(rezTree.getModel().getChild(rezTree.getModel().getRoot(), i));
            for (int j = 0; j < ((DefaultMutableTreeNode) rezTree.getModel().getChild(rezTree.getModel().getRoot(), i)).getChildCount(); ++j) {
                newNode.add(new DefaultMutableTreeNode(((DefaultMutableTreeNode) rezTree.getModel().getChild(rezTree.getModel().getRoot(), i)).getChildAt(j)));
            }
            top.add(newNode);
        }

        frame.getCatalogTree().reload();
    }
}
