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
    private InetAddress addr;
    private String hostName;
    private final int PORT = 333;
    private PrintWriter toBeagle;
    private static final String TAG = Init.class.getSimpleName();

    public void run(){
        //Set thread priorty to be background to reduce resource consumption
        android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_BACKGROUND);
        try{
            addr = InetAddress.getByName("10.24.0.166");
            hostName = addr.getHostName();

            espSocket = new Socket(hostName, PORT);

            OutputStream out = espSocket.getOutputStream();
            toBeagle = new PrintWriter(out,true); //true for auto flushing of printwriter

            //need to close
            //toStorageMan.close();

        }
        catch(UnknownHostException e){
            Log.d(TAG,"UnknownHost Exceptipon",e);
        }
        catch (IOException e){
            Log.d(TAG,"IOException",e);
        }
        catch(Exception e){
            Log.d(TAG,"ALL exceptions",e);
        }
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

    }
}
