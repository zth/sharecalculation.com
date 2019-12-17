[@react.component]
let make = (~active, ~onClick) =>
  <button
    onClick={_ => onClick()}
    className={
      CssHelpers.tcss(
        "appearance-none rounded-full w-4 h-4 text-2xs HelpIcon--position ",
      )
      ++ (
        active
          ? CssHelpers.tcss("bg-indigo-500 text-white")
          : CssHelpers.tcss("bg-indigo-200 text-indigo-600")
      )
    }>
    {React.string("?")}
  </button>;