[@react.component]
let make =
  React.memo((~title, ~description) =>
    <div className={CssHelpers.tcss("px-4 md:px-10 mb-4 text-center")}>
      {title !== ""
         ? <h2
             className={CssHelpers.tcss("text-2xl font-black text-gray-800")}>
             {React.string(title)}
           </h2>
         : React.null}
      {description !== "" ? <ExplanatoryText text=description /> : React.null}
    </div>
  );