type action =
  | SetValue({
      identifier: string,
      value: option(float),
    });

[@react.component]
let make = (~serializedData) => {
  let initialState =
    React.useMemo1(
      () => serializedData |> Serialize.deserialize,
      [|serializedData|],
    );

  let (state, dispatch) =
    React.useReducer(
      (state: State.state, action) =>
        switch (action) {
        | SetValue({identifier, value}) => {
            ...state,
            values:
              state.values
              |> State.updateValue(~id=identifier, ~updater=v =>
                   {...v, value}
                 ),
          }
        },
      initialState,
    );

  <div className={CssHelpers.tcss("max-w-lg mx-auto")}>
    <BsReactHelmet>
      {state.title !== ""
         ? <title>
             {React.string(state.title ++ " | ShareCalculation.com")}
           </title>
         : React.null}
      {state.description !== ""
         ? <meta name="description" content={state.description} /> : React.null}
    </BsReactHelmet>
    <UseForm
      state
      encodedInitialState=serializedData
      setValue={(value: State.value) =>
        dispatch(
          SetValue({identifier: value.identifier, value: value.value}),
        )
      }
    />
    <UseFormDisclaimer />
  </div>;
};