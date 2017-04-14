package org.memes.dank.smarthouse;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.EditText;


public class Init extends AppCompatActivity {
    ESPNetwork espn;
    Thread ESPNThread;
    private static final String TAG = Init.class.getSimpleName();
    String I_P_Address;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //Remove notification bar
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_init);
    }

    //each time the activity would be removed from the screen we want to close the socket
    //so that if the app closes the socket will allready be closed
    protected void onPause() {
        super.onPause();
        //must include this for the case where we haven't given it an I.P
        if(espn != null)
            espn.shutDownSocket();
    }
    public void connectToSmartHouse (View view) {
        //get the ented IP addres fom this activity
        EditText text = (EditText) findViewById(R.id.I_P_Input);
       I_P_Address = text.getText().toString();

        //open a socket on another thread
        espn = new ESPNetwork(I_P_Address);
        ESPNThread = new Thread(espn);
        //starting the thread is what builds the socket and also the print writer
        ESPNThread.start();

        goToSelectAction(view);

      /*  if(espn.write("Connected to INIT activity")){
           Log.d(TAG, "Socket is Open");

        }
        else{
            Log.d(TAG, "Socket is  not Open");
            //prompt user to enter a correct I.P
        }*/

    }
    private void goToSelectAction(View view){
        Intent intent = new Intent(this,selectActionActivity.class);
        //may need to push some data somehow
        intent.putExtra("IP", I_P_Address);
        startActivity(intent);
    }

    public void DEBUG(View view){
        goToSelectAction(view);
    }
}
