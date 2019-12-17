[@react.component]
let make = () => {
  React.useEffect0(() => {
    JsUtils.hideLoading();
    None;
  });

  let url = ReasonReactRouter.useUrl();

  <>
    <BsReactHelmet>
      <title> {React.string("ShareCalculation.com")} </title>
      <meta
        name="description"
        content="Create and share interactive calculations. When creating a spreadsheet is overkill."
      />
    </BsReactHelmet>
    <div
      className={CssHelpers.tcss("mx-auto md:w-2/3 sm:w-full mb-32 fade-in")}>
      <div className={CssHelpers.tcss("mt-8 sm:mx-2 md:m-0")}>
        {switch (url.path) {
         | ["v", _, data]
         | ["v", data] => <ViewCalculation serializedData=data />
         | ["create-from", data] =>
           <>
             <Title />
             <CreatorFormWrapper
               initialData={Some(data |> Serialize.deserialize)}
             />
           </>
         | [] => <> <Title /> <CreatorFormWrapper initialData=None /> </>
         | _ =>
           ReasonReactRouter.replace("/");
           React.null;
         }}
      </div>
    </div>
  </>;
};