[@react.component]
let make =
    (~disabled=false, ~onClick, ~text, ~type_="submit", ~variant=`Filled) => {
  <button
    className={
      CssHelpers.tcss(
        "mx-auto w-48 rounded uppercase font-semibold text-sm px-4 py-2 shadow-md ",
      )
      ++ Utils.classes([
           (
             CssHelpers.tcss("text-indigo-700 border-indigo-500 border-2"),
             variant === `Outlined && !disabled,
           ),
           (
             CssHelpers.tcss("text-white bg-indigo-500"),
             variant === `Filled && !disabled,
           ),
           (CssHelpers.tcss("text-gray-600 bg-gray-200"), disabled),
         ])
    }
    type_
    disabled
    onClick>
    {React.string(text)}
  </button>;
};