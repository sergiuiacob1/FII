package com.example.sergiu.lab12_android;

import java.util.Date;

public class AppObject implements java.io.Serializable{
    private String name;
    private String details;
    private Date date;

    AppObject(String name, String details, Date date){
        this.name = name;
        this.details = details;
        this.date = date;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDetails() {
        return details;
    }

    public void setDetails(String details) {
        this.details = details;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }
}
