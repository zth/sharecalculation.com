type springPreset = [ | `noWobble | `gently | `veryGentle | `wobbly | `stiff];

let mapSpringPreset = s =>
  switch (s) {
  | `gently => "gently"
  | `veryGentle => "veryGentle"
  | `wobbly => "wobbly"
  | `stiff => "stiff"
  | `noWobble => "noWobble"
  };

module Flipper = {
  [@bs.module "react-flip-toolkit"] [@react.component]
  external make:
    (
      ~flipKey: string,
      ~children: React.element,
      ~applyTransformOrigin: bool=?,
      ~spring: string=?,
      ~element: string=?,
      ~className: string=?,
      unit
    ) =>
    React.element =
    "Flipper";
  /*[@react.component]
    let make =
        (
          ~flipKey,
          ~children,
          ~applyTransformOrigin=?,
          ~spring=?,
          ~element=?,
          ~className=?,
          (),
        ) =>
      _make({
        "flipKey": flipKey,
        "children": children,
        "applyTransformOrigin": applyTransformOrigin,
        "spring":
          switch (spring) {
          | Some(s) => Some(mapSpringPreset(s))
          | None => None
          },
        "element": element,
        "className": className,
      });*/
};

module Flipped = {
  [@bs.module "react-flip-toolkit"] [@react.component]
  external make:
    (
      ~children: React.element,
      ~flipId: string=?,
      ~inverseFlipId: string=?,
      ~spring: string=?,
      ~className: string=?,
      ~element: string=?,
      ~stagger: bool=?
    ) =>
    React.element =
    "Flipped";
  /*[@react.component]
    let make = (~children, ~flipId=?, ~inverseFlipId=?, ~spring=?, ~stagger=?) =>
      _make({
        "children": children,
        "flipId": flipId,
        "inverseFlipId": inverseFlipId,
        "spring":
          switch (spring) {
          | Some(s) => Some(mapSpringPreset(s))
          | None => None
          },
        "stagger": stagger,
      });*/
};