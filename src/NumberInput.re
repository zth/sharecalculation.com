[@react.component]
let make = (~onChange, ~value, ~step=?, ~id=?, ~placeholder=?, ~autoFocus=?) => {
  let (v, setV) = React.useState(() => value);

  React.useEffect1(
    () => {
      setV(_ => value);
      None;
    },
    [|value|],
  );

  <input
    ?id
    type_="number"
    value=v
    ?autoFocus
    ?placeholder
    ?step
    className={CssHelpers.tcss(
      "w-full px-5 py-1 text-gray-700 bg-gray-200 rounded",
    )}
    onChange={e => {
      let value = ReactEvent.Form.currentTarget(e)##value;
      setV(_ => value);
    }}
    onBlur={_ => {onChange(v)}}
  />;
};