// See https://aka.ms/new-console-template for more information

var stl = Stl.Read("model.stl");

Console.WriteLine(stl);

stl.Write("model.edit.stl");
