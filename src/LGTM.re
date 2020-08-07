[@bs.val] external dirname: string = "__dirname";
[@bs.module] external nodeOpen: string => Js.Promise.t(unit) = "open";
[@bs.module] external isWSL: bool = "is-wsl";

type gifDir = {
  name: string,
  path: string,
};

let run = () => {
  let gifDirPath = dirname ++ "/gifs/thumbs-up";

  let gifPaths =
    FS.readdirSync(gifDirPath) |> Array.map(p => gifDirPath ++ "/" ++ p);
  let gifsCount = gifPaths |> Array.length;

  Random.self_init();
  let randomGifIndex = Random.int(gifsCount);
  let randomGifPath = gifPaths->Array.get(randomGifIndex);

  if (isWSL) {
    let command = "explorer.exe `wslpath -w \"" ++ randomGifPath ++ "\"`";

    try(
      Node.Child_process.execSync(command, Node.Child_process.option())
      ->ignore
    ) {
    | _ => ()
    };
  } else {
    nodeOpen(randomGifPath)->ignore;
  };
};
