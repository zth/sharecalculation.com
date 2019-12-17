[@react.component]
let make = (~values, ~setValue, ~preview=false) =>
  <div
    className={CssHelpers.tcss(
      "sm:block md:flex md:flex-wrap md:flex-row md:items-start",
    )}>
    {values
     |> Tablecloth.List.mapi(~f=(i, value: State.value) => {
          let theValue =
            Tablecloth.Option.withDefault(~default=0.0, value.value);

          <UseFormEnterValuesSingleValue
            key={value.identifier}
            value
            i
            theValue
            setValue
          />;
        })
     |> Tablecloth.Array.fromList
     |> React.array}
  </div>;