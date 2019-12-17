type state = {
  showTitle: bool,
  showDescription: bool,
};

[@react.component]
let make = (~description, ~setDescription, ~title, ~setTitle) => {
  let (state, setState) =
    React.useState(() =>
      {showTitle: title !== "", showDescription: description !== ""}
    );

  <>
    {state.showTitle
       ? <div>
           <label
             className={CssHelpers.tcss("block text-sm text-gray-700")}
             htmlFor="title_input">
             {React.string("Title")}
           </label>
           <input
             autoFocus=true
             type_="text"
             id="title_input"
             className={CssHelpers.tcss(
               "w-full px-5 py-1 text-gray-700 bg-gray-200 rounded",
             )}
             value=title
             onChange={e =>
               setTitle(ReactEvent.Form.currentTarget(e)##value)
             }
             placeholder="Example: Body Mass Index (BMI)"
           />
           <MaximumCharacters
             text=title
             maxLength=Constants.maximumTitleLength
           />
         </div>
       : <div className={CssHelpers.tcss("mt-4")}>
           <button
             type_="button"
             className=CssHelpers.linkStyles
             onClick={_ => setState(s => {...s, showTitle: true})}>
             {React.string("+ Add title")}
           </button>
         </div>}
    {state.showDescription
       ? <div className={CssHelpers.tcss("mt-4")}>
           <label
             className={CssHelpers.tcss("block text-sm text-gray-700")}
             htmlFor="formula_desc">
             {React.string("Formula description")}
           </label>
           <textarea
             id="formula_desc"
             autoFocus=true
             className={CssHelpers.tcss(
               "w-full px-5 py-1 text-gray-700 bg-gray-200 rounded",
             )}
             value=description
             onChange={e =>
               setDescription(ReactEvent.Form.currentTarget(e)##value)
             }
             placeholder="Example: Calculate your BMI."
             rows=2
           />
           <MaximumCharacters
             text=description
             maxLength=Constants.maximumDescLength
           />
         </div>
       : <div className={CssHelpers.tcss("mt-1")}>
           <button
             type_="button"
             className=CssHelpers.linkStyles
             onClick={_ => setState(s => {...s, showDescription: true})}>
             {React.string("+ Add description")}
           </button>
         </div>}
  </>;
};