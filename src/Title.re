[@react.component]
let make = () => {
  <div className={CssHelpers.tcss("mb-4 mt-12 p-2")}>
    <h1
      className={CssHelpers.tcss(
        "text-center text-2xl md:text-4xl font-black",
      )}>
      <span className={CssHelpers.tcss("text-gray-900")}>
        {React.string("ShareCalculation.com")}
      </span>
    </h1>
    <div className={CssHelpers.tcss("mb-2 text-center max-w-sm mx-auto")}>
      <ExplanatoryText
        text="Create and share interactive calculations. When creating a spreadsheet is overkill."
      />
    </div>
  </div>;
};