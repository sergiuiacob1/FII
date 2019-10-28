package com.example.sergiu.lab12_android;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.List;


public class ShowListActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_show_list);

        ListView lv = findViewById(R.id.showObjects);
        List<String> names = new ArrayList<>();
        List<AppObject> objects = new FileIO().getObjects(this);

        for (int i = 0; i < objects.size(); ++i)
            names.add(objects.get(i).getName());
        ArrayAdapter<String> arrayAdapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1,  names);

        lv.setAdapter(arrayAdapter);
    }
}