package org.memes.dank.smarthouse;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;

public class lightsActivity extends AppCompatActivity {
    ESPNetwork espn;
    String I_P;
    Thread ESPNThread;

    private final String ATTIC_COMAND = "ATIC";
    private final String BEDROOM1_COMAND = "BED1";
    private final String BEDROOM2_COMAND = "BED2";
    private final String BATHROOM_COMAND = "BATH";
    private final String LIVINGROOM_COMAND = "LVRM";
    private final String KITCHEN_COMAND = "KCHN";
    private final String PARTY_COMAND = "PART";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //Remove notification bar
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_lights);
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

    //button press for bedroom1
    public void controlBedroom1(View view){
        espn.write(BEDROOM1_COMAND);
    }
    //button press for bedromm2
    public void controlBedroom2(View view){
        espn.write(BEDROOM2_COMAND);
    }
    //button press for the bathroom
    public void controlBathroom(View view){
        espn.write(BATHROOM_COMAND);
    }
    //button press for the living room
    public void controlLivingRoom(View view){
        espn.write(LIVINGROOM_COMAND);
    }
    //button press for the kitchen
    public void controlKitchen(View view){
        espn.write(KITCHEN_COMAND);
    }
    //button press for the attic
    public void controlAttic(View view){
        espn.write(ATTIC_COMAND);
    }
    //button press for party mode
    public void controlParty(View view){
        espn.write(PARTY_COMAND);
    }
    ////button press to go back to selection menu
    public void toMenu(View view){
        Intent intent = new Intent(this, selectActionActivity.class);

        intent.putExtra("IP", I_P);
        startActivity(intent);
    }


}
