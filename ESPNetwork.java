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
    private final String PRESET_IP ="10.24.0.166" ;
    private final int PORT = 333;
    private PrintWriter toBeagle;
    private static final String TAG = Init.class.getSimpleName();

    public void run(){
        //Set thread priorty to be background to reduce resource consumption
        android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_BACKGROUND);

    }

    public boolean write(String msg){
        boolean succes = false;
        try{
            toBeagle.println(msg);
            succes = true;
        }
        catch(Exception e){
            Log.d(TAG,"ALL exceptions",e);
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
    public boolean makeSocket(String IP){
        boolean open = false;
        try{
            InetAddress addr = InetAddress.getByName("10.24.0.166");
            String hostName = addr.getHostName();

            espSocket = new Socket(hostName, PORT);

            OutputStream out = espSocket.getOutputStream();
            toBeagle = new PrintWriter(out,true); //true for auto flushing of printwriter
            //if the socket connets
            //and we can write to it return true
            open = true;
        }
        catch(Exception e){
            Log.d(TAG,"Error opening a socket",e);
        }
        return open;
    }
}
