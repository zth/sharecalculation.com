[@bs.module "./utils"] external slugify: string => string = "slugify";
[@bs.module "./utils"] external addOrigin: string => string = "addOrigin";
[@bs.module "./utils"] external hideLoading: unit => unit = "hideLoading";
[@bs.module "./utils"]
external copyToClipboardFromElement: string => bool =
  "copyToClipboardFromElement";

[@bs.val "__DEV__"] external devMode: bool = "__DEV__";
[@bs.val "SENTRY_ID"] external sentryId: string = "SENTRY_ID";
[@bs.val "ANALYTICS_ID"] external analyticsId: string = "ANALYTICS_ID";