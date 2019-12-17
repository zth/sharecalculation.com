[@react.component]
let make =
  React.memo(() => {
    let api = State.useStateApi();

    let (description, _) = api.useStoreWithSelector(s => s.description, ());
    let (title, _) = api.useStoreWithSelector(s => s.title, ());
    let (values, dispatch) = api.useStoreWithSelector(s => s.values, ());

    <div>
      <div className={CssHelpers.tcss("px-4 md:px-10 mb-4 text-center")}>
        <h3
          className={CssHelpers.tcss(
            "text-xl font-black uppercase text-gray-800",
          )}>
          {React.string("Settings")}
        </h3>
        <ExplanatoryText
          text="Various settings and optional texts you can add to describe your calculation and its variables here. Nothing is required."
        />
      </div>
      <div className={CssHelpers.tcss("block")}>
        <DescriptionInput
          description
          title
          setDescription={d => dispatch(SetDescription(d))}
          setTitle={d => dispatch(SetTitle(d))}
        />
        <ResultSettings />
        <LabelEditor
          values
          updateValue={opts => dispatch(UpdateValue(opts))}
        />
      </div>
    </div>;
  });