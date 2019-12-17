[@decco]
type style =
  | D
  | P;

[@decco]
type boolean =
  | T
  | F;

[@decco]
type label = {
  [@decco.default ""] [@decco.key "1"]
  label: string,
  [@decco.default ""] [@decco.key "2"]
  identifier: string,
  [@decco.key "3"]
  step: option(float),
  [@decco.key "4"]
  defaultValue: option(float),
};

[@decco]
type serialized = {
  [@decco.default ""] [@decco.key "1"]
  formula: string,
  [@decco.key "2"]
  style: option(style),
  [@decco.default ""] [@decco.key "3"]
  description: string,
  [@decco.default []] [@decco.key "4"]
  labels: list(label),
  [@decco.default ""] [@decco.key "5"]
  title: string,
};

let stateToSerialized = (state: State.state): serialized => {
  formula: state.formula,
  description: state.description,
  title: state.title,
  style:
    switch (state.style) {
    | Percent => Some(P)
    | _ => None
    },
  labels:
    state.values
    |> Tablecloth.List.map(~f=(value: State.value) =>
         {
           label: value.label,
           identifier: value.identifier,
           step: value.step,
           defaultValue: value.defaultValue,
         }
       ),
};

exception Decoding_failed(string);

let serializedToState = (str): State.state =>
  switch (str |> serialized_decode) {
  | Ok(decoded) => {
      formula: decoded.formula,
      description: decoded.description,
      title: decoded.title,
      values:
        decoded.labels
        |> Tablecloth.List.map(~f=(label: label) =>
             (
               {
                 identifier: label.identifier,
                 label: label.label,
                 value: label.defaultValue,
                 defaultValue: label.defaultValue,
                 step: label.step,
               }: State.value
             )
           ),
      style:
        switch (decoded.style) {
        | Some(P) => Percent
        | _ => Decimal
        },
    }
  | Error(e) => raise(Decoding_failed(e.message))
  };

let serialize = (state: State.state) =>
  state |> stateToSerialized |> serialized_encode |> Js.Json.stringify;

let deserialize = str =>
  str |> Compressor.decompress |> Js.Json.parseExn |> serializedToState;