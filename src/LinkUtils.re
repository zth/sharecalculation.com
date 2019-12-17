let makeCalculationLink = (~slug, serialized) =>
  "/v/"
  ++ (
    switch (slug) {
    | Some(slug) => slug ++ "/"
    | None => ""
    }
  )
  ++ serialized;