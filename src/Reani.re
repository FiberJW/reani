[@bs.val] external dirname: string = "__dirname";
[@bs.module] external nodeOpen: string => Js.Promise.t(unit) = "open";

type gifDir = {
  name: string,
  path: string,
};

let run = () => {
  let gifDirs =
    FS.readdirSync(dirname ++ "/gifs")
    |> Js.Array.filter(x => FS.isDirectory(dirname ++ "/gifs/" ++ x))
    |> Array.map(gifDirName =>
         {name: gifDirName, path: dirname ++ "/gifs/" ++ gifDirName}
       );

  let toSelectOption = (a: gifDir): Prompts.selectOption => {
    title: a.name,
    value: a.path,
  };

  Prompts.singleSelect({
    _type: "select",
    name: "value",
    message: "choose a reaction type",
    choices: gifDirs |> Array.map(toSelectOption),
  })
  |> Js.Promise.then_((gifDirPath: Prompts.selectValue) => {
       let gifPaths =
         FS.readdirSync(gifDirPath.value)
         |> Array.map(p => gifDirPath.value ++ "/" ++ p);
       let gifsCount = gifPaths |> Array.length;

       Random.self_init();
       let randomGifIndex = Random.int(gifsCount);
       let randomGifPath = gifPaths->Array.get(randomGifIndex);

       Js.log(
         "Opening a random reaction GIF based on your selection in your native photo app.",
       );

       nodeOpen(randomGifPath) |> ignore;
       Js.Promise.resolve();
     });
};