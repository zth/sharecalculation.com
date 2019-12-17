[@react.component]
let make = () =>
  <div className={CssHelpers.tcss("px-2")}>
    {React.string({j| • |j})}
  </div>;