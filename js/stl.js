import fs from "fs";

export function load(filename){
    const file = fs.openSync(filename)

    const bufferHeader = new Buffer.alloc(80);
    const bufferSize = new Buffer.alloc(4);
    fs.readSync(file, bufferHeader);
    fs.readSync(file, bufferSize);
    const header = bufferHeader.toString('utf-8')
    const size = bufferSize.readUInt32LE(0)
    const triangles = []

    for(let i=0; i<size; i++){

        const bufferVec3 = new Buffer.alloc(4*3*4 + 2)
        fs.readSync(file, bufferVec3);
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

    fs.closeSync(file)

    return {
        header: header,
        triangles: triangles
    }
}

export function save(filename, model){
    const file = fs.openSync(filename, "w")

    const bufferHeader = new Buffer.alloc(80)
    const bufferSize = new Buffer.alloc(4)
    bufferHeader.write(model.header, 'utf8')
    bufferSize.writeUInt32LE(model.triangles.length)

    fs.writeSync(file, bufferHeader)
    fs.writeSync(file, bufferSize)

    model.triangles.forEach(triangle => {
        const bufferVec3 = new Buffer.alloc(4*3*4 + 2)
        for(let i=0; i<3; i++)
            bufferVec3.writeFloatLE(triangle.normal[i], i*4)
        for(let j=0; j<3; j++)
            for(let i=0; i<3; i++)
                bufferVec3.writeFloatLE(triangle.vertex[j][i], 12*(1+j) + 4*i)
        bufferVec3.writeUint16LE(model.attrib, 4*3*4)
        fs.writeSync(file, bufferVec3);
    });

    fs.closeSync(file)
}
