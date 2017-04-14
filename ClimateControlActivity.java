package org.memes.dank.smarthouse;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.content.Intent;
import android.view.WindowManager;

public class ClimateControlActivity extends AppCompatActivity {
    String I_P;
    ESPNetwork espn;
    Thread ESPNThread;
    private String CONTROL_HEAT = "HEAT";
    private String CONTROL_AC = "COLD";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //Remove notification bar
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_climate_control);
        //get IP form previous activity
        Intent intent = getIntent();
        I_P = intent.getExtras().getString("I_P");

        espn = new ESPNetwork(I_P);
    }

    //each time the activity resumes we need to create a socket using a sepreate thread
    protected void onResume(){
        super.onResume();
        //change this to get it from before
        //open a socket on another thread
        //  espn = new ESPNetwork(I_P); //may change this?
        ESPNThread = new Thread(espn);
        ESPNThread.start();
    }


    //each time the activity would be removed from the screen we want to close the socket
    //so that if the app closes the socket will allready be closed
    protected void onPause() {
        super.onPause();
        espn.shutDownSocket();

    }

    //method that runs when heat button is pressed
    public void controlHeat(View view){
        espn.write(CONTROL_HEAT);
    }
    //method that runs when AC button is pressed
    public void controlAC(View view) {
        espn.write(CONTROL_AC);
    }

    public void toMenu(View view){
        Intent intent = new Intent(this, selectActionActivity.class);

        intent.putExtra("IP", I_P);
        startActivity(intent);
    }

}
