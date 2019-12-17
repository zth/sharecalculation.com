[@react.component]
let make = (~text, ~maxLength) =>
  <div className={CssHelpers.tcss("mt-1")}>
    {String.length(text) >= Js.Math.ceil(float_of_int(maxLength) *. 0.8)
       ? <div
           className={
             CssHelpers.tcss("text-sm text-gray-500 mb-2 ")
             ++ Utils.classes([
                  (
                    CssHelpers.tcss("text-red-600"),
                    String.length(text) === maxLength,
                  ),
                ])
           }>
           {text |> String.length |> string_of_int |> React.string}
           {React.string(
              " of maximum "
              ++ string_of_int(maxLength)
              ++ " characters allowed",
            )}
         </div>
       : React.null}
  </div>;