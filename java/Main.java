import java.io.FileNotFoundException;
import java.io.IOException;

import stl.Stl;

public class Main{
    public static void main(String[] args){
        
        try{
            Stl stl = Stl.read("model.stl");

            System.out.println(stl);

            stl.write("model.edit.stl");
        }catch(FileNotFoundException e){
            e.printStackTrace(System.err);
        }catch(IOException e){
            e.printStackTrace(System.err);
        }

    }
}