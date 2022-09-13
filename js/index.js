
import { save, load } from "./stl.js";

(()=>{

    const model = load("model.stl")

    console.log(model)

    save("model.edit.stl", model)

})();