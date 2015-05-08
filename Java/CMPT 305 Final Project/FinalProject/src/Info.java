/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Adam Sykes
 */
public class Info{
    private String title;
    private String genre;
    private String esrb;
    private String system;
    private String rating;
    private String summary;
    private String pic;
    
    public Info(){
        title = null;
        genre = null;
        esrb = null;
        system = null;
        rating = null;
        summary = null;
        pic = null;
    }
    
    public void setTitle(String s){this.title = s;}
    public void setGenre(String s){this.genre = s;}
    public void setESRB(String s){this.esrb = s;}
    public void setSystem(String s){this.system = s;}
    public void setRating(String s){this.rating = s;}
    public void setSummary(String s){this.summary = s;}
    public void setPic(String s){this.pic = s;}
    
    
    public String getTitle(){return this.title;}
    public String getGenre(){return this.genre;}
    public String getESRB(){return this.esrb;}
    public String getSystem(){return this.system;}
    public String getRating(){return this.rating;}
    public String getSummary(){return this.summary;}
    public String getPic(){return this.pic;}
    
    @Override
    public String toString(){
        return title+' '+genre+' '+esrb+' '+system+' '+rating+' '+summary+' '+pic;
    }
}
