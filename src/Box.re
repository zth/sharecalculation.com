[@react.component]
let make = (~children) =>
  <div className={CssHelpers.tcss("w-full mx-auto")}>
    <div className={CssHelpers.tcss("p-4 rounded-lg bg-white shadow-lg")}>
      children
    </div>
  </div>;