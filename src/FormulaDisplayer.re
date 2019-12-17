[@react.component]
let make =
  React.memo((~formula) =>
    switch (formula) {
    | "" => React.null
    | formula =>
      let maybeKatex = Suspender.useKaTex();

      switch (maybeKatex) {
      | Some(katex) =>
        <div
          className={CssHelpers.tcss("text-gray-900 overflow-y-auto")}
          dangerouslySetInnerHTML={
            "__html":
              switch (formula |> MathJs.parse) {
              | Ok(v) =>
                katex.renderToString(
                  v |> MathJs.ParsedExpression.toTex,
                  KaTex.makeOptions(~displayMode=true, ()),
                )

              | Error(_) => ""
              },
          }
        />
      | None => React.null
      };
    }
  );