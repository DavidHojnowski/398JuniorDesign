package org.memes.dank.smarthouse;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;


public class Init extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_init);

        (new Thread(new ESPNetwork())).start();


    }
}
