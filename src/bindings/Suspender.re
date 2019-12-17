[@bs.module "./libs"]
external _useDynamicLibrary: (unit => Js.Promise.t('m)) => 'm =
  "useDynamicLibrary";

[@bs.module "./libs"]
external importKaTex: unit => Js.Promise.t(KaTex.katex) = "importKaTex";

let useKatex = () => _useDynamicLibrary(importKaTex);

let preloadKatex = () => importKaTex() |> ignore;

let useKaTex = () => {
  let (lib, setLib) = React.useState(() => None);

  React.useEffect0(() => {
    importKaTex()
    |> Js.Promise.then_(m => setLib(_ => Some(m)) |> Js.Promise.resolve)
    |> ignore;
    None;
  });

  lib;
};