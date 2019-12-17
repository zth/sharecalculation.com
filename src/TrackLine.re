type style = [ | `Horizontal | `Vertical];

[@react.component]
let make = (~style=`Vertical) =>
  switch (style) {
  | `Vertical =>
    <div className={CssHelpers.tcss("w-1 bg-gray-400 h-20 mx-auto")} />
  | `Horizontal =>
    <div className={CssHelpers.tcss("h-1 bg-gray-400 w-10 mx-auto")} />
  };