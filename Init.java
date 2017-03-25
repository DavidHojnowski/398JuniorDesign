package org.memes.dank.smarthouse;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.view.View;
import android.widget.EditText;


public class Init extends AppCompatActivity {
    ESPNetwork espn;
    Thread ESPNThread;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_init);

        //open a socket on another thread
        espn = new ESPNetwork();
        ESPNThread =new Thread(espn);
        ESPNThread.start();
    }

    //each time the activity would be removed from the screen we want to close the socket
    //so that if the app closes the socket will allready be closed
    protected void onPause(){
        super.onPause();
        espn.shutDownSocket();
    }
    //on resume happens directly before the view becomes visible to the user
    //also on resume happends whenever the activity is paused and starts again
    public void connectToSmartHouse (View view) {
        EditText text = (EditText) findViewById(R.id.I_P_Input);
        String I_P_Address = text.getText().toString();
        if(espn.makeSocket(I_P_Address)){
            //constructed a socket susesfully now can move to the next actvity
            goToSelectAction(view);

        }
        else{
            //prompt user to enter a correct I.P
        }

    }
    private void goToSelectAction(View view){
        Intent intent = new Intent(this,selectActionActivity.class);
        //may need to push some data somehow

        startActivity(intent);
    }

    public void DEBUG(View view){
        goToSelectAction(view);
    }
}
