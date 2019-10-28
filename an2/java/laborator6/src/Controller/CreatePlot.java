package Controller;

import View.DrawingFrame;
import org.apache.batik.dom.GenericDOMImplementation;
import org.apache.batik.svggen.SVGGraphics2D;
import org.apache.batik.svggen.SVGGraphics2DIOException;
import org.w3c.dom.DOMImplementation;
import org.w3c.dom.Document;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.Random;
import java.util.Timer;

public class CreatePlot implements ActionListener {
    DrawingFrame frame;
    public CreatePlot(DrawingFrame frame) {
        this.frame = frame;
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        DOMImplementation domImpl = GenericDOMImplementation.getDOMImplementation();
        String svgNS = "http://www.w3.org/2000/svg";
        Document document = domImpl.createDocument(svgNS, "svg", null);

        SVGGraphics2D svgGenerator = new SVGGraphics2D(document);

        DotsDelay test = new DotsDelay(frame);
        test.paintSVG(svgGenerator);

        boolean useCSS = true; // we want to use CSS style attributes
        Writer out = null;
        OutputStream file = null;
        try {
            file = new FileOutputStream("output.svg");
        } catch (FileNotFoundException e1) {
            e1.printStackTrace();
        }
        try {
            out = new OutputStreamWriter(file, "UTF-8");
        } catch (UnsupportedEncodingException e1) {
            e1.printStackTrace();
        }
        try {
            svgGenerator.stream(out, useCSS);
        } catch (SVGGraphics2DIOException e1) {
            e1.printStackTrace();
        }
    }


}
