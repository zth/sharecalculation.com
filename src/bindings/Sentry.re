type options = {dsn: string};

let makeOptions = (~dsn: string, ()) => {dsn: dsn};

[@bs.module "@sentry/browser"] external init: options => unit = "init";
[@bs.module "@sentry/browser"] external captureMessage: string => unit = "captureMessage";