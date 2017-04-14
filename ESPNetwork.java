package org.memes.dank.smarthouse;

import android.util.Log;

import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.io.PrintWriter; //a print writer to write to sever over socket
import java.io.OutputStream; //for printwriter

/**
 * Created by David on 3/20/2017.
 */

public class ESPNetwork implements Runnable {
    private Socket espSocket;
    private final String PRESET_IP ="10.24.0.223" ;
    private String ipAddress;
    private final int PORT = 333;
    private PrintWriter toBeagle;
    private static final String TAG = Init.class.getSimpleName();
    private boolean conected;

    public ESPNetwork(String I_P){
        ipAddress = I_P;
        conected = false;
    }

    public void run(){
        //Set thread priorty to be background to reduce resource consumption
        android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_BACKGROUND);
        try {
            InetAddress addr = InetAddress.getByName(PRESET_IP); //Hard coded IP
            //InetAddress addr = InetAddress.getByName(ipAddress); IP that was enterd, but for whatever reason doesnt work

            String hostName = addr.getHostName();

            espSocket = new Socket(hostName, PORT);

            OutputStream out = espSocket.getOutputStream();
            toBeagle = new PrintWriter(out, true); //true for auto flushing of printwriter
            //At this point could aslo create a buffered reader if you wanted to read in some data

            //if the socket connets
            //and we can write to it return true
            conected = true; //this never ended up working
       } catch (Exception e) {
          Log.d(TAG, "Error opening a socket", e);
       }
    }

    //not implemented
   public boolean isConnected(){
        return conected;
    }

    public boolean write(String msg){
        boolean succes = false;
        try{
            toBeagle.println(msg);
            succes = true;
        }
        catch(Exception e){
            Log.d(TAG,"Writing not working",e);
        }
        return succes;
    }

    public void shutDownSocket(){
        try{
            if(espSocket != null){
                espSocket.close();
            }
            if(toBeagle != null){
                toBeagle.close();
            }
        }
        catch(Exception e){
            Log.d(TAG,"Error shutting down socket",e);
        }

    }

}
