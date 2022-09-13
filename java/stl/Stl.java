package stl;

import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Vector;

public class Stl {
    private String header;
    private Vector<Triangle> triangles;

    public Stl(String header_, Vector<Triangle> triangles_){
        header = header_;
        triangles = triangles_;
    }

    public static Stl read(String filename) throws FileNotFoundException {
        InputStream input = new FileInputStream(filename);
        String header = "";
        Vector<Triangle> triangles = new Vector<>();

        byte headerBytes[] = new byte[80];
        byte sizeBytes[] = new byte[8];

        try{
            input.read(headerBytes);
            input.read(sizeBytes, 0, 4);
            header = new String(headerBytes);
            long size = ByteBuffer.wrap(sizeBytes).order(ByteOrder.LITTLE_ENDIAN).getLong();
            triangles = new Vector<>((int)size);
            
            for(int i=0; i<size; i++){
                triangles.add(Triangle.read(input));
            }

            input.close();
        }catch(IOException e){
            e.printStackTrace(System.err);
        }

        return new Stl(header, triangles);
    }

    public void write(String filename){
        
    }

    public String getHeader(){
        return header;
    }
    public Vector<Triangle> getTriangles(){
        return triangles;
    }

    @Override
    public String toString(){
        return "Stl('"+header+"', Triangles("+triangles.size()+")";
    }
}
