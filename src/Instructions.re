module Step = {
  [@react.component]
  let make = (~num, ~text, ~title) =>
    <div className={CssHelpers.tcss("flex p-2 bg-white mt-2")}>
      <div className={CssHelpers.tcss("self-start")}>
        <div
          className={CssHelpers.tcss(
            "rounded-full p-2 w-8 h-8 bg-indigo-200 text-indigo-700 flex items-center justify-center",
          )}>
          <div
            className={CssHelpers.tcss(
              "text-sm font-bold align-top justify-start",
            )}>
            {React.string(num)}
          </div>
        </div>
      </div>
      <div className={CssHelpers.tcss("pl-4")}>
        <div className={CssHelpers.tcss("text-md font-bold text-gray-900")}>
          {React.string(title)}
        </div>
        <ExplanatoryText text />
      </div>
    </div>;
};

[@react.component]
let make = () =>
  <div className={CssHelpers.tcss("w-full md:w-1/2 mx-auto px-4")}>
    <Step
      title="Write formula"
      num="1"
      text="Write your formula by using as many variables as you need. For example weight / height^2 has two variables, weight and height."
    />
    <Step
      title="Add information to help users"
      num="2"
      text="You can add information about your formula and variables, like what the result means, and what each variable is."
    />
    <Step
      title="Try and share"
      num="3"
      text="Finally, try your calculation and then share it when you're done!"
    />
  </div>;