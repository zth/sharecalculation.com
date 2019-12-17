[@react.component]
let make = (~values, ~updateValue: State.updateValue => unit) =>
  <div className={CssHelpers.tcss("mt-8")}>
    <div className={CssHelpers.tcss("px-4 md:px-10 mb-4 text-center")}>
      <h3
        className={CssHelpers.tcss(
          "text-xl font-black uppercase text-gray-800",
        )}>
        {React.string("Variables")}
      </h3>
      <ExplanatoryText
        text="Configure the variables used in your formula here."
      />
    </div>
    {values
     |> Tablecloth.List.mapi(~f=(i, value: State.value) =>
          <SingleLabel
            value
            key={value.identifier}
            updateValue
            first={i == 0}
          />
        )
     |> Tablecloth.Array.fromList
     |> React.array}
  </div>;