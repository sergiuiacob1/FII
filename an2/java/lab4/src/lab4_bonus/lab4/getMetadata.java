package lab4;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

import org.apache.tika.exception.TikaException;
import org.apache.tika.metadata.Metadata;
import org.apache.tika.parser.AutoDetectParser;
import org.apache.tika.parser.ParseContext;
import org.apache.tika.parser.Parser;
import org.apache.tika.sax.BodyContentHandler;

import org.xml.sax.SAXException;


public class getMetadata {
        public void extract(Catalog catalog) throws IOException, TikaException, SAXException {
            //File file = new File();
            //System.out.print(catalog.documents.get(0));
            File file = new File(catalog.documents.get(0).getPath());
            //File file = new File("chopin.jpg");
            //
            Parser parser  = new AutoDetectParser();
            BodyContentHandler handler = new BodyContentHandler();
            Metadata metadata = new Metadata();
            FileInputStream inputStream = new FileInputStream(file);
            ParseContext context = new ParseContext();

            parser.parse(inputStream, handler, metadata, context);
            System.out.println(handler.toString());

            String[] metadataNames = metadata.names();
            for(String name : metadataNames){
                System.out.println(name + ": " + metadata.get(name));
            }

        }
}
