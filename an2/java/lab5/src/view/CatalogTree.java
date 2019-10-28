package view;

import controller.OpenCommand;

import javax.swing.*;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;

public class CatalogTree extends JTree implements java.io.Serializable {
    private DefaultMutableTreeNode top;
    private static int nrNodes = 0;

    public CatalogTree() {
        super(new DefaultMutableTreeNode("Catalog Documents"));
        top = (DefaultMutableTreeNode) this.getModel().getRoot();

        CatalogTree thisTree = this;
        this.addTreeSelectionListener(new TreeSelectionListener() {
            @Override
            public void valueChanged(TreeSelectionEvent treeSelectionEvent) {
                DefaultMutableTreeNode node = (DefaultMutableTreeNode) thisTree.getLastSelectedPathComponent();
                String[] parts = node.toString().split(":| ");
                if (!parts[0].equals("Path")) return;
                System.out.println("Opening path " + parts[2]);
                try {
                    new OpenCommand(null).openFile(parts[2]);
                } catch (NullPointerException e) {
                    System.out.println("Path doesn't exist");
                } catch (IllegalArgumentException e) {
                    System.out.println("Path doesn't exist");
                }
            }
        });
    }

    public void addDocument(String item) {
        DefaultMutableTreeNode newNode;
        this.nrNodes++;
        newNode = new DefaultMutableTreeNode("Document " + String.valueOf(this.nrNodes));
        top.add(newNode);
        String[] parts = item.split(" |,|\\[|\\]");
        newNode.add(new DefaultMutableTreeNode("Name: " + parts[0]));
        newNode.add(new DefaultMutableTreeNode("Year: " + parts[2]));
        newNode.add(new DefaultMutableTreeNode("Path: " + parts[3]));
        reload();
    }

    public void reload() {
        ((DefaultTreeModel) this.getModel()).reload();
    }
}
