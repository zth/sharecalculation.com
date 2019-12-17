type help =
  | Step;

type state = {
  showLabel: bool,
  showDefaultValue: bool,
  showStep: bool,
  helpVisible: option(help),
};

type action =
  | ShowLabel
  | ShowDefaultValue
  | ShowStep
  | ShowHelp(help)
  | HideHelp;

[@react.component]
let make =
    (
      ~value: State.value,
      ~first=false,
      ~updateValue: State.updateValue => unit,
    ) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | ShowLabel => {...state, showLabel: true}
        | ShowDefaultValue => {...state, showDefaultValue: true}
        | ShowStep => {...state, showStep: true}
        | ShowHelp(h) => {...state, helpVisible: Some(h)}
        | HideHelp => {...state, helpVisible: None}
        },
      {
        showLabel: value.label !== "",
        showDefaultValue:
          switch (value.defaultValue) {
          | Some(_) => true
          | None => false
          },
        showStep:
          switch (value.step) {
          | Some(_) => true
          | None => false
          },
        helpVisible: None,
      },
    );

  <div className={first ? "" : CssHelpers.tcss("mt-4")}>
    <label
      className={CssHelpers.tcss(
        "block text-sm font-bold text-gray-700 uppercase mb-1",
      )}>
      {React.string(value.identifier)}
    </label>
    <div className={CssHelpers.tcss("flex")}>
      <div className={CssHelpers.tcss("flex-1")}>
        <label
          className={CssHelpers.tcss(
            "block text-xs md:font-thin text-gray-600 uppercase",
          )}
          htmlFor={"label-for--" ++ value.identifier}>
          {React.string("Label")}
        </label>
        {state.showLabel
           ? <input
               type_="text"
               autoFocus=true
               id={"label-for--" ++ value.identifier}
               className={CssHelpers.tcss(
                 "w-full px-5 py-1 text-gray-700 bg-gray-200 rounded",
               )}
               placeholder="Ex: In meters."
               value={value.label}
               onChange={e =>
                 updateValue({
                   identifier: value.identifier,
                   updater: value => {
                     ...value,
                     label: ReactEvent.Form.currentTarget(e)##value,
                   },
                 })
               }
             />
           : <button
               type_="button"
               className=CssHelpers.linkStyles
               onClick={_ => dispatch(ShowLabel)}>
               {React.string("+ Add label")}
             </button>}
      </div>
    </div>
    <div className={CssHelpers.tcss("flex mt-2")}>
      <div className={CssHelpers.tcss("flex-1")}>
        <label
          className={CssHelpers.tcss(
            "block text-xs md:font-thin text-gray-600 uppercase",
          )}
          htmlFor={"default-value-for--" ++ value.identifier}>
          {React.string("Default value")}
        </label>
        {state.showDefaultValue
           ? <NumberInput
               id={"default-value-for--" ++ value.identifier}
               placeholder="Optional"
               autoFocus=true
               value={
                 switch (value.defaultValue) {
                 | None => ""
                 | Some(v) => Js.Float.toString(v)
                 }
               }
               onChange={e =>
                 updateValue({
                   identifier: value.identifier,
                   updater: value => {
                     ...value,
                     defaultValue:
                       switch (e) {
                       | "" => None
                       | v => Some(float_of_string(v))
                       },
                   },
                 })
               }
             />
           : <button
               type_="button"
               className=CssHelpers.linkStyles
               onClick={_ => dispatch(ShowDefaultValue)}>
               {React.string("+ Set default value")}
             </button>}
      </div>
      <div className={CssHelpers.tcss("flex-1 pl-2")}>
        <label
          className={CssHelpers.tcss(
            "block text-xs md:font-thin text-gray-600 uppercase",
          )}
          htmlFor={"step-for--" ++ value.identifier}>
          <div className={CssHelpers.tcss("flex")}>
            {React.string("Step")}
            <div className={CssHelpers.tcss("ml-1")}>
              <HelpIcon
                onClick={() =>
                  dispatch(
                    switch (state.helpVisible) {
                    | Some(_) => HideHelp
                    | None => ShowHelp(Step)
                    },
                  )
                }
                active={state.helpVisible === Some(Step)}
              />
            </div>
          </div>
        </label>
        {state.showStep
           ? <NumberInput
               id={"step-for--" ++ value.identifier}
               autoFocus=true
               value={
                 switch (value.step) {
                 | None => ""
                 | Some(v) => Js.Float.toString(v)
                 }
               }
               onChange={e =>
                 updateValue({
                   identifier: value.identifier,
                   updater: v => {
                     ...v,
                     step:
                       switch (e) {
                       | "" => None
                       | v => Some(float_of_string(v))
                       },
                   },
                 })
               }
             />
           : <button
               type_="button"
               className=CssHelpers.linkStyles
               onClick={_ => dispatch(ShowStep)}>
               {React.string("+ Set step")}
             </button>}
      </div>
    </div>
    {switch (state.helpVisible) {
     | None => React.null
     | Some(Step) =>
       <div className={CssHelpers.tcss("mt-4 p-4 bg-gray-100 fade-in")}>
         <ExplanatoryText
           text="Step is how much is added or removed when you use the up/down arrows on your keyboard when changing this value. Try it by setting a value here, and then using the keyboard arrows in the preview."
         />
       </div>
     }}
  </div>;
};