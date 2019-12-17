[@react.component]
let make =
  React.memo((~formula, ~style, ~values) => {
    let parsedFormula =
      React.useMemo1(() => MathJs.parse(formula), [|formula|]);

    switch (parsedFormula) {
    | Ok(parsedFormula) => <ResultDisplayer style parsedFormula values />
    | Error(_) => React.null
    };
  });