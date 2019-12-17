[@react.component]
let make = (~text) =>
  <div className={CssHelpers.tcss("text-sm text-gray-700")}>
    {React.string(text)}
  </div>;