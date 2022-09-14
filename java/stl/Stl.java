package stl;

import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Vector;

public class Stl {
    private String header;
    private Vector<Triangle> triangles;

    public Stl(String header_, Vector<Triangle> triangles_){
        header = header_;
        triangles = triangles_;
    }

    public static Stl read(String filename) throws FileNotFoundException, IOException {
        InputStream input = new FileInputStream(filename);
        String header = "";
        Vector<Triangle> triangles = new Vector<>();

        byte headerBytes[] = new byte[80];
        byte sizeBytes[] = new byte[8];

        input.read(headerBytes);
        input.read(sizeBytes, 0, 4);
        header = new String(headerBytes);
        long size = ByteBuffer.wrap(sizeBytes).order(ByteOrder.LITTLE_ENDIAN).getLong();
        triangles = new Vector<>((int)size);
        
        for(int i=0; i<size; i++){
            triangles.add(Triangle.read(input));
        }
        input.close();

        return new Stl(header, triangles);
    }

    public void write(String filename) throws FileNotFoundException {
        OutputStream output = new FileOutputStream(filename);

        try{
            byte headerBytes[] = header.getBytes();

            if(headerBytes.length > 80){
                output.write(headerBytes, 0, 80);
            } else {
                output.write(headerBytes);
                byte gbytes[] = new byte[80 - headerBytes.length];
                output.write(gbytes);
            }

            int size = triangles.size();
            output.write(ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(size).array());
        
            for(Triangle triangle: triangles){
                triangle.write(output);
            }

            output.close();
        }catch(IOException e){
            e.printStackTrace(System.err);
        }
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
