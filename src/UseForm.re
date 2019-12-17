[@react.component]
let make =
    (~state: State.state, ~setValue, ~preview=false, ~encodedInitialState=?) => {
  let (showFormula, setShowFormula) = React.useState(() => false);

  let toggleShowFormula =
    React.useCallback1(
      () => setShowFormula(lastVal => !lastVal),
      [|setShowFormula|],
    );

  let showFormulaButtonContent =
    <div className={CssHelpers.tcss("text-center")}>
      <button
        className={
          CssHelpers.linkStyles ++ CssHelpers.tcss(" text-xs sm:mt-1 md:mt-0")
        }
        onClick={_ => toggleShowFormula()}>
        {React.string((showFormula ? "Hide" : "Show") ++ " formula used")}
      </button>
    </div>;

  let currentSize = Responsive.currentSize();

  <div className={CssHelpers.tcss("mx-4 md:mx-0 mt-4 md:mt-16")}>
    <UseFormIntro title={state.title} description={state.description} />
    <Box>
      <div
        className={CssHelpers.tcss(
          "relative flex flex-col-reverse md:flex-col",
        )}>
        {showFormula
           ? <FormulaDisplayer formula={state.formula} /> : React.null}
        <div className={CssHelpers.tcss("mb-4")}>
          <UseFormEnterValues values={state.values} setValue preview />
        </div>
        <div className={CssHelpers.tcss("mb-4 sticky md:static top-inset")}>
          <UseFormResultDisplayer
            formula={state.formula}
            values={state.values}
            style={state.style}
          />
        </div>
        {currentSize !== Sm ? showFormulaButtonContent : React.null}
      </div>
      {currentSize === Sm ? showFormulaButtonContent : React.null}
    </Box>
    <div className={CssHelpers.tcss("mt-16")}>
      {preview ? React.null : <UseFormFooter encodedInitialState />}
    </div>
  </div>;
};