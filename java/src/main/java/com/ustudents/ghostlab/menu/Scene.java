package com.ustudents.ghostlab.menu;

import com.ustudents.application.graphic.ImGuiManager;
import com.ustudents.ghostlab.client.Client;

import org.lwjgl.glfw.GLFW;

import imgui.ImGui;
import imgui.ImGuiListClipper;
import imgui.callback.ImListClipperCallback;
import imgui.flag.ImGuiWindowFlags;
import static java.lang.System.exit;

public abstract class Scene {

    protected final Client client;

    public Scene(Client client){
        this.client = client;
    }

    protected void header(){
        ImGui.setNextWindowPos(0, 0);
        ImGui.setNextWindowSize(ImGui.getIO().getDisplaySizeX(), ImGui.getIO().getDisplaySizeY() * 0.6f);
        ImGui.begin("Ghostlab Client", ImGuiWindowFlags.NoResize | ImGuiWindowFlags.NoMove | ImGuiWindowFlags.NoCollapse | ImGuiWindowFlags.MenuBar);

        if (ImGui.beginMenuBar()) {
            if (ImGui.beginMenu("File")) {
                if (ImGui.menuItem("Quit")) {
                    client.quit();
                }

                ImGui.endMenu();
            }

            ImGui.endMenuBar();
        }

        ImGui.end();
    }

    protected void footer(){
        ImGui.setNextWindowPos(0, 0);
        ImGui.setNextWindowSize(ImGui.getIO().getDisplaySizeX(), ImGui.getIO().getDisplaySizeY() * 0.6f);
        ImGui.begin("Ghostlab Client", ImGuiWindowFlags.NoResize | ImGuiWindowFlags.NoMove | ImGuiWindowFlags.NoCollapse | ImGuiWindowFlags.MenuBar);

        if (ImGui.beginMenuBar()) {
            if (ImGui.beginMenu("File")) {
                if (ImGui.menuItem("Quit")) {
                    client.quit();
                }

                ImGui.endMenu();
            }

            ImGui.endMenuBar();
        }



        ImGui.end();

        

        ImGui.setNextWindowPos(0, ImGui.getIO().getDisplaySizeY() * 0.6f);
        ImGui.setNextWindowSize(ImGui.getIO().getDisplaySizeX(), ImGui.getIO().getDisplaySizeY() * 0.4f);
        ImGui.begin("Console", ImGuiWindowFlags.NoResize | ImGuiWindowFlags.NoMove | ImGuiWindowFlags.NoCollapse | ImGuiWindowFlags.MenuBar);

        if (ImGui.beginMenuBar()) {
            if (ImGui.beginMenu("View")) {
                if (ImGui.menuItem("Clear Logs")) {
                    client.getLogs().clear();
                }

                ImGui.separator();

                ImGui.menuItem("Show Info", null, client.getConsoleShowInfo());
                ImGui.menuItem("Show Warning", null, client.getConsoleShowWarning());
                ImGui.menuItem("Show Error", null, client.getConsoleShowError());

                ImGui.endMenu();
            }

            ImGui.endMenuBar();
        }

        ImGui.text("Enter a command:");
        ImGui.sameLine();
        ImGui.inputText("##Command", client.getConsoleCommand());
        ImGui.sameLine();

        if ((ImGui.button("Send")) || ImGui.isKeyPressed(GLFW.GLFW_KEY_ENTER)) {
            // TODO: Execute command
            
            String command = client.getConsoleCommand().get();
            client.addContentTologs("$", command);
            if(command.equals("q") || command.equals("e") ||
               command.equals("quit") || command.equals("exit")){
                exit(0);
            }else if(command.equals("h") || command.equals("help")){
                client.helpcommand();
            }else if(command.equals("v") || command.equals("version")){
                client.addContentTologs("client:", "version : 1.0.0");
            }else{
                client.addContentTologs("client: warning:", "invalid option `" + command + "`!");
                client.addContentTologs("client: warning:", "use `h` for more informations.");
            }
            client.getConsoleCommand().clear();
        }

        ImGui.beginChild("##Logs", 0, 0, true, ImGuiWindowFlags.HorizontalScrollbar);
        ImGui.pushFont(ImGuiManager.firaCode);

        ImGuiListClipper.forEach(client.getLogs().size(), new ImListClipperCallback() {
            public void accept(int i) {
                String command = client.getLogs().get(i);
                if(command.startsWith("client: warning:")) 
                    ImGui.textColored(215, 215, 0, 255, command);
                else if(command.startsWith("client: error:"))
                    ImGui.textColored(255, 0, 0, 255, command);   
                else if(command.startsWith("$"))
                    ImGui.textColored(57, 255, 20, 255, command); 
                else
                    ImGui.textUnformatted(command);
            }
        });

        // TODO: Scroll quand tu rajoute un element dans logs
        //if (consoleShouldScroll) {
        //    ImGui.setScrollHereX(1.0f);
        //    ImGui.setScrollHereY(1.0f);
        //}

        ImGui.popFont();
        ImGui.endChild();

        ImGui.end();

        //ImGui.showDemoWindow();;
    }
    
}
