[@react.component]
let make = () => {
  let api = State.useStateApi();

  let (state, _) = api.useStore();
  let (showShareLink, setShowShareLink) = React.useState(() => false);
  let (hasCopied, setHasCopied) = React.useState(() => false);

  React.useEffect1(
    () => {
      let timeoutId =
        Js.Global.setTimeout(() => setHasCopied(_ => false), 10000);

      Some(() => Js.Global.clearTimeout(timeoutId));
    },
    [|hasCopied|],
  );

  React.useEffect1(
    () => {
      if (showShareLink) {
        Utils.saveHasUsed(true);
      };

      None;
    },
    [|showShareLink|],
  );

  <div>
    <div className={CssHelpers.tcss("px-4 md:px-10 mb-4 text-center")}>
      <h3
        className={CssHelpers.tcss(
          "text-xl font-black uppercase text-gray-800",
        )}>
        {React.string("Share")}
      </h3>
      <ExplanatoryText text="You share your calculation by sharing a link." />
      <div className={CssHelpers.tcss("font-bold")}>
        <ExplanatoryText
          text="Please note that the link is long, but you really do need the full link."
        />
      </div>
    </div>
    <div>
      {showShareLink
         ? {
           let link =
             state
             |> Serialize.serialize
             |> Compressor.compress
             |> LinkUtils.makeCalculationLink(
                  ~slug=
                    switch (state.title |> JsUtils.slugify) {
                    | "" => None
                    | slug => Some(slug)
                    },
                )
             |> JsUtils.addOrigin;
           <div>
             <div className={CssHelpers.tcss("flex flex-col")}>
               <div>
                 <input
                   type_="text"
                   id="save_share_input"
                   value=link
                   onChange={_ => ()}
                   onClick={e => ReactEvent.Mouse.currentTarget(e)##select()}
                   className={CssHelpers.tcss(
                     "w-full px-5 py-1 text-gray-700 bg-gray-200 rounded",
                   )}
                 />
               </div>
               <div className="mt-2 mx-auto">
                 <Button
                   onClick={_ =>
                     JsUtils.copyToClipboardFromElement("save_share_input")
                       ? setHasCopied(_ => true) : setHasCopied(_ => false)
                   }
                   text="Copy to clipboard"
                 />
               </div>
             </div>
             {hasCopied
                ? <div
                    className={CssHelpers.tcss(
                      "fade-in mt-4 p-2 bg-green-100 text-center text-green-700 text-sm font-semibold",
                    )}>
                    {React.string("Link copied to clipboard")}
                  </div>
                : React.null}
             <div className={CssHelpers.tcss("mt-4 text-center")}>
               <a href=link className=CssHelpers.linkStyles target="_blank">
                 {React.string("Click to open calculation in new window")}
               </a>
             </div>
           </div>;
         }
         : <div className={CssHelpers.tcss("flex justify-center")}>
             <button
               className=CssHelpers.linkStyles
               onClick={_ => setShowShareLink(l => !l)}>
               {React.string(showShareLink ? "Hide link" : "Show link")}
             </button>
           </div>}
    </div>
  </div>;
};