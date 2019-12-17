[@react.component]
let make = () => {
  let api = State.useStateApi();
  let (formula, _) = api.useStoreWithSelector(s => s.formula, ());
  let hasFormula = formula !== "";
  let currentSize = Responsive.currentSize();

  let hasUsed = React.useMemo0(Utils.loadHasUsed);

  <>
    {!hasUsed ? <> <Instructions /> <TrackLine /> </> : React.null}
    <ReactFlipToolkit.Flipper
      flipKey={
        switch (currentSize, hasFormula) {
        | (Sm, _)
        | (Md | Lg | Xl, true) => "formula"
        | (Md | Lg | Xl, false) => "no-formula"
        }
      }>
      <div className={CssHelpers.tcss("mx-auto mb-2 block lg:flex")}>
        <div
          className={
            CssHelpers.tcss("w-full md:w-1/2  mx-auto ")
            ++ (hasFormula ? CssHelpers.tcss("flex-1") : "")
          }>
          <div>
            <ReactFlipToolkit.Flipped flipId="left-col" spring="veryGentle">
              <div className={CssHelpers.tcss("mx-4 md:mx-0")}>
                <Box> <FormulaInput /> </Box>
                {hasFormula
                   ? <div className={CssHelpers.tcss("md:hidden fade-in")}>
                       <TrackLine />
                     </div>
                   : React.null}
              </div>
            </ReactFlipToolkit.Flipped>
            {hasFormula
               ? <div
                   className={CssHelpers.tcss(
                     "md:mt-8 fade-in mx-4 md:mx-0 md:anim-delay",
                   )}>
                   <Box> <Describe /> </Box>
                 </div>
               : React.null}
          </div>
          {switch (currentSize, hasFormula) {
           | (Sm, _)
           | (Md | Lg | Xl, false) => React.null
           | (Md | Lg | Xl, true) =>
             <div className={CssHelpers.tcss("anim-delay fade-in")}>
               <TrackLine />
               <div className={CssHelpers.tcss("mx-4 md:mx-0")}>
                 <Box> <SaveAndShare /> </Box>
               </div>
             </div>
           }}
        </div>
        {hasFormula
           ? <ReactFlipToolkit.Flipped flipId="result">
               <div className={CssHelpers.tcss("flex-1 md:ml-10 relative")}>
                 <div
                   className={CssHelpers.tcss(
                     "top-inset md:sticky m-4 md:m-0 md:p-4 md:pt-4 md:border-dashed md:border-gray-300 md:border-2 md:border-collapse",
                   )}>
                   <div className={CssHelpers.tcss("mb-4")}>
                     <div className={CssHelpers.tcss("md:hidden")}>
                       <TrackLine />
                     </div>
                     <h3
                       className={CssHelpers.tcss(
                         "text-gray-600 text-center text-xl uppercase md:font-thin",
                       )}>
                       {React.string("Preview")}
                     </h3>
                     <div className={CssHelpers.tcss("text-center mb-4")}>
                       <ExplanatoryText
                         text="This is roughly what the result will look like."
                       />
                     </div>
                   </div>
                   <CreatorFormUseFormWrapper />
                 </div>
               </div>
             </ReactFlipToolkit.Flipped>
           : <ReactFlipToolkit.Flipped flipId="result">
               <div />
             </ReactFlipToolkit.Flipped>}
        {switch (currentSize, hasFormula) {
         | (Md | Lg | Xl, _)
         | (Sm, false) => React.null
         | (Sm, true) =>
           <div className={CssHelpers.tcss("anim-delay fade-in")}>
             <TrackLine />
             <div className={CssHelpers.tcss("mx-4 md:mx-0")}>
               <Box> <SaveAndShare /> </Box>
             </div>
           </div>
         }}
      </div>
    </ReactFlipToolkit.Flipper>
  </>;
};