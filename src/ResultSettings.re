type styleOption = {
  style: Intl.NumberFormat.style,
  label: string,
  value: string,
};

let decimalStyle: styleOption = {
  style: Decimal,
  label: "Regular number",
  value: "decimal",
};

let percentStyle: styleOption = {
  style: Percent,
  label: "Percent",
  value: "percent",
};

let styles: list(styleOption) = [decimalStyle, percentStyle];

[@react.component]
let make = () => {
  let api = State.useStateApi();

  let (style, dispatch) = api.useStoreWithSelector(s => s.style, ());

  let selectedStyle =
    styles
    |> Tablecloth.List.find(~f=s => s.style === style)
    |> Tablecloth.Option.withDefault(~default=decimalStyle);

  <div>
    <div className={CssHelpers.tcss("mt-4")}>
      <label
        className={CssHelpers.tcss(
          "block text-xs font-bold text-gray-700 uppercase",
        )}>
        {React.string("Display result as")}
      </label>
      <div className={CssHelpers.tcss("flex")}>
        {styles
         |> Tablecloth.List.map(~f=s =>
              <div className={CssHelpers.tcss("mr-4")} key={s.value}>
                <input
                  type_="radio"
                  checked={selectedStyle.value === s.value}
                  key={s.value}
                  value={s.value}
                  id={"radio-" ++ s.value}
                  name={s.value}
                  onChange={_ => dispatch(SetResultStyle(s.style))}
                />
                <label
                  className={CssHelpers.tcss("text-sm text-gray-900 ml-1")}
                  htmlFor={"radio-" ++ s.value}>
                  {React.string(s.label)}
                </label>
              </div>
            )
         |> Tablecloth.Array.fromList
         |> React.array}
      </div>
    </div>
  </div>;
};