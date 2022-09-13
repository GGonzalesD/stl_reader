package stl;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class Vec3 {
    private float x, y, z;

    public Vec3(float x_, float y_, float z_){
        x = x_;
        y = y_;
        z = z_;
    }

    public static Vec3 read(InputStream input){
        float x = 0, y = 0, z = 0;
        byte bytes[] = new byte[4];
        ByteBuffer buffer;
        try{
            input.read(bytes);
            buffer = ByteBuffer.wrap(bytes);
            x = buffer.order(ByteOrder.LITTLE_ENDIAN).getFloat();
            input.read(bytes);
            buffer = ByteBuffer.wrap(bytes);
            y = buffer.order(ByteOrder.LITTLE_ENDIAN).getFloat();
            input.read(bytes);
            buffer = ByteBuffer.wrap(bytes);
            z = buffer.order(ByteOrder.LITTLE_ENDIAN).getFloat();
        }catch(IOException e){
            e.printStackTrace(System.err);
        }
        return new Vec3(x, y, z);
    }

    public void write(OutputStream output){
        byte bytes[];
        try{
            bytes = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putFloat(x).array();
            output.write(bytes);
            bytes = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putFloat(y).array();
            output.write(bytes);
            bytes = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putFloat(z).array();
            output.write(bytes);
        }catch(IOException e){
            e.printStackTrace(System.err);
        }
    }

    public void setX(float x_){
        x = x_;
    }

    public void setY(float y_){
        y = y_;
    }

    public void setZ(float z_){
        z = z_;
    }

    public float getX(){
        return x;
    }

    public float getY(){
        return y;
    }

    public float getZ(){
        return z;
    }

    @Override
    public String toString(){
        return "Vec3(" + x + ", " + y + ", " + z + ")";
    }
}
