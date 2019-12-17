[@react.component]
let make =
  React.memo((~encodedInitialState) =>
    <>
      <div className={CssHelpers.tcss("mt-8 md:mt-4 text-gray-900")}>
        <div>
          <div className={CssHelpers.tcss("block")}>
            <a
              href="/"
              target="_blank"
              className={
                CssHelpers.linkStyles
                ++ CssHelpers.tcss(" text-xs block mt-2")
              }>
              {React.string("Create your own shareable calculation")}
            </a>
            {switch (encodedInitialState) {
             | Some(encodedInitialState) =>
               <a
                 href={"/create-from/" ++ encodedInitialState}
                 target="_blank"
                 className={
                   CssHelpers.linkStyles
                   ++ CssHelpers.tcss(" text-xs block mt-2")
                 }>
                 {React.string(
                    "Create new calculation from current calculation",
                  )}
               </a>
             | None => React.null
             }}
          </div>
        </div>
      </div>
      <div
        className={CssHelpers.tcss(
          "mt-4 text mt-2 text-xs text-gray-700 text-left",
        )}>
        {React.string("Want to save this calculation? Bookmark this page!")}
      </div>
    </>
  );