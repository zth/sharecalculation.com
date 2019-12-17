type description = {
  name: string,
  description: string,
};

let functions: list(description) = [
  {name: "sqrt(x)", description: "Calculate the square root of a value."},
  {name: "abs(x)", description: "Calculate the absolute value of a number."},
  {
    name: "round(x)",
    description: "Round a value towards the nearest integer.",
  },
  {name: "pow(x, y)", description: "Calculates the power of x to y."},
  {name: "exp(x)", description: "Calculate the exponent of a value."},
  {name: "cbrt(x)", description: "Calculate the cubic root of a value."},
  {
    name: "log(x, base)",
    description: "Calculate the logarithm of a value. Providing the base is optional.",
  },
];

let constants: list(description) = [
  {
    name: "e",
    description: "Euler's number, the base of the natural logarithm.",
  },
  {
    name: "phi",
    description: "Phi is the golden ratio. Two quantities are in the golden ratio if their ratio is the same as the ratio of their sum to the larger of the two quantities. Phi is defined as (1 + sqrt(5)) / 2",
  },
  {
    name: "pi",
    description: "The number pi is a mathematical constant that is the ratio of a circle's circumference to its diameter.",
  },
  {
    name: "tau",
    description: "Tau is the ratio constant of a circle's circumference to radius, equal to 2 * pi.",
  },
];

[@react.component]
let make = () =>
  <div className={CssHelpers.tcss("text-sm text-gray-700")}>
    <p>
      {React.string(
         "Here's a reference of some of the constants and functions you can use when building your formula.",
       )}
    </p>
    <p className={CssHelpers.tcss("mt-2")}>
      {React.string(
         "Please note that this is not an exhaustive list, and there's lots of more things you can do (including trigonometry and what not). "
         ++ "For a complete reference, please look at the reference for MathJS, which is the library that's powering this website: ",
       )}
      <a
        target="_blank"
        href="https://mathjs.org/docs/reference/"
        className=CssHelpers.linkStyles
        rel="noreferrer">
        {React.string("MathJs reference")}
      </a>
    </p>
    <h3
      className={CssHelpers.tcss(
        "text-sm font-semibold text-gray-700 uppercase mt-6",
      )}>
      {React.string("Functions")}
    </h3>
    <table className={CssHelpers.tcss("border-2 border-gray-300")}>
      <tbody>
        {functions
         |> Tablecloth.List.mapi(~f=(i, fn) =>
              <tr
                key={fn.name}
                className={
                  i mod 2 === 0
                    ? CssHelpers.tcss("bg-white")
                    : CssHelpers.tcss("bg-gray-200")
                }>
                <td
                  className={CssHelpers.tcss(
                    "font-semibold w-1/3 align-top p-2",
                  )}>
                  {React.string(fn.name)}
                </td>
                <td className={CssHelpers.tcss("align-top p-2")}>
                  {React.string(fn.description)}
                </td>
              </tr>
            )
         |> Tablecloth.Array.fromList
         |> React.array}
      </tbody>
    </table>
    <h3
      className={CssHelpers.tcss(
        "text-sm font-semibold text-gray-700 uppercase mt-6",
      )}>
      {React.string("Constants")}
    </h3>
    <table className={CssHelpers.tcss("border-2 border-gray-300")}>
      <tbody>
        {constants
         |> Tablecloth.List.mapi(~f=(i, fn) =>
              <tr
                key={fn.name}
                className={
                  i mod 2 === 0
                    ? CssHelpers.tcss("bg-white")
                    : CssHelpers.tcss("bg-gray-200")
                }>
                <td
                  className={CssHelpers.tcss(
                    "font-semibold w-1/3 align-top p-2",
                  )}>
                  {React.string(fn.name)}
                </td>
                <td className={CssHelpers.tcss("align-top p-2")}>
                  {React.string(fn.description)}
                </td>
              </tr>
            )
         |> Tablecloth.Array.fromList
         |> React.array}
      </tbody>
    </table>
  </div>;