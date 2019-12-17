type options = {
  displayMode: option(bool),
  output: option(string),
  leqno: option(bool),
  fleqn: option(bool),
  throwOnError: option(bool),
  errorColor: option(string),
  minRuleThickness: option(float),
  colorIsTextColor: option(bool),
  maxSize: option(float),
};

let makeOptions =
    (
      ~displayMode=?,
      ~output=?,
      ~leqno=?,
      ~fleqn=?,
      ~throwOnError=?,
      ~errorColor=?,
      ~minRuleThickness=?,
      ~colorIsTextColor=?,
      ~maxSize=?,
      (),
    ) => {
  displayMode,
  output,
  leqno,
  fleqn,
  throwOnError,
  errorColor,
  minRuleThickness,
  colorIsTextColor,
  maxSize,
};

type katex = {renderToString: (MathJs.tex, options) => string};