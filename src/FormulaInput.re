[@react.component]
let make =
  React.memo(() => {
    let (intermediateFormula, setIntermediateFormula) =
      React.useState(() => "");

    let api = State.useStateApi();

    let (formula, dispatch) = api.useStoreWithSelector(s => s.formula, ());
    let (hasFormula, setHasFormula) = React.useState(() => formula !== "");
    let (errorText, setErrorText) = React.useState(() => None);
    let (showHelp, setShowHelp) = React.useState(() => false);

    let currentSize = Responsive.currentSize();

    let setFormula = f =>
      switch (f |> MathJs.parse) {
      | Error(e) =>
        Sentry.captureMessage(e);
        setErrorText(_ => Some(e));
      | Ok(v) =>
        switch (v |> MathJs.ParsedExpression.getSymbols) {
        | [] =>
          setErrorText(_ => Some("Your formula must include variables"));
          setShowHelp(_ => false);
        | _ =>
          setErrorText(_ => None);
          dispatch(SetFormula(f));
          setShowHelp(_ => false);
        }
      };

    React.useEffect1(
      () => {
        setIntermediateFormula(_ => formula);
        None;
      },
      [|formula|],
    );

    React.useEffect1(
      () =>
        if (!hasFormula) {
          let timeoutId =
            Js.Global.setTimeout(
              () => {setHasFormula(_ => formula !== "")},
              currentSize === Sm ? 0 : 500,
            );
          Some(() => Js.Global.clearTimeout(timeoutId));
        } else {
          setHasFormula(_ => formula !== "");
          None;
        },
      [|formula|],
    );

    let disabled = intermediateFormula === formula;

    <form type_="GET" onSubmit={e => ReactEvent.Form.preventDefault(e)}>
      <div className={CssHelpers.tcss("px-4 md:px-10 mb-4 text-center")}>
        <h3
          className={CssHelpers.tcss(
            "text-xl font-black uppercase text-gray-800",
          )}>
          {React.string("Formula")}
        </h3>
        <label htmlFor="formula_input">
          <ExplanatoryText
            text="Enter the formula you want to use for the calculation."
          />
        </label>
      </div>
      <textarea
        autoComplete="off"
        id="formula_input"
        placeholder="Examples: weight / height^2\npi * radius^2"
        className={CssHelpers.tcss(
          "text-center w-full bg-gray-100 px-5 py-2 text-gray-700 rounded-lg",
        )}
        value=intermediateFormula
        onChange={e => {
          let value = ReactEvent.Form.currentTarget(e)##value;
          setIntermediateFormula(value);
        }}
      />
      {switch (errorText) {
       | Some(text) =>
         <div
           className={CssHelpers.tcss(
             "mt-2 fade-in text-center text-sm text-red-600",
           )}
           key=text>
           <div className={CssHelpers.tcss("font-bold")}>
             {React.string("Oops, something's wrong with your formula:")}
           </div>
           {React.string(text)}
         </div>
       | None => React.null
       }}
      {hasFormula
         ? <div className={CssHelpers.tcss("mt-2 fade-in")}>
             <ReactExperimental.Suspense
               fallback={<div> {React.string("Loading...")} </div>}>
               <FormulaDisplayer formula />
             </ReactExperimental.Suspense>
           </div>
         : React.null}
      <div className={CssHelpers.tcss("text-center mt-4")}>
        <Button
          disabled
          onClick={_ => setFormula(intermediateFormula)}
          text={
            switch (formula) {
            | "" => "Use formula"
            | _ => "Update formula"
            }
          }
        />
      </div>
      <div className={CssHelpers.tcss("text-center")}>
        <button
          type_="button"
          onClick={_ => setShowHelp(l => !l)}
          className={
            CssHelpers.linkStyles ++ CssHelpers.tcss(" text-xs mt-8")
          }>
          {React.string(
             showHelp
               ? "Hide help"
               : "What functions and constants are available when writing the formula?",
           )}
        </button>
      </div>
      {showHelp
         ? <div className={CssHelpers.tcss("fade-in mt-2")}>
             <FormulaExplanation />
           </div>
         : React.null}
    </form>;
  });