package org.memes.dank.smarthouse;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.view.View;


public class Init extends AppCompatActivity {
    ESPNetwork ESPN;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_init);
        ESPN = new ESPNetwork();
        Thread ESPNThread =new Thread(ESPN);
        ESPNThread.start();



    }
    public void sendData (View view) {
        ESPN.write("Hello");
    }
}
