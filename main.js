
const stl = {
    fs: require("fs"),
    load: (filename) => {
        const file = stl.fs.openSync(filename)

        const bufferHeader = new Buffer.alloc(80);
        const bufferSize = new Buffer.alloc(4);
        stl.fs.readSync(file, bufferHeader);
        stl.fs.readSync(file, bufferSize);
        const header = bufferHeader.toString('utf-8')
        const size = bufferSize.readUInt32LE(0)
        const triangles = []

        for(let i=0; i<size; i++){

            const bufferVec3 = new Buffer.alloc(4*3*4 + 2)
            stl.fs.readSync(file, bufferVec3);
            const normal = [bufferVec3.readFloatLE(0), bufferVec3.readFloatLE(4), bufferVec3.readFloatLE(8)]
            let vertex = []
            for(let j=0; j<3; j++){
                vertex.push([
                    bufferVec3.readFloatLE(12+12*j),
                    bufferVec3.readFloatLE(16+12*j),
                    bufferVec3.readFloatLE(20+12*j)
                    ]
                )
            }
            const attrib = bufferVec3.readUInt16LE(4*3*4);

            triangles.push( {normal: normal, vertex: vertex, attrib: attrib} )
        }

        stl.fs.closeSync(file)

        return {
            header: header,
            triangles: triangles
        }
    },
    save: (filename, model) => {
        const file = stl.fs.openSync(filename, "w")

        const bufferHeader = new Buffer.alloc(80)
        const bufferSize = new Buffer.alloc(4)
        bufferHeader.write(model.header, 'utf8')
        bufferSize.writeUInt32LE(model.triangles.length)

        stl.fs.writeSync(file, bufferHeader)
        stl.fs.writeSync(file, bufferSize)

        model.triangles.forEach(triangle => {
            const bufferVec3 = new Buffer.alloc(4*3*4 + 2)
            for(let i=0; i<3; i++)
                bufferVec3.writeFloatLE(triangle.normal[i], i*4)
            for(let j=0; j<3; j++)
                for(let i=0; i<3; i++)
                    bufferVec3.writeFloatLE(triangle.vertex[j][i], 12*(1+j) + 4*i)
            bufferVec3.writeUint16LE(model.attrib, 4*3*4)
            stl.fs.writeSync(file, bufferVec3);
        });

        stl.fs.closeSync(file)
    }
};


(()=>{
    const fs = require("fs")
    
    const filename = "model.stl"
    const fileout = "model.edit.stl"

    const model = stl.load(filename)

    //model.header = "Grober"

    stl.save(fileout, model)
    

})();