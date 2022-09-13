import java.io.FileNotFoundException;

import stl.Stl;

public class Main{
    public static void main(String[] args){
        
        try{
            Stl stl = Stl.read("model.stl");

            System.out.println(stl);

            for(int i=0; i<stl.getTriangles().size(); i++){
                System.out.println(stl.getTriangles().get(i));
            }

            stl.write("model.edit.stl");
        }catch(FileNotFoundException e){
            e.printStackTrace(System.err);
        }

    }
}