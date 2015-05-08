/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 *
 * @author Adam Sykes
 */
public class GameModel {
    List<Info> games;
    
    public GameModel(){
        games = new ArrayList<>();
    }
    
    public void makeGames(int which) throws FileNotFoundException{
        Scanner system;
        
        this.games.clear();
        
        switch(which){
            case 0:
                system = new Scanner(new FileReader("n64.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                    }
                break;
            case 1:
                system = new Scanner(new FileReader("gcn.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                    }
                break;
            case 2:
                system = new Scanner(new FileReader("wii.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                    }
                break;
            case 3:
                system = new Scanner(new FileReader("wiiu.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                    }
                break;
            case 4:
                system = new Scanner(new FileReader("PC.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                    }
                break;
            case 5:
                system = new Scanner(new FileReader("ps3.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                    }
                break;
            case 6:
                system = new Scanner(new FileReader("ps4.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                }
                break;
            case 7:
                system = new Scanner(new FileReader("xbox.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                }
                break;
            case 8:
                system = new Scanner(new FileReader("xbox360.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                }
                break;
            case 9:
                system = new Scanner(new FileReader("xboxone.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                }
                break;
            case 10:
                system = new Scanner(new FileReader("Mac.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                }
                break;
            case 11:
                system = new Scanner(new FileReader("All.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setSystem(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                }
                break;
            case 12:
                system = new Scanner(new FileReader("3ds.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                }
                break;
            case 13:
                system = new Scanner(new FileReader("ds.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                }
                break;
            case 14:
                system = new Scanner(new FileReader("gba.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                }
                break;
            case 15:
                system = new Scanner(new FileReader("gbc.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                }
                break;
            case 16:
                system = new Scanner(new FileReader("ps2.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                }
                break;
            case 17:
                system = new Scanner(new FileReader("psv.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                }
                break;
            case 18:
                system = new Scanner(new FileReader("psp.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                }
                break;
            case 19:
                system = new Scanner(new FileReader("linux.txt"));
                while(system.hasNextLine()){
                    Info game = new Info();
                    game.setTitle(system.nextLine());
                    game.setGenre(system.nextLine());
                    game.setESRB(system.nextLine());
                    game.setRating(system.nextLine());
                    game.setSummary(system.nextLine());
                    game.setPic(system.nextLine());
                    this.games.add(game);
                }
                break;
        }
    }
    
    public List getGames(){
        return this.games;
    }
}

