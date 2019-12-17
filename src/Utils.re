let hasUsedStorageKey = "@calc/has-used";

let saveHasUsed = hasUsed =>
  Dom.Storage.(
    localStorage |> setItem(hasUsedStorageKey, string_of_bool(hasUsed))
  );

let loadHasUsed = () =>
  switch (Dom.Storage.(localStorage |> getItem(hasUsedStorageKey))) {
  | Some(v) =>
    switch (Js.Json.parseExn(v)) {
    | exception _ => false
    | b =>
      switch (Js.Json.decodeBoolean(b)) {
      | Some(boolean) => boolean
      | None => false
      }
    }
  | None => false
  };

let classes = (l: list((string, bool))) =>
  l
  |> Tablecloth.List.filterMap(~f=((str, shouldInclude)) =>
       shouldInclude ? Some(str) : None
     )
  |> Tablecloth.String.join(~sep=" ");