package lab4;

import java.io.*;
import java.io.FileNotFoundException;

public class ReportHtml {
    public void run(Catalog catalog) throws FileNotFoundException {
        Writer writer = null;
        try {
            writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("index.html"), "utf-8"));
            String html = new String();
            html += "<html><body><p>";
            for(Document doc : catalog.documents){
                html += doc;
                html += "<br>";
            }
            //html += catalog;
            html += "</p></body></html>";
            //System.out.println(html);
            writer.write(html);
            writer.close();

        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
