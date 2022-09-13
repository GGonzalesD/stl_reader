
import { save, load } from "./stl.js";

(()=>{
    
    const filename = "model.stl"
    const fileout = "model.edit.stl"

    const model = load(filename)

    //model.header = "Grober"

    save(fileout, model)
    

})();