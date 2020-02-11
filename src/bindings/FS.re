type stat;

[@bs.module "fs"]
external readdirSync: string => array(string) = "readdirSync";
[@bs.module "fs"] external statSync: string => stat = "statSync";
[@bs.send] external isDirectory: stat => bool = "isDirectory";

let isDirectory = path =>
  try(isDirectory(statSync(path))) {
  | _ => false
  };