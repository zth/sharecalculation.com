type value = {
  identifier: string,
  label: string,
  value: option(float),
  defaultValue: option(float),
  step: option(float),
};

type state = {
  title: string,
  description: string,
  style: Intl.NumberFormat.style,
  formula: string,
  values: list(value),
};

type updateValue = {
  identifier: string,
  updater: value => value,
};

type action =
  | SetDescription(string)
  | SetTitle(string)
  | SetFormula(string)
  | UpdateValue(updateValue)
  | SetResultStyle(Intl.NumberFormat.style);

let emptyState = (): state => {
  title: "",
  description: "",
  style: Decimal,
  formula: "",
  values: [],
};

let constants = [
  "e",
  "E",
  "i",
  "Infinity",
  "LN2",
  "LN10",
  "LOG2E",
  "LOG10E",
  "NaN",
  "null",
  "phi",
  "pi",
  "PI",
  "SQRT1_2",
  "SQRT2",
  "tau",
  "undefined",
  "version",
];

let valuesFromFormula = (~oldValues: list(value), formula: string) => {
  MathJs.(
    switch (formula |> parse) {
    | Ok(v) =>
      v
      |> ParsedExpression.getSymbols
      |> Tablecloth.List.filterMap(~f=symbolName =>
           constants |> List.exists(c => c === symbolName)
             ? None
             : Some(
                 oldValues
                 |> Tablecloth.List.find(~f=(label: value) =>
                      label.identifier === symbolName
                    )
                 |> Tablecloth.Option.withDefault(
                      ~default={
                        identifier: symbolName,
                        label: "",
                        value: None,
                        defaultValue: None,
                        step: None,
                      },
                    ),
               )
         )

    | Error(_) => []
    }
  );
};

let updateValue = (~id, ~updater: value => value, list) =>
  list
  |> Tablecloth.List.map(~f=(item: value) =>
       item.identifier === id ? updater(item) : item
     );

let makeApi = (~initialState=?, ()) =>
  Restorative.createStore(
    switch (initialState) {
    | Some(s) => s
    | None => emptyState()
    },
    (state, action) =>
    switch (action) {
    | SetTitle(title) =>
      String.length(title) <= Constants.maximumTitleLength
        ? {...state, title} : state
    | SetDescription(description) =>
      String.length(description) <= Constants.maximumDescLength
        ? {...state, description} : state
    | SetFormula(formula) => {
        ...state,
        values: formula |> valuesFromFormula(~oldValues=state.values),
        formula,
      }
    | UpdateValue(opts) => {
        ...state,
        values:
          state.values
          |> updateValue(~id=opts.identifier, ~updater=opts.updater),
      }

    | SetResultStyle(style) => {...state, style}
    }
  );

let api = makeApi();

let stateContext: React.Context.t(option(Restorative.api(state, action))) =
  React.createContext(None);

exception State_context_missing;

let useStateApi = () =>
  switch (React.useContext(stateContext)) {
  | Some(c) => c
  | None => raise(State_context_missing)
  };

module Provider = {
  let make = React.Context.provider(stateContext);

  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };
};