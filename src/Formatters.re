let formatNumber = (~style, num) => {
  open Intl.NumberFormat;
  let formatter = make(~locales=[|JsBindings.language|], ~style, ());
  format(formatter, num);
};