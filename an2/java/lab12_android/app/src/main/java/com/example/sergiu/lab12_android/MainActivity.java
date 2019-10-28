package com.example.sergiu.lab12_android;

import android.app.AlertDialog;
import android.app.DatePickerDialog;
import android.content.Context;
import android.content.Intent;
import android.support.design.widget.TextInputEditText;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.format.DateUtils;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button button = (Button) findViewById(R.id.saveButton);
        Button dateButton = findViewById(R.id.dateButton);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                saveInputs();
            }
        });

        dateButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                chooseDate();
            }
        });

        Button listButton = findViewById(R.id.listButton);

        listButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showList();
            }
        });

        checkUpcomingEvents();
    }

    private void checkUpcomingEvents() {
        Date currentDate = Calendar.getInstance().getTime();
        List<AppObject> objects = new FileIO().getObjects(this);
        if (objects == null) return;

        for (int i = 0; i < objects.size(); ++i)
            if (!sameDay (objects.get(i).getDate(), currentDate)) {
                objects.remove(i);
                --i;
            }

        if (objects.size() == 0)
            return;

        AlertDialog.Builder mBuilder = new AlertDialog.Builder(this);
        View mView = getLayoutInflater().inflate(R.layout.events_today, null);
        mBuilder.setView(mView);

        ListView lv = mView.findViewById(R.id.upcomingEvents);
        List<Map<String, String>> data = new ArrayList<Map<String, String>>();
        for (AppObject object: objects) {
            Map<String, String> datum = new HashMap<String, String>(2);
            datum.put("Name", object.getName());
            datum.put("Details", object.getDetails());
            data.add(datum);
        }
        SimpleAdapter adapter = new SimpleAdapter(this, data,
                android.R.layout.simple_list_item_2,
                new String[] {"Name", "Details"},
                new int[] {android.R.id.text1,
                        android.R.id.text2});
        lv.setAdapter(adapter);

        final AlertDialog dialog = mBuilder.create();
        dialog.show();
    }

    private boolean sameDay(Date d1, Date d2) {
        if (d1.getYear() != d2.getYear())
            return false;
        if (d1.getMonth() != d2.getMonth())
            return false;
        return d1.getDate() == d2.getDate();
    }

    private void showList() {
        Intent myIntent = new Intent(this, ShowListActivity.class);
        startActivity(myIntent);
    }

    private void chooseDate() {
        int d, m, y;
        final Calendar calendar = Calendar.getInstance();
        d = calendar.get(Calendar.DAY_OF_MONTH);
        m = calendar.get(Calendar.MONTH);
        y = calendar.get(Calendar.YEAR);
        DatePickerDialog datePickerDialog = new DatePickerDialog(MainActivity.this, new DatePickerDialog.OnDateSetListener() {
            @Override
            public void onDateSet(DatePicker view, int year, int month, int dayOfMonth) {
                TextInputEditText dateShow = findViewById(R.id.dateShow);
                dateShow.setText(new StringBuilder().append(dayOfMonth).append("-").append(month + 1).append("-").append(year).append(" "));
            }
        }, y, m, d);
        datePickerDialog.show();
    }

    private void saveInputs() {
        TextInputEditText name = findViewById(R.id.nameInput);
        TextInputEditText detalii = findViewById(R.id.detalii);
        TextInputEditText data = findViewById(R.id.dateShow);

        Date date = null;
        try {
            date = new SimpleDateFormat("dd-MM-yyyy").parse(data.getText().toString());
        } catch (ParseException e) {
            e.printStackTrace();
        }

        AppObject appObject = new AppObject(name.getText().toString(), detalii.getText().toString(), date);
        new FileIO().saveObject(MainActivity.this, appObject);
    }
}
