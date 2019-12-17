let addUnit = (~unit, ~prefix, str) =>
  switch (unit, prefix) {
  | ("", _) => str
  | (unit, true) => unit ++ str
  | (unit, false) => str ++ unit
  };

[@react.component]
let make =
    (
      ~style: Intl.NumberFormat.style,
      ~parsedFormula: MathJs.ParsedExpression.t,
      ~values: list(State.value),
    ) => {
  let valuesDict =
    Js.Dict.fromList(
      values
      |> Tablecloth.List.filterMap(~f=(value: State.value) =>
           switch (value) {
           | {value: Some(actualValue)} =>
             Some((value.identifier, actualValue))
           | _ => Some((value.identifier, 0.0))
           }
         ),
    );

  let hasAllValues =
    Tablecloth.List.length(values)
    == (
         values
         |> Tablecloth.List.filter(~f=(value: State.value) =>
              switch (value.value) {
              | Some(_) => true
              | None => false
              }
            )
         |> Tablecloth.List.length
       );

  let compiled = parsedFormula |> MathJs.ParsedExpression.compile;

  <div
    className={CssHelpers.tcss(
      "w-full text-2xl font-bold text-gray-800 bg-gray-100 rounded-lg shadow-md text-center px-4 py-6",
    )}>
    {hasAllValues
       ? compiled
         |> MathJs.CompiledExpression.evaluate(valuesDict)
         |> Formatters.formatNumber(~style)
         |> React.string
       : <ExplanatoryText
           text="Please enter all variables to see the result."
         />}
  </div>;
};