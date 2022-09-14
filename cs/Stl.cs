
class Vec3{
    private float x, y, z;

    public Vec3(float x_, float y_, float z_){
        x = x_;
        y = y_;
        z = z_;
    }

    public static Vec3 Read(ref BinaryReader input){
        float x = input.ReadSingle();
        float y = input.ReadSingle();
        float z = input.ReadSingle();

        return new Vec3(x, y, z);
    }

    public void Write(ref BinaryWriter output){
        byte[] xBytes = BitConverter.GetBytes(x);
        output.Write(xBytes);
        byte[] yBytes = BitConverter.GetBytes(y);
        output.Write(yBytes);
        byte[] zBytes = BitConverter.GetBytes(z);
        output.Write(zBytes);
    }

    public override string ToString(){
        return "Vec3(" + X + ", " + Y + ", " + Z + ")";
    }

    public float X { get => x; set => x = value;  }
    public float Y { get => y; set => y = value;  }
    public float Z { get => z; set => z = value;  }
}

class Triangle{
    private Vec3 normal;
    private Vec3[] vertex;
    private ushort attrib;

    public Triangle(Vec3 normal_, Vec3 v1, Vec3 v2, Vec3 v3, ushort attrib_){
        normal = normal_;
        vertex = new Vec3[]{v1, v2, v3};
        attrib = attrib_;
    }

    public static Triangle Read(ref BinaryReader input){
        Vec3 normal = Vec3.Read(ref input);
        Vec3 v1 = Vec3.Read(ref input);
        Vec3 v2 = Vec3.Read(ref input);
        Vec3 v3 = Vec3.Read(ref input);
        ushort attrib = input.ReadUInt16();
        
        return new Triangle(normal, v1, v2, v3, attrib);
    }

    public void Write(ref BinaryWriter output){
        normal.Write(ref output);
        for(int i=0; i<3; i++){
            vertex[i].Write(ref output);
        }
        byte[] attribBytes = BitConverter.GetBytes(attrib);
        output.Write(attribBytes);
    }

    public override string ToString(){
        return "Triangle(Normal: " + normal + ")";
    }

    public Vec3 Normal{
        get => normal;
        set => normal = value;
    }
}

public class Stl{

    private string header;
    private List<Triangle> triangles;

    public string Header{
        get => header;
        set => header = value;
    }

    public static Stl Read(string filename){
        string header = "";
        uint size;
        List<Triangle> triangles = new List<Triangle>();

        if (File.Exists(filename))
        {
            using (var stream = File.Open(filename, FileMode.Open))
            {
                var reader = new BinaryReader(stream, System.Text.Encoding.UTF8, false);
                byte[] headerBytes = reader.ReadBytes(80);
                size = reader.ReadUInt32();
                header = System.Text.Encoding.UTF8.GetString(headerBytes);

                triangles = new List<Triangle>((int)size);

                for(int i=0; i<size; i++){
                    Triangle triangle = Triangle.Read(ref reader);
                    triangles.Add(triangle);
                }
                reader.Close();
            }
        }
        return new Stl(header, triangles);
    }

    public void Write(string filename){
        using (var stream = File.Open(filename, FileMode.Create))
        {
            var writer = new BinaryWriter(stream, System.Text.Encoding.UTF8, false);
            byte[] bytes = System.Text.Encoding.UTF8.GetBytes(header, 0, 80);
            
            writer.Write(bytes);
            byte[] sizeBytes = BitConverter.GetBytes((uint)triangles.Count);
            writer.Write(sizeBytes);

            for(int i=0; i<triangles.Count; i++){
                triangles[i].Write(ref writer);
            }

            writer.Close();
        }
    }

    public override string ToString()
    {
        return "Stl('" + header + "', Triangles(" + triangles.Count + "))";
    }

    private Stl(string header_, List<Triangle> triangles_){
        header = header_;
        triangles = triangles_;
    }
}