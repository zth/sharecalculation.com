type tex;

module CompiledExpression: {
  type t;
  let evaluate: (Js.Dict.t(float), t) => float;
} = {
  type t;

  [@bs.send] external _evaluate: (t, Js.Dict.t(float)) => float = "evaluate";
  let evaluate = (config, t) => t->_evaluate(config);
};

module ParsedExpression: {
  type t;
  let getSymbols: t => list(string);
  let compile: t => CompiledExpression.t;
  let toTex: t => tex;
  let toString: t => string;
} = {
  type t;

  [@bs.module "./mathjs"]
  external _getSymbols: t => array(string) = "getSymbols";

  let getSymbols = t => t |> _getSymbols |> Tablecloth.Array.toList;

  [@bs.send] external compile: t => CompiledExpression.t = "compile";
  [@bs.send] external toTex: t => tex = "toTex";
  [@bs.send] external toString: t => string = "toString";
};

[@bs.module "mathjs/number"]
external _parse: string => ParsedExpression.t = "parse";
[@bs.module "mathjs/number"]
external simplifyString: string => ParsedExpression.t = "simplify";
[@bs.module "mathjs/number"]
external simplifyPasedExpression: ParsedExpression.t => ParsedExpression.t =
  "simplify";

exception Parse_error(string);

let parse = v =>
  switch (v |> _parse) {
  | exception (Js.Exn.Error(e)) =>
    Error(
      Js.Exn.message(e) |> Tablecloth.Option.withDefault(~default="Error"),
    )
  | v =>
    let compiled = v |> ParsedExpression.compile;

    switch (
      CompiledExpression.evaluate(
        v
        |> ParsedExpression.getSymbols
        |> Tablecloth.List.map(~f=s => (s, 1.0))
        |> Js.Dict.fromList,
        compiled,
      )
    ) {
    | exception (Js.Exn.Error(err)) =>
      Error(
        Js.Exn.message(err)
        |> Tablecloth.Option.withDefault(~default="Error"),
      )
    | _ => Ok(v)
    };
  };