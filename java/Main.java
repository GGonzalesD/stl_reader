import java.io.FileNotFoundException;

import stl.Stl;

public class Main{
    public static void main(String[] args){
        
        try{
            Stl stl = Stl.read("model.stl");

            System.out.println(stl);

            stl.write("model.edit.stl");
        }catch(FileNotFoundException e){
            e.printStackTrace(System.err);
        }

    }
}