package org.memes.dank.smarthouse;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.EditText;
import android.content.Intent;

public class selectActionActivity extends AppCompatActivity {
    ESPNetwork espn;
    String I_P;
    Thread ESPNThread;
    private static final String TAG = Init.class.getSimpleName();

    private static final String TURN_ON_COMMAND = "HONN";
    private static final String TURN_OFF_COMMAND = "HOFF";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //Remove notification bar
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_select_action);


        //Get the intent  and then get the IP from that intent
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



    public void goToSecurityActivity(View view){
        //go to security activity take the I.P and pass it along
        Intent intent = new Intent(this, SecurityActivity.class);
        //send the I_P to the next Activity
        intent.putExtra("IP", I_P);
        //start next activity
        startActivity(intent);
    }

    public void goToClimateActivity(View view){
        //go to climate activity take the I.P and pass it along
        Intent intent = new Intent(this, ClimateControlActivity.class);
        //send the I_P to the next Activity
        intent.putExtra("IP", I_P);
        //start next activity
        startActivity(intent);
    }

    public void goToLightActivity(View view){
        //go to light activity take the I.P and pass it along
        Intent intent = new Intent(this, lightsActivity.class);
        //send the I_P to the next Activity
        intent.putExtra("IP", I_P);
        //start next activity
        startActivity(intent);
    }

    public void turnOnHouse(View view){
        espn.write(TURN_ON_COMMAND);
    }

    public void turnOffHouse(View view){
        espn.write(TURN_OFF_COMMAND);
    }

}
