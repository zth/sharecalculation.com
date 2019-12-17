[@react.component]
let make = (~initialData) => {
  let api =
    React.useMemo1(
      () =>
        State.makeApi(
          ~initialState=
            switch (initialData) {
            | Some(d) => d
            | None => State.emptyState()
            },
          (),
        ),
      [|initialData|],
    );

  <State.Provider value={Some(api)}> <CreatorForm /> </State.Provider>;
};