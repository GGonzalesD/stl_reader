package stl;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.stream.Collectors;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class Triangle {
    private Vec3 normal;
    private Vec3[] vertex;
    private int attrib;

    public Triangle(Vec3 normal_, Vec3 v1, Vec3 v2, Vec3 v3, int attrib_){
        normal = normal_;
        vertex = new Vec3[3];
        vertex[0] = v1;
        vertex[1] = v2;
        vertex[2] = v3;
        attrib = attrib_;
    }

    public static Triangle read(InputStream input){
        byte bytes[] = new byte[4];
        int attrib = 0;

        Vec3 normal = Vec3.read(input);
        Vec3 v1 = Vec3.read(input);
        Vec3 v2 = Vec3.read(input);
        Vec3 v3 = Vec3.read(input);
        try{
            input.read(bytes, 0, 2);
            attrib = ByteBuffer.wrap(bytes).order(ByteOrder.LITTLE_ENDIAN).getInt();
        }catch(IOException e){
            e.printStackTrace(System.err);
        }

        return new Triangle(normal, v1, v2, v3, attrib);
    }

    public void write(OutputStream output){
        normal.write(output);
        for (Vec3 vec3 : vertex) {
            vec3.write(output);
        }
        try{
            output.write(ByteBuffer.allocate(2).order(ByteOrder.LITTLE_ENDIAN).putFloat(attrib).array());
        }catch(IOException e){
            e.printStackTrace(System.err);
        }
    }

    @Override
    public String toString(){
        String vertx = Arrays.asList(vertex).stream().map(String::valueOf).collect(Collectors.joining(", "));
        return "Triangle(normal: "+normal+", Vertex("+vertx+"), "+attrib+")";
    }
}
