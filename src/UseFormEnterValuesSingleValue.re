[@react.component]
let make = (~value: State.value, ~theValue, ~setValue, ~i) => {
  <div
    className={
      CssHelpers.tcss("UseFormEnterValues__item ")
      ++ (i mod 2 == 0 ? "" : CssHelpers.tcss("md:pl-4"))
    }>
    <label
      htmlFor={value.identifier ++ "_input"}
      className={CssHelpers.tcss(
        "block text-xs font-bold text-gray-700 uppercase",
      )}>
      {React.string(value.identifier)}
    </label>
    <p className={CssHelpers.tcss("text-xs text-gray-700")}>
      {React.string(value.label ++ {j|‎ |j})}
    </p>
    <div>
      <div>
        <input
          id={value.identifier ++ "_input"}
          type_="number"
          step={value.step |> Tablecloth.Option.withDefault(~default=1.0)}
          defaultValue={Js.Float.toString(theValue)}
          className={CssHelpers.tcss(
            "h-10 w-full px-5 py-1 text-gray-700 bg-gray-200 rounded",
          )}
          onChange={e =>
            setValue({
              ...value,
              value:
                switch (ReactEvent.Form.currentTarget(e)##value) {
                | "" => None
                | v => Some(float_of_string(v))
                },
            })
          }
        />
      </div>
      <div className={CssHelpers.tcss("mt-1")}>
        <div
          className={CssHelpers.tcss(
            "ml-4 h-10 pl-1 pt-2 text-sm text-gray-700 font-light flex content-center justify-start",
          )}>
          <span>
            {switch (
               theValue,
               Js.Float.toString(theValue),
               theValue |> Formatters.formatNumber(~style=Decimal),
             ) {
             | (0.0, _, _) => React.string("")
             | (_, fn, fi) when fn == fi => React.string("")
             | (_, _, fi) => React.string("Formatted: " ++ fi)
             }}
          </span>
        </div>
      </div>
    </div>
  </div>;
};