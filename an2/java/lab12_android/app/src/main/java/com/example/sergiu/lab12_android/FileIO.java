package com.example.sergiu.lab12_android;

import android.content.Context;
import android.support.design.widget.TextInputEditText;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.List;

public class FileIO {

    public void saveObject(Context context, AppObject appObject) {
        String fileName = "lab12";

        List<AppObject> objects = getObjects(context);

        if (objects == null)
            objects = new ArrayList<>();
        objects.add(appObject);

        try {
            FileOutputStream fos = context.openFileOutput(fileName, Context.MODE_PRIVATE);
            ObjectOutputStream os = new ObjectOutputStream(fos);
            os.writeObject(objects);
            os.close();
            fos.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public List<AppObject> getObjects(Context context){
        List<AppObject> res = null;
        try {
            FileInputStream fis = context.openFileInput("lab12");
            ObjectInputStream is = new ObjectInputStream(fis);
            res = (List<AppObject>) is.readObject();
            is.close();
            fis.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

        return res;
    }
}
