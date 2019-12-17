[@react.component]
let make =
  React.memo(() => {
    let api = State.useStateApi();
    let (state, dispatch) = api.useStore();

    <UseForm
      state
      preview=true
      setValue={(opts: State.value) =>
        dispatch(
          UpdateValue({
            identifier: opts.identifier,
            updater: v => {...v, value: opts.value},
          }),
        )
      }
    />;
  });