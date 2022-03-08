package com.company;

public class Foo {
    private String name_;
    private int id_;

    public Foo(){
        name_ = "";
        id_ = 0;
    }

    public void SetName(String name){
        this.name_ = name;
    }
    public String GetName() {
        return name_;
    }
    public void IncreaseId(){
        id_++;
    }
}
