package com.ustudents.ghostlab.listener;

import com.ustudents.ghostlab.client.Client;
import com.ustudents.ghostlab.communication.Reader;
import com.ustudents.ghostlab.communication.Sender;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

public class TCPRunnable implements Runnable{

    private final Client client;
    private final BufferedReader br;
    private volatile boolean exit;
    //private final PrintWriter pw;
    //private String username;


    public TCPRunnable(Client client/*, String username*/) throws IOException{
        this.client = client;
        this.br = new BufferedReader(new InputStreamReader(client.getSocket().getInputStream()));
        exit = false;
        //this.pw = new PrintWriter(new OutputStreamWriter(client.getSocket().getOutputStream()));
        //this.username = username;
    }

    public void wantExit(){
        this.exit = true;
    }

    /*public String getUsername(){
        return username;
    }

    public void setUsername(String username){
        this.username = username;
    }

    public void send(String action) throws IOException{
        Sender.send(pw, action);
    }*/

    @Override
    public void run() {
        Reader reader = new Reader(client, this);
        try {
            while(!exit && !client.getSocket().isClosed()){
                reader.read(br);
            }
            
        } catch (IOException e) {
            client.addContentTologs("warning:", "Exception", 1);
            e.printStackTrace();
        }


        /*try{
            String question = "What to you want to do ? (move/list/messall/messto/quit)";
            InteractionInGamePhase iigp = new InteractionInGamePhase(client);
            iigp.putQuestionOnGamePhase(br, pw, question, new String[]{"move","list","messall","messto","quit"}, sc);

        }catch (Exception e){
            e.printStackTrace();
        }*/
    }
}
