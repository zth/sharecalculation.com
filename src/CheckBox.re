[@react.component]
let make = (~label, ~value, ~onChange) =>
  <label className={CssHelpers.tcss("flex justify-start items-start mt-1")}>
    <div
      className={CssHelpers.tcss(
        "bg-white border-2 rounded border-gray-400 w-6 h-6 flex flex-shrink-0 justify-center items-center mr-2 focus-within:border-blue-500",
      )}>
      <input
        checked=value
        onChange={e => onChange(ReactEvent.Form.currentTarget(e)##checked)}
        type_="checkbox"
        className={CssHelpers.tcss("opacity-0 absolute")}
      />
      <svg
        className={CssHelpers.tcss(
          "fill-current hidden w-4 h-4 text-green-500 pointer-events-none",
        )}
        viewBox="0 0 20 20">
        <path d="M0 11l2-2 5 5L18 3l2 2L7 18z" />
      </svg>
    </div>
    <div
      className={CssHelpers.tcss(
        "select-none text-xs md:font-thin text-gray-700 uppercase mt-1",
      )}>
      {React.string(label)}
    </div>
  </label>;