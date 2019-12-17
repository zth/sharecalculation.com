type screenSize =
  | Sm
  | Md
  | Lg
  | Xl;

let currentSize = () =>
  switch (Webapi.Dom.window |> Webapi.Dom.Window.innerWidth) {
  | v when v <= 640 => Sm
  | v when v <= 768 => Md
  | v when v <= 1024 => Lg
  | v when v <= 1280 => Xl
  | _ => Md
  };